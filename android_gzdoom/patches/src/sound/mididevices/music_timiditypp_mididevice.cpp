--- gzdoom/src/sound/mididevices/music_timiditypp_mididevice.cpp	2017-11-17 17:53:39.252185871 -0600
+++ gzdoom_android/src/sound/mididevices/music_timiditypp_mididevice.cpp	2017-11-17 23:52:48.488564931 -0600
@@ -48,7 +48,11 @@
 
 #include <sys/types.h>
 #include <sys/wait.h>
+
+#ifndef __ANDROID__
 #include <wordexp.h>
+#endif
+
 #include <glob.h>
 #include <signal.h>
 
@@ -533,16 +537,20 @@
 	}
 
 	int forkres;
+  #ifndef __ANDROID__
 	wordexp_t words;
 	glob_t glb;
+  #endif
 
 	// Get timidity executable path
 	const char *exename = "timidity"; // Fallback default
+  #ifndef __ANDROID__
 	glob(ExeName.GetChars(), 0, NULL, &glb);
 	if(glb.gl_pathc != 0)
 		exename = glb.gl_pathv[0];
 	// Get user-defined extra args
 	wordexp(timidity_extargs, &words, WRDE_NOCMD);
+  #endif
 
 	std::string chorusarg = std::string("-EFchorus=") + *timidity_chorus;
 	std::string reverbarg = std::string("-EFreverb=") + *timidity_reverb;
@@ -557,8 +565,10 @@
 
 	std::vector<const char*> arglist;
 	arglist.push_back(exename);
+  #ifndef __ANDROID__
 	for(size_t i = 0;i < words.we_wordc;i++)
 		arglist.push_back(words.we_wordv[i]);
+  #endif
 	if(**timidity_config != '\0')
 	{
 		arglist.push_back("-c");
@@ -611,8 +621,10 @@
 		}*/
 	}
 
+  #ifndef __ANDROID__
 	wordfree(&words);
 	globfree (&glb);
+  #endif
 	return ChildProcess != -1;
 #endif // _WIN32
 }
