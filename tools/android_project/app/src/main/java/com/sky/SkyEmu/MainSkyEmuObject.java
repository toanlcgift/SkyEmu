package com.sky.SkyEmu;

import android.app.Activity;
import android.content.Intent;
import android.content.res.Configuration;
import android.graphics.Rect;
import android.net.Uri;
import android.os.Bundle;
import android.util.DisplayMetrics;
import android.view.View;
import android.widget.EditText;

import androidx.browser.customtabs.CustomTabsIntent;

import java.util.Locale;
import java.util.Vector;

public class MainSkyEmuObject {
    public void initialize(Bundle savedInstanceState, Activity activity) {
        NativeBridge.initialize(activity);
    }

    public native void se_android_load_file(String filePath);
    public native void se_android_load_rom(String filePath);
    public native void se_android_load_html(String filePath);
    public native void se_android_show_ui(boolean isShow);
    public native void se_android_stretch_on();
    public native void se_android_stretch_off();
    public native void se_android_capture_state_slot(int slot);
    public native void se_android_restore_state_slot(int slot);
    public native void se_android_send_key(String key, float value);
    public native void se_android_set_screen_shader(int shaderMode);
    public native int se_android_get_screen_shader();

    /* ---- Volume / Theme / Display ---- */
    public native void se_android_set_volume(float volume);
    public native float se_android_get_volume();
    public native void se_android_set_theme(int theme);
    public native int se_android_get_theme();
    public native void se_android_set_integer_scaling(int value);
    public native int se_android_get_integer_scaling();
    public native void se_android_set_screen_rotation(int rotation);
    public native int se_android_get_screen_rotation();
    public native void se_android_set_stretch_to_fit(int value);
    public native int se_android_get_stretch_to_fit();

    /* ---- GB Palette (index 0-3) ---- */
    public native void se_android_set_gb_palette(int index, int color);
    public native int se_android_get_gb_palette(int index);

    /* ---- Visual Effects ---- */
    public native void se_android_set_ghosting(float ghosting);
    public native float se_android_get_ghosting();
    public native void se_android_set_color_correction(float value);
    public native float se_android_get_color_correction();

    /* ---- Touch Controls ---- */
    public native void se_android_set_auto_hide_touch_controls(int value);
    public native int se_android_get_auto_hide_touch_controls();
    public native void se_android_set_touch_controls_opacity(float opacity);
    public native float se_android_get_touch_controls_opacity();
    public native void se_android_set_touch_controls_scale(float scale);
    public native float se_android_get_touch_controls_scale();
    public native void se_android_set_touch_controls_show_turbo(int value);
    public native int se_android_get_touch_controls_show_turbo();
    public native void se_android_set_avoid_overlapping_touchscreen(int value);
    public native int se_android_get_avoid_overlapping_touchscreen();
    public native void se_android_set_touch_screen_show_button_labels(int value);
    public native int se_android_get_touch_screen_show_button_labels();

    /* ---- UI / Menubar ---- */
    public native void se_android_set_always_show_menubar(int value);
    public native int se_android_get_always_show_menubar();
    public native void se_android_set_gui_scale_factor(float scale);
    public native float se_android_get_gui_scale_factor();
    public native void se_android_set_custom_font_scale(float scale);
    public native float se_android_get_custom_font_scale();

    /* ---- Emulation Options ---- */
    public native void se_android_set_force_dmg_mode(int value);
    public native int se_android_get_force_dmg_mode();
    public native void se_android_set_gba_color_correction_mode(int mode);
    public native int se_android_get_gba_color_correction_mode();
    public native void se_android_set_save_to_path(int value);
    public native int se_android_get_save_to_path();
    public native void se_android_set_nds_layout(int layout);
    public native int se_android_get_nds_layout();
    public native void se_android_set_show_screen_bezel(int value);
    public native int se_android_get_show_screen_bezel();

    /* ---- Language ---- */
    public native void se_android_set_language(int language);
    public native int se_android_get_language();

    /* ---- HTTP Control Server ---- */
    public native void se_android_set_http_control_server_enable(int value);
    public native int se_android_get_http_control_server_enable();
    public native void se_android_set_http_control_server_port(int port);
    public native int se_android_get_http_control_server_port();

    /* ---- RetroAchievements ---- */
    public native void se_android_set_hardcore_mode(int value);
    public native int se_android_get_hardcore_mode();
    public native void se_android_set_draw_challenge_indicators(int value);
    public native int se_android_get_draw_challenge_indicators();
    public native void se_android_set_draw_progress_indicators(int value);
    public native int se_android_get_draw_progress_indicators();
    public native void se_android_set_draw_leaderboard_trackers(int value);
    public native int se_android_get_draw_leaderboard_trackers();
    public native void se_android_set_draw_notifications(int value);
    public native int se_android_get_draw_notifications();
    public native void se_android_set_only_one_notification(int value);
    public native int se_android_get_only_one_notification();

    /* ---- Misc ---- */
    public native void se_android_set_enable_download_cache(int value);
    public native int se_android_get_enable_download_cache();
    public native void se_android_set_draw_debug_menu(int value);
    public native int se_android_get_draw_debug_menu();
}