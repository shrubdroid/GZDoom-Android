*** doom/src/main/jni/gzdoom/src/gl/system/gl_load.c	2017-06-25 16:06:20.524613865 -0400
--- doom/src/main/jni/Doom/gzdoom_2/src/gl/system/gl_load.c	2017-06-25 16:29:25.176591580 -0400
***************
*** 89,94 ****
--- 89,98 ----
  	#else
  		#if defined(__sgi) || defined(__sun)
  			#define IntGetProcAddress(name) SunGetProcAddress(name)
+         #elif defined __ANDROID__
+ 		    #include <EGL/egl.h>
+ 
+ 			#define IntGetProcAddress(name) (*eglGetProcAddress)(name)
  		#else /* GLX */
  		    #include <GL/glx.h>
  
