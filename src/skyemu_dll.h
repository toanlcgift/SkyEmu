#ifndef SKYEMU_DLL_H
#define SKYEMU_DLL_H

#include <stdint.h>
#include <stdbool.h>

/*
 * SkyEmu DLL API header
 *
 * When building the DLL, define SKYEMU_DLL_EXPORTS so that functions are
 * exported with __declspec(dllexport).  When consuming the DLL from C/C++
 * code, include this header without defining SKYEMU_DLL_EXPORTS so that
 * functions are imported with __declspec(dllimport).
 *
 * For non-MSVC compilers on Windows (MinGW/GCC) we use __attribute__((visibility("default"))).
 * On non-Windows platforms the macros expand to nothing.
 */

/*
 * SKYEMU_API expands to dllexport/dllimport only when SE_PLATFORM_WINDOWS_DLL
 * is defined.  In all other build configurations it expands to nothing so that
 * the existing executable/library builds are unaffected.
 */
#if defined(SE_PLATFORM_WINDOWS_DLL)
typedef void(__stdcall* RemoteKeycodeCallback)(const char* data1, const char* data2);
typedef void(__stdcall* PingCallback)(void);
typedef void(__stdcall* ExternalMenuCallback)(void);
  #if defined(SKYEMU_DLL_EXPORTS)
    #define SKYEMU_API __declspec(dllexport)
  #else
    #define SKYEMU_API __declspec(dllimport)
  #endif
#else
  #define SKYEMU_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Load an HTML file (used for cloud/HTTP control) */
SKYEMU_API void se_load_html(const char *filename);

/* Load a ROM file by path */
SKYEMU_API void se_load_rom(const char *filename);

/* Show the emulator UI overlay */
SKYEMU_API void se_show_ui(void);

/* Hide the emulator UI overlay */
SKYEMU_API void se_hide_ui(void);

/* Set stretch-to-fit mode: 0 = off, 1 = on */
SKYEMU_API void se_stretch_to_fit(int fit);

/*
 * Screen shader modes:
 *   0 = Pixelate (nearest-neighbor)
 *   1 = Bilinear
 *   2 = LCD filter
 *   3 = LCD & Subpixels
 *   4 = Smooth Upscale (xBRZ)
 */
SKYEMU_API void se_set_screen_shader(uint32_t shader_mode);
SKYEMU_API uint32_t se_get_screen_shader(void);

/*
   * New API: send a key event directly to the emulator.
   * The function is exported on all platforms. It can be called
   * from native code or via JNI on Android.
   */
SKYEMU_API void se_send_key(const char* key, float value);

/*
 * SkyEmu Framebuffer Interface
 * 
 * The framebuffer is in BGRA format (4 bytes per pixel).
 */

/* System types matching SkyEmu's internal definitions */
#define SE_SYSTEM_NONE  0
#define SE_SYSTEM_GB    1
#define SE_SYSTEM_GBA   2
#define SE_SYSTEM_NDS   3

/* Screen dimensions */
#define SE_GBA_LCD_W    240
#define SE_GBA_LCD_H    160

#define SE_NDS_LCD_W    256
#define SE_NDS_LCD_H    192

#define SE_GB_LCD_W     160
#define SE_GB_LCD_H     144

/* Maximum framebuffer size (NDS top + bottom) */
#define SE_MAX_FRAMEBUFFER_SIZE (SE_NDS_LCD_W * SE_NDS_LCD_H * 4 * 2)

/* Get the currently emulated system */
SKYEMU_API int se_get_system(void);

/* Get the framebuffer dimensions */
SKYEMU_API void se_get_framebuffer_dimensions(int* width, int* height);

/* Get the number of framebuffers for the current system */
SKYEMU_API int se_get_framebuffer_count(void);

/* Get a pointer to the framebuffer data (BGRA format) */
SKYEMU_API const uint8_t* se_get_framebuffer(int screen_index);

/* Copy the framebuffer to a caller-provided buffer */
SKYEMU_API int se_copy_framebuffer(uint8_t* buffer, int buffer_size);

/* Check if a frame is ready */
SKYEMU_API bool se_is_frame_ready(void);

/* Get the framebuffer as a contiguous buffer */
SKYEMU_API const uint8_t* se_get_screenshot(int* out_width, int* out_height);

#ifdef SE_PLATFORM_WINDOWS_DLL
SKYEMU_API int win_main(int argc, char* argv[]);

    // 2. Export a function that takes the callback
SKYEMU_API void set_remote_keycode_callback(RemoteKeycodeCallback callback);
SKYEMU_API void set_ping_callback(PingCallback callback);
SKYEMU_API void set_external_menu_callback(ExternalMenuCallback callback);
SKYEMU_API void se_capture_state_slot(int slot);
SKYEMU_API void se_restore_state_slot(int slot);
#endif

#ifdef __cplusplus
}
#endif

#endif /* SKYEMU_DLL_H */