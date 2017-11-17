--- gzdoom/src/gl/system/gl_swframebuffer.cpp	2017-11-16 12:03:20.000000000 -0600
+++ gzdoom_android/src/gl/system/gl_swframebuffer.cpp	2017-11-17 15:46:30.496152054 -0600
@@ -73,7 +73,8 @@
 #include "swrenderer/scene/r_light.h"
 
 #ifndef NO_SSE
-#include <immintrin.h>
+#define NO_SSE
+//#include <immintrin.h>
 #endif
 
 CVAR(Int, gl_showpacks, 0, 0)
