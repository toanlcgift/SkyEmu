#ifndef IOS_SUPPORT_H
#define IOS_SUPPORT_H 1

void se_ios_open_file_picker( int num_extensions, const char ** extensions);
void se_ios_get_safe_ui_padding(float *top, float* bottom,float* left, float *right);
void se_ios_set_documents_working_directory();
void se_ios_open_modal(const char* url);
void se_ios_close_modal();
void se_ios_remote_keycode_callback(const char *data1, const char* data2);
void se_ios_ping();
void se_ios_open_external_menu();

#if defined(SE_PLATFORM_MACOS)
#define se_macos_remote_keycode_callback se_ios_remote_keycode_callback
#define se_macos_ping se_ios_ping
#define se_macos_open_external_menu se_ios_open_external_menu
#endif

#endif
