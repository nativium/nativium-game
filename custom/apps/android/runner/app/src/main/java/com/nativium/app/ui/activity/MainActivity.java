package com.nativium.app.ui.activity;

import android.util.DisplayMetrics;

import com.nativium.djinni.JNILoader;

import org.libsdl.app.SDLActivity;

public class MainActivity extends SDLActivity {
    @Override
    protected String[] getArguments() {
        DisplayMetrics metrics = new DisplayMetrics();
        getWindowManager().getDefaultDisplay().getMetrics(metrics);

        int width = metrics.widthPixels;
        int height = metrics.heightPixels;

        return new String[]{String.valueOf(width), String.valueOf(height)};
    }

    @Override
    protected String[] getLibraries() {
        return new String[]{
            "nativium"
        };
    }

    @Override
    public void loadLibraries() {
        super.loadLibraries();
        JNILoader.load();
    }
}
