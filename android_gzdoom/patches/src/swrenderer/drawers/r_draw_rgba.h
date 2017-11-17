--- gzdoom/src/swrenderer/drawers/r_draw_rgba.h	2017-11-16 12:03:20.000000000 -0600
+++ gzdoom_android/src/swrenderer/drawers/r_draw_rgba.h	2017-11-17 15:44:51.394541211 -0600
@@ -31,7 +31,8 @@
 #include "swrenderer/viewport/r_spritedrawer.h"
 
 #ifndef NO_SSE
-#include <immintrin.h>
+#define NO_SSE
+//#include <immintrin.h>
 #endif
 
 struct FSpecialColormap;
