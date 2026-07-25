package com.sky.SkyEmu;

import android.view.Surface;
import android.app.Activity;

public final class NativeBridge {

    static {
        System.loadLibrary("SkyEmu");
    }

    private NativeBridge() {
    }

    public static native void initialize(Activity activity);

    public static native void destroy();

    public static native void resume();

    public static native void pause();

    public static native void focusChanged(boolean focused);

    public static native void setSurface(Surface surface);

    public static native void surfaceChanged(
            int width,
            int height);

    public static native void lowMemory();

    public static native void configurationChanged();
}
