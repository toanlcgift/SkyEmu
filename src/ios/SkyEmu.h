/*
 *  SkyEmu.h
 *  SkyEmu iOS Wrapper
 *
 *  Created for static library integration
 *  Non-blocking API for integration into existing iOS apps
 */

#import <UIKit/UIKit.h>
#include <stdint.h>

//! Project version number for SkyEmu.
FOUNDATION_EXPORT double SkyEmuVersionNumber;

//! Project version string for SkyEmu.
FOUNDATION_EXPORT const unsigned char SkyEmuVersionString[];

#ifdef __cplusplus
extern "C" {
#endif

// System types
typedef enum {
    SE_SYSTEM_GB = 0,
    SE_SYSTEM_GBA = 1,
    SE_SYSTEM_NDS = 2
} se_system_t;

// Run modes
typedef enum {
    SE_MODE_STOPPED = 0,
    SE_MODE_PAUSED = 1,
    SE_MODE_RUNNING = 2,
    SE_MODE_STEP = 3
} se_run_mode_t;

// Button indices
typedef enum {
    SE_BUTTON_A = 0,
    SE_BUTTON_B = 1,
    SE_BUTTON_X = 2,
    SE_BUTTON_Y = 3,
    SE_BUTTON_UP = 4,
    SE_BUTTON_DOWN = 5,
    SE_BUTTON_LEFT = 6,
    SE_BUTTON_RIGHT = 7,
    SE_BUTTON_L = 8,
    SE_NUM_BUTTONS = 9
} se_button_t;

/**
 * Initialize SkyEmu
 * Must be called from the main thread before any other functions
 * @param system System type (GB, GBA, or NDS)
 * @param window Optional UIWindow for rendering (can be NULL, uses default)
 * @return 0 on success, non-zero on failure
 */
int se_init(se_system_t system, UIWindow* window);

/**
 * Shutdown SkyEmu and free resources
 * Call this when done using SkyEmu
 */
void se_shutdown(void);

/**
 * Run one frame of emulation
 * Call this every frame from your app's render loop
 * @return YES if a frame was rendered successfully
 */
BOOL se_run_frame(void);

/**
 * Load a ROM file
 * @param path Path to ROM file
 * @return 0 on success, non-zero on failure
 */
int se_load_rom(const char* path);

/**
 * Set the current run mode
 * @param mode SE_MODE_STOPPED, SE_MODE_PAUSED, SE_MODE_RUNNING, or SE_MODE_STEP
 */
void se_set_run_mode(se_run_mode_t mode);

/**
 * Get current run mode
 * @return Current run mode
 */
se_run_mode_t se_get_run_mode(void);

/**
 * Get current system type
 * @return Current system type
 */
se_system_t se_get_system(void);

/**
 * Set audio volume
 * @param volume 0.0 to 1.0
 */
void se_set_volume(float volume);

/**
 * Get current audio volume
 * @return Volume 0.0 to 1.0
 */
float se_get_volume(void);

/**
 * Get framebuffer width in pixels
 * @return Width in pixels
 */
int se_framebuffer_width(void);

/**
 * Get framebuffer height in pixels
 * @return Height in pixels
 */
int se_framebuffer_height(void);

/**
 * Get framebuffer format string
 * @return Format string (e.g., "RGBA8888")
 */
const char* se_framebuffer_format(void);

/**
 * Get framebuffer pitch (bytes per row)
 * @return Bytes per row
 */
int se_framebuffer_pitch(void);

/**
 * Get frame counter (incremented each frame)
 * @return Frame count
 */
uint64_t se_get_frame_count(void);

/**
 * Reset emulator (soft reset)
 */
void se_reset(void);

#ifdef __cplusplus
}
#endif
