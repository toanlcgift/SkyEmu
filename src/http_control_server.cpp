extern "C"{
    #include "http_control_server.h"
};
#include "httplib.h"
#include <thread>
#include <iostream>
#include <sstream>
#include <vector>
#include <atomic>
struct HCSServer{
    hcs_callback callback; 
    httplib::Server svr;
    std::recursive_mutex mutex;
    std::thread thread;
    int64_t port; 
    std::atomic<bool> server_running;
    static void server_thread(HCSServer* server){
        server->svr.set_tcp_nodelay(true);
        server->svr.set_pre_routing_handler([server](const httplib::Request& req, httplib::Response& res) {
            std::vector<const char*> params;
            for(auto &v :req.params){
                params.push_back(v.first.c_str());
                params.push_back(v.second.c_str());
            }
            params.push_back(NULL);
            params.push_back(NULL);
            bool handled = false; 
            if(server->callback){
                uint64_t result_size = 0; 
                const char *mime_type = "";
                server->mutex.lock();
                uint8_t * result = server->callback(req.path.c_str(),&params[0],&result_size, &mime_type);
                server->mutex.unlock();
                if(result&&result_size){
                    res.set_content((const char*)result,result_size,mime_type);
                    free(result);
                    return httplib::Server::HandlerResponse::Handled;
                }
            }
            return httplib::Server::HandlerResponse::Unhandled;
        });
        
        // Try binding to specific addresses for better macOS compatibility
        // First try 0.0.0.0 (IPv4 only), then fall back to :: (IPv6)
        std::string bind_host = "0.0.0.0";
        std::cout<<"Starting HCS: http://"<<bind_host<<":"<<server->port<<std::endl;
        
        // Check if listen succeeds
        auto result = server->svr.listen(bind_host.c_str(), server->port);
        if(!result) {
            std::cerr<<"Failed to start HTTP server on "<<bind_host<<":"<<server->port<<std::endl;
#ifdef SE_PLATFORM_MACOS
            // On macOS, try :: (IPv6) if 0.0.0.0 fails
            bind_host = "::";
            std::cout<<"Trying IPv6: http://"<<bind_host<<":"<<server->port<<std::endl;
            result = server->svr.listen(bind_host.c_str(), server->port);
            if(!result) {
                std::cerr<<"Failed to start HTTP server on "<<bind_host<<":"<<server->port<<std::endl;
            } else {
                std::cout<<"HTTP server started successfully on http://"<<bind_host<<":"<<server->port<<std::endl;
            }
#else
            std::cerr<<"HTTP server listen returned false"<<std::endl;
#endif
        } else {
            std::cout<<"HTTP server started successfully on http://"<<bind_host<<":"<<server->port<<std::endl;
        }
        
        server->server_running = result;
        
        // Keep the server running until stopped
        while(server->server_running.load()){
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        
        std::cout<<"Terminating HCS: http://"<<bind_host<<":"<<server->port<<std::endl;
    }
    HCSServer(int64_t port, hcs_callback call){
        callback = call; 
        this->port = port; 
        server_running = false;
        thread = std::thread(server_thread,this);
    }
    ~HCSServer(){
       server_running = false;
       svr.stop();
       thread.join();
    }
};
HCSServer * server = NULL;
extern "C"{
    void hcs_update(bool enable, int64_t port, hcs_callback callback){
        if(server){
            std::lock_guard<std::recursive_mutex> lock(server->mutex);
            if(!enable || port != server->port){
                delete server;
                server = NULL;
            }
        }
        if(!server && enable){
            server = new HCSServer(port, callback);
            // Lock the mutex to prevent callbacks until hcs_resume_callbacks is called
            // This matches the original behavior
            server->mutex.lock();
        }
    }

    void hcs_suspend_callbacks(){
        if(server)server->mutex.lock();
    }
    void hcs_resume_callbacks(){
        if(server)server->mutex.unlock();
    }
    void hcs_join_server_thread(){
        if(server)server->thread.join();
    }
    bool hcs_is_server_running(){
        return server && server->server_running.load();
    }
}