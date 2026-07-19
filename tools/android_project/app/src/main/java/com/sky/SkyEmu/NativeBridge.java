package com.sky.SkyEmu;

import android.view.Surface;

public class NativeBridge {
    static {
        System.loadLibrary("SkyEmu");
    }

    public static native void setSurface(Surface surface);
}
