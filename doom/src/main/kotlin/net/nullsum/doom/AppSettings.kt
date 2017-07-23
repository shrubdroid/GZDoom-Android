package net.nullsum.doom

import android.content.Context
import android.content.SharedPreferences
import android.os.Environment

import com.beloko.touchcontrols.TouchSettings

import java.io.File
import java.io.IOException

class AppSettings {
    companion object {
        @JvmField var gzdoomBaseDir: String = ""
        @JvmField var graphicsDir: String = ""

        @JvmStatic fun resetBaseDir(ctx: Context) {
            AppSettings.gzdoomBaseDir = Environment.getExternalStorageDirectory().toString() + "/GZDoom"
            setStringOption(ctx, "base_path", AppSettings.gzdoomBaseDir)
        }

        @JvmStatic fun reloadSettings(ctx: Context) {
            TouchSettings.reloadSettings(ctx)
            AppSettings.gzdoomBaseDir = getStringOption(ctx, "base_path")
            AppSettings.graphicsDir = ctx.getFilesDir().toString() + "/"
        }

        @JvmStatic fun getFullDir(): String {
            return AppSettings.gzdoomBaseDir + "/config"
        }

        @JvmStatic fun createDirectories(ctx: Context) {
            var scan: Boolean = false

            var d: String = ""
            if (!File(getFullDir() + d).exists())
                scan = true

            File(getFullDir() + d).mkdirs()

            //This is totally stupid, need to do this so folder shows up in explorer!
            if (scan)
            {
                var f: File = File(getFullDir() + d , "temp_")
                try {
                    f.createNewFile()
                } catch (e: IOException) {
                    e.printStackTrace()
                }
            }
            else
            {
                File(getFullDir() + d , "temp_").delete()
            }
        }

        @JvmStatic fun getIntOption(ctx: Context, name: String, def: Int): Int {
            var settings: SharedPreferences = ctx.getSharedPreferences("OPTIONS", Context.MODE_MULTI_PROCESS)
            return settings.getInt(name, def)
        }

        @JvmStatic fun setIntOption(ctx: Context, name: String, value: Int) {
            var settings: SharedPreferences = ctx.getSharedPreferences("OPTIONS", Context.MODE_MULTI_PROCESS)
            var editor: SharedPreferences.Editor = settings.edit()
            editor.putInt(name, value)
            editor.apply()
        }

        @JvmStatic fun getStringOption(ctx: Context, name: String): String {
            var settings: SharedPreferences = ctx.getSharedPreferences("OPTIONS", Context.MODE_MULTI_PROCESS)
            return settings.getString(name, name)
        }

        @JvmStatic fun setStringOption(ctx: Context, name: String, value: String) {
            var settings: SharedPreferences = ctx.getSharedPreferences("OPTIONS", Context.MODE_MULTI_PROCESS)
            var editor: SharedPreferences.Editor = settings.edit()
            editor.putString(name, value)
            editor.apply()
        }
    }
}
