--- doom/src/main/jni/gzdoom/src/posix/sdl/i_main.cpp	2017-11-17 17:53:39.238852612 -0600
+++ doom/src/main/jni/gzdoom_android/src/posix/sdl/i_main.cpp	2017-11-18 00:40:50.940511466 -0600
@@ -185,16 +185,10 @@
 void I_StartupJoysticks();
 void I_ShutdownJoysticks();
 
-int main (int argc, char **argv)
+int main_android (int argc, char **argv)
 {
-#if !defined (__APPLE__)
-	{
-		int s[4] = { SIGSEGV, SIGILL, SIGFPE, SIGBUS };
-		cc_install_handlers(argc, argv, 4, s, GAMENAMELOWERCASE "-crash.log", DoomSpecificInfo);
-	}
-#endif // !__APPLE__
 
-	printf(GAMENAME" %s - %s - SDL version\nCompiled on %s\n",
+	LOGI(GAMENAME" %s - %s - SDL version\nCompiled on %s\n",
 		GetVersionString(), GetGitTime(), __DATE__);
 
 	seteuid (getuid ());
@@ -209,7 +203,7 @@
 
 	if (SDL_Init (0) < 0)
 	{
-		fprintf (stderr, "Could not initialize SDL:\n%s\n", SDL_GetError());
+		LOGE("Could not initialize SDL:\n%s\n", SDL_GetError());
 		return -1;
 	}
 	atterm (SDL_Quit);
@@ -262,7 +256,7 @@
     {
 		I_ShutdownJoysticks();
 		if (error.GetMessage ())
-			fprintf (stderr, "%s\n", error.GetMessage ());
+			LOGE("%s\n", error.GetMessage ());
 
 #ifdef __APPLE__
 		Mac_I_FatalError(error.GetMessage());
@@ -272,6 +266,7 @@
     }
     catch (...)
     {
+      LOGI("main catch...");
 		call_terms ();
 		throw;
     }
