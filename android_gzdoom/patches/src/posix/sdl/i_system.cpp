--- gzdoom/src/posix/sdl/i_system.cpp	2017-11-17 17:53:39.238852612 -0600
+++ gzdoom_android/src/posix/sdl/i_system.cpp	2017-11-18 21:07:33.515106833 -0600
@@ -151,6 +151,13 @@
 	I_InitTimer ();
 }
 
+#ifdef __ANDROID__
+extern "C"
+{
+  void appShutdown();
+}
+#endif
+
 //
 // I_Quit
 //
@@ -158,11 +165,16 @@
 
 void I_Quit (void)
 {
+  LOGI("I_Quit");
     has_exited = 1;		/* Prevent infinitely recursive exits -- killough */
 
     if (demorecording)
 		G_CheckDemoStatus();
 
+#ifdef __ANDROID__
+    appShutdown();
+#endif
+
 	C_DeinitConsole();
 
 	I_ShutdownTimer();
@@ -183,6 +195,7 @@
 {
     static bool alreadyThrown = false;
     gameisdead = true;
+    LOGI("I_FatalError");
 
     if (!alreadyThrown)		// ignore all but the first message -- killough
     {
@@ -193,6 +206,7 @@
 		va_start (argptr, error);
 		index = vsnprintf (errortext, MAX_ERRORTEXT, error, argptr);
 		va_end (argptr);
+    LOGI("I_FatalError: %s", errortext);
 
 #ifdef __APPLE__
 		Mac_I_FatalError(errortext);
@@ -211,6 +225,7 @@
 
     if (!has_exited)	// If it hasn't exited yet, exit now -- killough
     {
+      LOGI("Fatal exit");
 		has_exited = 1;	// Prevent infinitely recursive exits -- killough
 		exit(-1);
     }
@@ -225,6 +240,8 @@
     vsprintf (errortext, error, argptr);
     va_end (argptr);
 
+    LOGI("Error: %s", errortext);
+
     throw CRecoverableError (errortext);
 }
 
@@ -271,7 +288,7 @@
 		return defaultiwad;
 	}
 
-#ifndef __APPLE__
+#if !defined(__APPLE__) && !defined(__ANDROID__)
 	const char *str;
 	if((str=getenv("KDE_FULL_SESSION")) && strcmp(str, "true") == 0)
 	{
