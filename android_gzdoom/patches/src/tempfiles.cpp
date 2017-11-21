--- gzdoom/src/tempfiles.cpp	2017-11-20 12:23:26.000000000 -0600
+++ gzdoom_android/src/tempfiles.cpp	2017-11-21 08:42:47.000000000 -0600
@@ -42,8 +42,12 @@
 // mkstemp should be used instead. However, there is no mkstemp
 // under VC++, and even if there was, I still need to know the
 // file name so that it can be used as input to Timidity.
-
+#ifdef __ANDROID__
+  Name = malloc(256);
+  sprintf(Name, "./gzdoom_cache/%s", prefix);
+#else
 	Name = tempnam (NULL, prefix);
+#endif
 }
 
 FTempFileName::~FTempFileName ()
