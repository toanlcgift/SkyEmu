/*
 *  main.m
 *  SkyEmu iOS Application Entry Point
 *  
 *  This file provides the iOS application entry point.
 *  When building as an app, this is used.
 *  When integrating as a library, the user's app provides its own main.
 */

#include <UIKit/UIKit.h>
#include "ios/SkyEmu.h"

int main(int argc, char * argv[]) {
    @autoreleasepool {
        // Initialize SkyEmu
        se_init(SE_SYSTEM_GBA, nil);
        
        // Run the main loop
        BOOL done = NO;
        while (!done) {
            if (!se_run_frame()) {
                done = YES;
            }
            
            // Handle events and sleep to avoid 100% CPU
            // The actual event handling is done by sokol_app
            usleep(16666); // ~60 FPS
        }
        
        // Shutdown
        se_shutdown();
        
        return 0;
    }
}
