package net.nullsum.doom

import android.util.Log
import android.view.KeyEvent

import com.beloko.libsdl.SDLLib
import net.nullsum.doom.MyGLSurfaceView
import com.beloko.touchcontrols.ControlInterface

class NativeLib : ControlInterface {
    override fun quickCommand_if(command: String) {
        quickCommand(command)
    }

    override fun initTouchControls_if(pngPath: String, width: Int, height: Int) {}

    override fun touchEvent_if(action: Int, pid: Int, x: Float, y: Float): Boolean {
        return touchEvent(  action,  pid,  x,  y)
    }

    override fun keyPress_if(down: Int, qkey: Int, unicode: Int) {
        keypress(down,qkey,unicode)
    }

    override fun doAction_if(state: Int, action: Int) {
        doAction(state,action)
    }

    override fun analogFwd_if(v: Float) {
        analogFwd(v)
    }

    override fun analogSide_if(v: Float) {
        analogSide(v)
    }

    override fun analogPitch_if(mode: Int, v: Float ) {
        analogPitch(mode,v)
    }

    override fun analogYaw_if(mode: Int, v: Float) {
        analogYaw(mode,v)
    }

    override fun setTouchSettings_if(alpha: Float, strafe: Float, fwd: Float, pitch: Float, yaw: Float, other: Int) {
        setTouchSettings(alpha, strafe, fwd, pitch, yaw, other)
    }

    override fun mapKey(acode: Int, unicode: Int): Int {
        Log.d("TEST","key = " + acode + " " + unicode)

        if (unicode == 95) { //Hack to make underscore work
            return SDL_SCANCODE_POWER
        } else if ((acode >= KeyEvent.KEYCODE_A) && (acode <= KeyEvent.KEYCODE_Z)) {
            return SDL_SCANCODE_A + (acode - KeyEvent.KEYCODE_A)
        } else {
            when(acode) {
                KeyEvent.KEYCODE_TAB -> return SDL_SCANCODE_TAB
                KeyEvent.KEYCODE_DPAD_CENTER, KeyEvent.KEYCODE_ENTER -> return SDL_SCANCODE_RETURN
                KeyEvent.KEYCODE_ESCAPE, KeyEvent.KEYCODE_BACK -> return SDL_SCANCODE_ESCAPE
                KeyEvent.KEYCODE_SPACE -> return SDL_SCANCODE_SPACE
                KeyEvent.KEYCODE_DEL -> return SDL_SCANCODE_BACKSPACE
                KeyEvent.KEYCODE_DPAD_UP -> return SDL_SCANCODE_UP
                KeyEvent.KEYCODE_DPAD_DOWN -> return SDL_SCANCODE_DOWN
                KeyEvent.KEYCODE_DPAD_LEFT -> return SDL_SCANCODE_LEFT
                KeyEvent.KEYCODE_DPAD_RIGHT -> return SDL_SCANCODE_RIGHT
                KeyEvent.KEYCODE_ALT_LEFT -> return SDL_SCANCODE_A
                KeyEvent.KEYCODE_ALT_RIGHT -> return SDL_SCANCODE_RALT
                KeyEvent.KEYCODE_CTRL_LEFT -> return SDL_SCANCODE_LCTRL
                KeyEvent.KEYCODE_CTRL_RIGHT -> return SDL_SCANCODE_RCTRL
                KeyEvent.KEYCODE_SHIFT_LEFT -> return SDL_SCANCODE_LSHIFT
                KeyEvent.KEYCODE_SHIFT_RIGHT -> return SDL_SCANCODE_RSHIFT
                KeyEvent.KEYCODE_F1 -> return SDL_SCANCODE_F1
                KeyEvent.KEYCODE_F2 -> return SDL_SCANCODE_F2
                KeyEvent.KEYCODE_F3 -> return SDL_SCANCODE_F3
                KeyEvent.KEYCODE_F4 -> return SDL_SCANCODE_F4
                KeyEvent.KEYCODE_F5 -> return SDL_SCANCODE_F5
                KeyEvent.KEYCODE_F6 -> return SDL_SCANCODE_F6
                KeyEvent.KEYCODE_F7 -> return SDL_SCANCODE_F7
                KeyEvent.KEYCODE_F8 -> return SDL_SCANCODE_F8
                KeyEvent.KEYCODE_F9 -> return SDL_SCANCODE_F9
                KeyEvent.KEYCODE_F10 -> return SDL_SCANCODE_F10
                KeyEvent.KEYCODE_F11 -> return SDL_SCANCODE_F11
                KeyEvent.KEYCODE_F12 -> return SDL_SCANCODE_F12
                KeyEvent.KEYCODE_FORWARD_DEL -> return SDL_SCANCODE_DELETE
                KeyEvent.KEYCODE_INSERT -> return SDL_SCANCODE_INSERT
                KeyEvent.KEYCODE_PAGE_UP -> return SDL_SCANCODE_PAGEUP
                KeyEvent.KEYCODE_PAGE_DOWN -> return SDL_SCANCODE_PAGEDOWN
                KeyEvent.KEYCODE_MOVE_HOME -> return SDL_SCANCODE_HOME
                KeyEvent.KEYCODE_MOVE_END -> return SDL_SCANCODE_END
                KeyEvent.KEYCODE_BREAK -> return SDL_SCANCODE_PRINTSCREEN
                KeyEvent.KEYCODE_PERIOD -> return SDL_SCANCODE_PERIOD
                KeyEvent.KEYCODE_COMMA -> return SDL_SCANCODE_COMMA
                KeyEvent.KEYCODE_SLASH -> return SDL_SCANCODE_SLASH
                KeyEvent.KEYCODE_0 -> return SDL_SCANCODE_0
                KeyEvent.KEYCODE_1 -> return SDL_SCANCODE_1
                KeyEvent.KEYCODE_2 -> return SDL_SCANCODE_2
                KeyEvent.KEYCODE_3 -> return SDL_SCANCODE_3
                KeyEvent.KEYCODE_4 -> return SDL_SCANCODE_4
                KeyEvent.KEYCODE_5 -> return SDL_SCANCODE_5
                KeyEvent.KEYCODE_6 -> return SDL_SCANCODE_6
                KeyEvent.KEYCODE_7 -> return SDL_SCANCODE_7
                KeyEvent.KEYCODE_8 -> return SDL_SCANCODE_8
                KeyEvent.KEYCODE_9 -> return SDL_SCANCODE_9
                KeyEvent.KEYCODE_MINUS -> return SDL_SCANCODE_MINUS
                KeyEvent.KEYCODE_EQUALS -> return SDL_SCANCODE_EQUALS
                else -> if (unicode < 128) {return Character.toLowerCase(unicode) }
            }
        }
        return 0
    }

    companion object {
        @JvmStatic fun loadLibraries() {
            try {
                Log.i("JNI", "Trying to load libraries")
                SDLLib.loadSDL()
                System.loadLibrary("touchcontrols")
                System.loadLibrary("fmod")
                System.loadLibrary("openal")
                System.loadLibrary("gzdoom")
            } catch (ule: UnsatisfiedLinkError) {
                Log.e("JNI", "WARNING: Could not load shared library: " + ule.toString())
            }
        }

        @JvmStatic external fun init(graphics_dir: String, mem: Int, args: Array<String>, game: Int, path: String): Int
        @JvmStatic external fun setScreenSize(width: Int, height: Int)
        @JvmStatic external fun frame(): Int
        @JvmStatic external fun touchEvent(action: Int, pid: Int, x: Float, y: Float): Boolean
        @JvmStatic external fun keypress(down: Int, qkey: Int, unicode: Int)
        @JvmStatic external fun doAction(state: Int, action: Int)
        @JvmStatic external fun analogFwd(v: Float)
        @JvmStatic external fun analogSide(v: Float)
        @JvmStatic external fun analogPitch(mode: Int, v: Float)
        @JvmStatic external fun analogYaw(mode: Int, v: Float)
        @JvmStatic external fun setTouchSettings(alpha: Float, strafe: Float, fwd: Float, pitch: Float, yaw: Float, other: Int)
        @JvmStatic external fun quickCommand(command: String)

        @JvmField val KEY_PRESS: Int = 1
        @JvmField val KEY_RELEASE: Int = 0
        @JvmField val SDL_SCANCODE_A: Int = 4
        @JvmField val SDL_SCANCODE_B: Int = 5
        @JvmField val SDL_SCANCODE_C: Int = 6
        @JvmField val SDL_SCANCODE_D: Int = 7
        @JvmField val SDL_SCANCODE_E: Int = 8
        @JvmField val SDL_SCANCODE_F: Int = 9
        @JvmField val SDL_SCANCODE_G: Int = 10
        @JvmField val SDL_SCANCODE_H: Int = 11
        @JvmField val SDL_SCANCODE_I: Int = 12
        @JvmField val SDL_SCANCODE_J: Int = 13
        @JvmField val SDL_SCANCODE_K: Int = 14
        @JvmField val SDL_SCANCODE_L: Int = 15
        @JvmField val SDL_SCANCODE_M: Int = 16
        @JvmField val SDL_SCANCODE_N: Int = 17
        @JvmField val SDL_SCANCODE_O: Int = 18
        @JvmField val SDL_SCANCODE_P: Int = 19
        @JvmField val SDL_SCANCODE_Q: Int = 20
        @JvmField val SDL_SCANCODE_R: Int = 21
        @JvmField val SDL_SCANCODE_S: Int = 22
        @JvmField val SDL_SCANCODE_T: Int = 23
        @JvmField val SDL_SCANCODE_U: Int = 24
        @JvmField val SDL_SCANCODE_V: Int = 25
        @JvmField val SDL_SCANCODE_W: Int = 26
        @JvmField val SDL_SCANCODE_X: Int = 27
        @JvmField val SDL_SCANCODE_Y: Int = 28
        @JvmField val SDL_SCANCODE_Z: Int = 29
        @JvmField val SDL_SCANCODE_1: Int = 30
        @JvmField val SDL_SCANCODE_2: Int = 31
        @JvmField val SDL_SCANCODE_3: Int = 32
        @JvmField val SDL_SCANCODE_4: Int = 33
        @JvmField val SDL_SCANCODE_5: Int = 34
        @JvmField val SDL_SCANCODE_6: Int = 35
        @JvmField val SDL_SCANCODE_7: Int = 36
        @JvmField val SDL_SCANCODE_8: Int = 37
        @JvmField val SDL_SCANCODE_9: Int = 38
        @JvmField val SDL_SCANCODE_0: Int = 39
        @JvmField val SDL_SCANCODE_RETURN: Int = 40
        @JvmField val SDL_SCANCODE_ESCAPE: Int = 41
        @JvmField val SDL_SCANCODE_BACKSPACE: Int = 42
        @JvmField val SDL_SCANCODE_TAB: Int = 43
        @JvmField val SDL_SCANCODE_SPACE: Int = 44
        @JvmField val SDL_SCANCODE_MINUS: Int = 45
        @JvmField val SDL_SCANCODE_EQUALS: Int = 46
        @JvmField val SDL_SCANCODE_LEFTBRACKET: Int = 47
        @JvmField val SDL_SCANCODE_RIGHTBRACKET: Int = 48
        @JvmField val SDL_SCANCODE_COMMA: Int = 54
        @JvmField val SDL_SCANCODE_PERIOD: Int = 55
        @JvmField val SDL_SCANCODE_SLASH: Int = 56
        @JvmField val SDL_SCANCODE_CAPSLOCK: Int = 57
        @JvmField val SDL_SCANCODE_F1: Int = 58
        @JvmField val SDL_SCANCODE_F2: Int = 59
        @JvmField val SDL_SCANCODE_F3: Int = 60
        @JvmField val SDL_SCANCODE_F4: Int = 61
        @JvmField val SDL_SCANCODE_F5: Int = 62
        @JvmField val SDL_SCANCODE_F6: Int = 63
        @JvmField val SDL_SCANCODE_F7: Int = 64
        @JvmField val SDL_SCANCODE_F8: Int = 65
        @JvmField val SDL_SCANCODE_F9: Int = 66
        @JvmField val SDL_SCANCODE_F10: Int = 67
        @JvmField val SDL_SCANCODE_F11: Int = 68
        @JvmField val SDL_SCANCODE_F12: Int = 69
        @JvmField val SDL_SCANCODE_PRINTSCREEN: Int = 70
        @JvmField val SDL_SCANCODE_SCROLLLOCK: Int = 71
        @JvmField val SDL_SCANCODE_PAUSE: Int = 72
        @JvmField val SDL_SCANCODE_INSERT: Int = 73
        @JvmField val SDL_SCANCODE_HOME: Int = 74
        @JvmField val SDL_SCANCODE_PAGEUP: Int = 75
        @JvmField val SDL_SCANCODE_DELETE: Int = 76
        @JvmField val SDL_SCANCODE_END: Int = 77
        @JvmField val SDL_SCANCODE_PAGEDOWN: Int = 78
        @JvmField val SDL_SCANCODE_RIGHT: Int = 79
        @JvmField val SDL_SCANCODE_LEFT: Int = 80
        @JvmField val SDL_SCANCODE_DOWN: Int = 81
        @JvmField val SDL_SCANCODE_UP: Int = 82
        @JvmField val SDL_SCANCODE_POWER: Int = 102// Hack this is overridden to give an underscore instead
        @JvmField val SDL_SCANCODE_LCTRL: Int = 224
        @JvmField val SDL_SCANCODE_LSHIFT: Int = 225
        @JvmField val SDL_SCANCODE_LALT: Int = 226 /**< alt option */
        @JvmField val SDL_SCANCODE_LGUI: Int = 227 /**< windows command (apple) meta */
        @JvmField val SDL_SCANCODE_RCTRL: Int = 228
        @JvmField val SDL_SCANCODE_RSHIFT: Int = 229
        @JvmField val SDL_SCANCODE_RALT: Int = 230 /**< alt gr option */

        lateinit var gv: MyGLSurfaceView

        @JvmStatic fun swapBuffers() {
            var canDraw: Boolean = false
            do {
                gv.swapBuffers()
                canDraw = gv.setupSurface()
            } while (!canDraw)
        }
    }
}
