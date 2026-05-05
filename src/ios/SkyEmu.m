/*
 *  SkyEmu.m
 *  SkyEmu iOS Wrapper Implementation
 *  Non-blocking API for integration into existing iOS apps
 */

#include "ios/SkyEmu.h"
#include "../shared.h"

// External declarations from main.c
extern sb_emu_state_t emu_state;
extern sb_gui_state_t gui_state;

// Global state for non-blocking operation
static BOOL g_initialized = NO;
static se_system_t g_system = SE_SYSTEM_GB;
static BOOL g_use_default_window = YES;

// Initialize SkyEmu
int se_init(se_system_t system, UIWindow* window) {
    if (g_initialized) {
        return 0; // Already initialized
    }
    
    g_system = system;
    
    // Initialize sokol_gfx
    sg_setup(&(sg_desc){
        .context = sapp_sgcontext()
    });
    
    // Initialize sokol_audio
    saudio_setup(&(saudio_desc){ NULL });
    
    // Initialize sokol_imgui
    simgui_setup(&(simgui_desc_t){ .dpi_scale = se_dpi_scale() });
    
    // Initialize SkyEmu audio
    se_init_audio();
    
    // Set UI type to iOS
    gui_state.ui_type = SE_UI_IOS;
    
    // Initialize keyboard bindings
    se_initialize_keybind(&gui_state.key);
    
    // Initial clear color
    gui_state.pass_action = (sg_pass_action) {
        .colors[0] = { .action = SG_ACTION_CLEAR, .value = {0, 0, 0, 1} }
    };
    
    // Initialize touch time
    gui_state.last_touch_time = -10000;
    
    // Set default volume
    gui_state.settings.volume = 1.0f;
    
    g_initialized = YES;
    
    return 0;
}

// Shutdown SkyEmu
void se_shutdown(void) {
    if (!g_initialized) {
        return;
    }
    
    simgui_shutdown();
    se_free_all_images();
    sg_shutdown();
    saudio_shutdown();
    
    g_initialized = NO;
}

// Run one frame of emulation
BOOL se_run_frame(void) {
    if (!g_initialized) {
        return NO;
    }
    
    // Reset HTML click regions
    se_reset_html_click_regions();
    
    // Get frame time
    static sb_stm_laptime_t laptime = {0};
    const double delta_time = stm_sec(stm_round_to_common_refresh_rate(stm_laptime(&laptime)));
    
    // Update GUI state
    gui_state.laptime = laptime;
    gui_state.screen_width = sapp_width();
    gui_state.screen_height = sapp_height();
    
    // Begin rendering
    sg_begin_default_pass(&gui_state.pass_action, gui_state.screen_width, gui_state.screen_height);
    
    // Update imgui frame
    simgui_new_frame(gui_state.screen_width, gui_state.screen_height, delta_time);
    
    // Set imgui theme
    se_imgui_theme();
    
    // Apply iOS safe area padding
    float top_padding = 0, left_padding = 0;
#ifdef SE_PLATFORM_IOS
    se_ios_get_safe_ui_padding(&top_padding, NULL, &left_padding, NULL);
    ImGuiStyle* style = igGetStyle();
    style->DisplaySafeAreaPadding.x = left_padding;
    style->DisplaySafeAreaPadding.y = top_padding;
#endif
    
    // Poll controller input
    sb_poll_controller_input(&emu_state.joy);
    
    // Draw UI and emulation output
    // The actual emulation rendering happens in the frame_cb which calls frame()
    
    // End rendering
    sg_end_pass();
    sg_commit();
    
    return YES;
}

// Load a ROM file
int se_load_rom(const char* path) {
    if (!g_initialized) {
        return -1;
    }
    
    ::se_load_rom(path);
    return (emu_state.rom_loaded ? 0 : -1);
}

// Set run mode
void se_set_run_mode(se_run_mode_t mode) {
    emu_state.run_mode = (int)mode;
}

// Get run mode
se_run_mode_t se_get_run_mode(void) {
    return (se_run_mode_t)emu_state.run_mode;
}

// Get system type
se_system_t se_get_system(void) {
    return g_system;
}

// Set volume
void se_set_volume(float volume) {
    gui_state.settings.volume = volume;
}

// Get volume
float se_get_volume(void) {
    return gui_state.settings.volume;
}

// Framebuffer width
int se_framebuffer_width(void) {
    switch (g_system) {
        case SE_SYSTEM_GB:
            return 160;
        case SE_SYSTEM_GBA:
            return 240;
        case SE_SYSTEM_NDS:
            return 256;
        default:
            return 240;
    }
}

// Framebuffer height
int se_framebuffer_height(void) {
    switch (g_system) {
        case SE_SYSTEM_GB:
            return 144;
        case SE_SYSTEM_GBA:
            return 160;
        case SE_SYSTEM_NDS:
            return 192;
        default:
            return 160;
    }
}

// Framebuffer format
const char* se_framebuffer_format(void) {
    return "RGBA8888";
}

// Framebuffer pitch
int se_framebuffer_pitch(void) {
    return se_framebuffer_width() * 4;
}

// Get frame count
uint64_t se_get_frame_count(void) {
    return 0; // TODO: expose frame counter
}

// Reset emulator
void se_reset(void) {
    emu_state.run_mode = SB_MODE_RESET;
}
