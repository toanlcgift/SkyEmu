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
 * Persistent Settings API
 * Getters and setters for all gui_state.settings fields.
 * Use these from Windows, macOS, iOS, or Android (via JNI).
 */

/* Volume (0.0 - 1.0) */
SKYEMU_API void se_set_volume(float volume);
SKYEMU_API float se_get_volume(void);

/* Theme index */
SKYEMU_API void se_set_theme(uint32_t theme);
SKYEMU_API uint32_t se_get_theme(void);

/* GB palette colors (index 0-3) */
SKYEMU_API void se_set_gb_palette(int index, uint32_t color);
SKYEMU_API uint32_t se_get_gb_palette(int index);

/* Ghosting effect strength (0.0 - 1.0) */
SKYEMU_API void se_set_ghosting(float ghosting);
SKYEMU_API float se_get_ghosting(void);

/* Color correction strength (0.0 - 1.0) */
SKYEMU_API void se_set_color_correction(float value);
SKYEMU_API float se_get_color_correction(void);

/* Integer scaling: 0 = off, 1 = on */
SKYEMU_API void se_set_integer_scaling(uint32_t value);
SKYEMU_API uint32_t se_get_integer_scaling(void);

/* Screen rotation: 0=None, 1=Left, 2=Right, 3=Upside Down */
SKYEMU_API void se_set_screen_rotation(uint32_t rotation);
SKYEMU_API uint32_t se_get_screen_rotation(void);

/* Stretch to fit getter (setter already exists as se_stretch_to_fit) */
SKYEMU_API uint32_t se_get_stretch_to_fit(void);

/* Auto-hide touch controls: 0 = off, 1 = on */
SKYEMU_API void se_set_auto_hide_touch_controls(uint32_t value);
SKYEMU_API uint32_t se_get_auto_hide_touch_controls(void);

/* Touch controls opacity (0.0 - 1.0) */
SKYEMU_API void se_set_touch_controls_opacity(float opacity);
SKYEMU_API float se_get_touch_controls_opacity(void);

/* Always show menubar: 0 = off, 1 = on */
SKYEMU_API void se_set_always_show_menubar(uint32_t value);
SKYEMU_API uint32_t se_get_always_show_menubar(void);

/* Language index */
SKYEMU_API void se_set_language_int(uint32_t language);
SKYEMU_API uint32_t se_get_language_int(void);

/* Touch controls scale factor */
SKYEMU_API void se_set_touch_controls_scale(float scale);
SKYEMU_API float se_get_touch_controls_scale(void);

/* Show turbo on touch controls: 0 = off, 1 = on */
SKYEMU_API void se_set_touch_controls_show_turbo(uint32_t value);
SKYEMU_API uint32_t se_get_touch_controls_show_turbo(void);

/* Save game data to ROM path: 0 = off, 1 = on */
SKYEMU_API void se_set_save_to_path(uint32_t value);
SKYEMU_API uint32_t se_get_save_to_path(void);

/* Force DMG mode for Color GB: 0 = off, 1 = on */
SKYEMU_API void se_set_force_dmg_mode(uint32_t value);
SKYEMU_API uint32_t se_get_force_dmg_mode(void);

/* GBA color correction mode: 0 = SkyEmu, 1 = Higan */
SKYEMU_API void se_set_gba_color_correction_mode(uint32_t mode);
SKYEMU_API uint32_t se_get_gba_color_correction_mode(void);

/* HTTP control server port */
SKYEMU_API void se_set_http_control_server_port(uint32_t port);
SKYEMU_API uint32_t se_get_http_control_server_port(void);

/* HTTP control server enable: 0 = off, 1 = on */
SKYEMU_API void se_set_http_control_server_enable(uint32_t value);
SKYEMU_API uint32_t se_get_http_control_server_enable(void);

/* Avoid overlapping touchscreen: 1=Portrait, 2=Landscape, 3=Both, 0=Off */
SKYEMU_API void se_set_avoid_overlapping_touchscreen(uint32_t value);
SKYEMU_API uint32_t se_get_avoid_overlapping_touchscreen(void);

/* Custom font scale factor */
SKYEMU_API void se_set_custom_font_scale(float scale);
SKYEMU_API float se_get_custom_font_scale(void);

/* Hardcore mode (achievements): 0 = off, 1 = on */
SKYEMU_API void se_set_hardcore_mode(uint32_t value);
SKYEMU_API uint32_t se_get_hardcore_mode(void);

/* Draw challenge indicators: 0 = off, 1 = on */
SKYEMU_API void se_set_draw_challenge_indicators(uint32_t value);
SKYEMU_API uint32_t se_get_draw_challenge_indicators(void);

/* Draw progress indicators: 0 = off, 1 = on */
SKYEMU_API void se_set_draw_progress_indicators(uint32_t value);
SKYEMU_API uint32_t se_get_draw_progress_indicators(void);

/* Draw leaderboard trackers: 0 = off, 1 = on */
SKYEMU_API void se_set_draw_leaderboard_trackers(uint32_t value);
SKYEMU_API uint32_t se_get_draw_leaderboard_trackers(void);

/* Draw notifications: 0 = off, 1 = on */
SKYEMU_API void se_set_draw_notifications(uint32_t value);
SKYEMU_API uint32_t se_get_draw_notifications(void);

/* GUI scale factor */
SKYEMU_API void se_set_gui_scale_factor(float scale);
SKYEMU_API float se_get_gui_scale_factor(void);

/* Only one notification at a time: 0 = off, 1 = on */
SKYEMU_API void se_set_only_one_notification(uint32_t value);
SKYEMU_API uint32_t se_get_only_one_notification(void);

/* Enable download cache: 0 = off, 1 = on */
SKYEMU_API void se_set_enable_download_cache(uint32_t value);
SKYEMU_API uint32_t se_get_enable_download_cache(void);

/* NDS layout index */
SKYEMU_API void se_set_nds_layout(uint32_t layout);
SKYEMU_API uint32_t se_get_nds_layout(void);

/* Touch screen show button labels: 0 = off, 1 = on */
SKYEMU_API void se_set_touch_screen_show_button_labels(uint32_t value);
SKYEMU_API uint32_t se_get_touch_screen_show_button_labels(void);

/* Show screen bezel: 0 = off, 1 = on */
SKYEMU_API void se_set_show_screen_bezel(uint32_t value);
SKYEMU_API uint32_t se_get_show_screen_bezel(void);

/* Draw debug menu: 0 = off, 1 = on */
SKYEMU_API void se_set_draw_debug_menu(uint32_t value);
SKYEMU_API uint32_t se_get_draw_debug_menu(void);

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