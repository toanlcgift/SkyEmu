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
}