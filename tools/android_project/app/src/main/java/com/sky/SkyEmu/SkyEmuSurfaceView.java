package com.sky.SkyEmu;
import android.content.Context;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

public class SkyEmuSurfaceView
        extends SurfaceView
        implements SurfaceHolder.Callback {

    public SkyEmuSurfaceView(Context context) {
        super(context);

        getHolder().addCallback(this);

        setFocusable(true);
        setFocusableInTouchMode(true);
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        NativeBridge.setSurface(holder.getSurface());
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        NativeBridge.setSurface(null);
    }

    @Override
    public void surfaceChanged(
            SurfaceHolder holder,
            int format,
            int width,
            int height) {

        NativeBridge.surfaceChanged(width, height);
    }
}
