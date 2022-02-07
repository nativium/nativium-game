package com.nativium.app.main

import android.os.StrictMode
import androidx.appcompat.app.AppCompatDelegate
import androidx.multidex.MultiDexApplication
import com.nativium.app.BuildConfig

class Application : MultiDexApplication() {

    override fun onCreate() {
        super.onCreate()

        instance = this

        initializeStrictMode()

        AppCompatDelegate.setCompatVectorFromResourcesEnabled(true)
    }

    private fun initializeStrictMode() {
        if (BuildConfig.DEBUG) {
            StrictMode.setThreadPolicy(
                StrictMode.ThreadPolicy.Builder()
                    .detectAll()
                    .penaltyLog()
                    .build()
            )

            StrictMode.setVmPolicy(
                StrictMode.VmPolicy.Builder()
                    .detectLeakedSqlLiteObjects()
                    .detectLeakedClosableObjects()
                    .penaltyLog()
                    .build()
            )
        }
    }

    companion object {
        lateinit var instance: Application
            private set
    }
}
