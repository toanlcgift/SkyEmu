package com.sky.SkyEmu;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.res.Configuration;
import android.graphics.Rect;
import android.net.Uri;
import android.os.Bundle;
import android.util.DisplayMetrics;
import android.view.View;
import android.view.ViewTreeObserver;
import android.view.inputmethod.InputMethodManager;
import android.widget.EditText;
import android.widget.FrameLayout;

import androidx.browser.customtabs.CustomTabsIntent;

import java.util.Locale;
import java.util.Vector;

public class MainActivity extends Activity {

    private SkyEmuSurfaceView view;
    public Rect visibleRect = new Rect();
    private Vector<Integer> keyboardEvents = new Vector<>();
    private EditText invisibleEditText;
    private View mRootView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        NativeBridge.initialize(this);

        view = new SkyEmuSurfaceView(this);
        setContentView(view);

        mRootView = getWindow().getDecorView().findViewById(android.R.id.content);
        mRootView.getViewTreeObserver().addOnGlobalLayoutListener(
                new ViewTreeObserver.OnGlobalLayoutListener() {
                    public void onGlobalLayout(){
                        mRootView.getWindowVisibleDisplayFrame(visibleRect);
                    }
                });
    }

    public void requestPermissions() {
    }

    public float getDPIScale(){
        DisplayMetrics metrics = getResources().getDisplayMetrics();
        getWindowManager().getDefaultDisplay().getRealMetrics(metrics);
        return metrics.xdpi/120.0f;
    }

    public float getVisibleBottom(){
        return visibleRect.bottom;
    }

    public float getVisibleTop(){
        return visibleRect.top;
    }

    public void showKeyboard(){
        final Activity activity = this;
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if(invisibleEditText==null){
                    FrameLayout.LayoutParams mRparams = new FrameLayout.LayoutParams(FrameLayout.LayoutParams.WRAP_CONTENT, FrameLayout.LayoutParams.WRAP_CONTENT);
                    invisibleEditText = new EditText(activity);
                    invisibleEditText.setLayoutParams(mRparams);
                    ((FrameLayout)mRootView).addView(invisibleEditText);
                }
                invisibleEditText.requestFocus();
                InputMethodManager imm = (InputMethodManager) getSystemService(Context.INPUT_METHOD_SERVICE);
                imm.showSoftInput(invisibleEditText, InputMethodManager.SHOW_IMPLICIT);
            }
        });
    }

    public void hideKeyboard()
    {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if (invisibleEditText != null) {
                    ((FrameLayout) mRootView).removeView(invisibleEditText);
                    invisibleEditText = null;
                }
            }
        });
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
        authIntent.launchUrl(this, Uri.parse(url));
    }

    public void openFile(){
        Intent intent = new Intent(Intent.ACTION_OPEN_DOCUMENT);
        intent.setType("*/*");
        startActivityForResult(intent, 123);
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

    @Override
    protected void onResume() {
        super.onResume();
        NativeBridge.resume();
    }

    @Override
    protected void onPause() {
        NativeBridge.pause();
        super.onPause();
    }

    @Override
    protected void onDestroy() {
        NativeBridge.destroy();
        super.onDestroy();
    }

    @Override
    public void onWindowFocusChanged(boolean hasFocus) {
        super.onWindowFocusChanged(hasFocus);
        NativeBridge.focusChanged(hasFocus);
    }

    @Override
    public void onLowMemory() {
        super.onLowMemory();
        NativeBridge.lowMemory();
    }

    @Override
    public void onConfigurationChanged(Configuration newConfig) {
        super.onConfigurationChanged(newConfig);
        NativeBridge.configurationChanged();
    }
}