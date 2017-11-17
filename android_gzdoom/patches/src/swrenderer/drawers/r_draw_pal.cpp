--- gzdoom/src/swrenderer/drawers/r_draw_pal.cpp	2017-11-16 12:03:20.000000000 -0600
+++ gzdoom_android/src/swrenderer/drawers/r_draw_pal.cpp	2017-11-17 15:45:52.789669332 -0600
@@ -34,7 +34,8 @@
 */
 
 #ifndef NO_SSE
-#include <xmmintrin.h>
+#define NO_SSE
+//#include <xmmintrin.h>
 #endif
 #include "templates.h"
 #include "doomtype.h"
