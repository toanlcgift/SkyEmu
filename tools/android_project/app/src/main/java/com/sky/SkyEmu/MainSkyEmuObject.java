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

    public SkyEmuSurfaceView view;
    private Activity activity;
    public Rect visibleRect = new Rect();
    private Vector<Integer> keyboardEvents = new Vector<>();
    private EditText invisibleEditText;
    private View mRootView;

    //@Override
    public void onCreate(Bundle savedInstanceState, Activity activity) {

        NativeBridge.initialize(activity);

        view = new SkyEmuSurfaceView(activity);
    }

    public void requestPermissions() {
    }

    public float getDPIScale(){
        DisplayMetrics metrics = activity.getResources().getDisplayMetrics();
        activity.getWindowManager().getDefaultDisplay().getRealMetrics(metrics);
        return metrics.xdpi/120.0f;
    }

    public float getVisibleBottom(){
        return visibleRect.bottom;
    }

    public float getVisibleTop(){
        return visibleRect.top;
    }

    public void showKeyboard(){
    }

    public void hideKeyboard()
    {
    }

    public void pollKeyboard(){
        // simplified version or copy from EnhancedNativeActivity if needed
    }

    public int getEvent(){
        if(keyboardEvents.isEmpty())return -1;
        int val = keyboardEvents.get(0);
        keyboardEvents.remove(0);
        return val;
    }

    public void openCustomTab(String url){
        CustomTabsIntent authIntent = new CustomTabsIntent.Builder().build();
        authIntent.intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
        authIntent.launchUrl(activity, Uri.parse(url));
    }

    public void openFile(){
        Intent intent = new Intent(Intent.ACTION_OPEN_DOCUMENT);
        intent.setType("*/*");
        activity.startActivityForResult(intent, 123);
    }

    public static String getLanguage() {
        return Locale.getDefault().toString();
    }

    public native void se_android_load_file(String filePath);
    public native void se_android_load_rom(String filePath);
    public native void se_android_load_html(String filePath);
    public native void se_android_show_ui(boolean isShow);
    public native void se_android_stretch_on();
    public native void se_android_stretch_off();
    public native void se_android_capture_state_slot(int slot);
    public native void se_android_restore_state_slot(int slot);


    public void onResume() {
        NativeBridge.resume();
    }

    public void onPause() {
        NativeBridge.pause();
    }

    public void onDestroy() {
        NativeBridge.destroy();
    }

    public void onWindowFocusChanged(boolean hasFocus) {
        NativeBridge.focusChanged(hasFocus);
    }

    public void onLowMemory() {
        NativeBridge.lowMemory();
    }

    public void onConfigurationChanged(Configuration newConfig) {
        NativeBridge.configurationChanged();
    }
}