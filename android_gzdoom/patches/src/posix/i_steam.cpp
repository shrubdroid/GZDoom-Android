--- gzdoom/src/posix/i_steam.cpp	2017-11-20 12:23:26.000000000 -0600
+++ gzdoom_android/src/posix/i_steam.cpp	2017-11-21 13:14:01.221981403 -0600
@@ -196,6 +196,18 @@
 	}
 
 	SteamInstallFolders.Push(appSupportPath + "/Steam/SteamApps/common");
+#elif defined(__ANDROID__)
+  FString regPath = "./config/config.vdf";
+  try
+  {
+    SteamInstallFolders = ParseSteamRegistry(regPath);
+  }
+  catch (class CDoomError &error)
+  {
+    return result;
+  }
+
+  SteamInstallFolders.Push(regPath);
 #else
 	char* home = getenv("HOME");
 	if(home != NULL && *home != '\0')
