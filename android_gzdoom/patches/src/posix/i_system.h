--- gzdoom/src/posix/i_system.h	2017-11-17 17:53:39.235519297 -0600
+++ gzdoom_android/src/posix/i_system.h	2017-11-18 21:10:59.890575183 -0600
@@ -27,6 +27,14 @@
 #ifndef __I_SYSTEM__
 #define __I_SYSTEM__
 
+#include <android/log.h>
+
+#ifndef LOGI
+#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "JNI", __VA_ARGS__))
+#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "JNI", __VA_ARGS__))
+#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "JNI", __VA_ARGS__))
+#endif
+
 #include <dirent.h>
 #include <ctype.h>
 
