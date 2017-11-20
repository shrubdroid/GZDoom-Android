--- gzdoom/src/posix/unix/i_specialpaths.cpp	2017-11-20 12:23:26.658864681 -0600
+++ gzdoom_android/src/posix/unix/i_specialpaths.cpp	2017-11-20 15:51:04.638893643 -0600
@@ -38,69 +38,228 @@
 #include "i_system.h"
 #include "cmdlib.h"
 
-#include "version.h"	// for GAMENAME
+#include "version.h"  // for GAMENAME
 
+#ifdef __ANDROID__
+FString GetUserFile (const char *file)
+{
+  FString path;
+  struct stat info;
+
+  path = NicePath("./gzdoom/");
+
+  if (stat (path, &info) == -1)
+  {
+    struct stat extrainfo;
+
+    // Sanity check for ~/.config
+    FString configPath = NicePath("./gzdoom");
+    if (stat (configPath, &extrainfo) == -1)
+    {
+      if (mkdir (configPath, S_IRUSR | S_IWUSR | S_IXUSR) == -1)
+      {
+        I_FatalError ("Failed to create ./gzdoom directory:\n%s", strerror(errno));
+      }
+    }
+    else if (!S_ISDIR(extrainfo.st_mode))
+    {
+      I_FatalError ("./gzdoom must be a directory");
+    }
+
+    // This can be removed after a release or two
+    // Transfer the old zdoom directory to the new location
+    bool moved = false;
+    FString oldpath = NicePath("./gzdoom_dev/");
+    if (stat (oldpath, &extrainfo) != -1)
+    {
+      if (rename(oldpath, path) == -1)
+      {
+        I_Error ("Failed to move old gzdoom_dev directory (%s) to new location (%s).",
+          oldpath.GetChars(), path.GetChars());
+      }
+      else
+        moved = true;
+    }
+
+    if (!moved && mkdir (path, S_IRUSR | S_IWUSR | S_IXUSR) == -1)
+    {
+      I_FatalError ("Failed to create %s directory:\n%s",
+        path.GetChars(), strerror (errno));
+    }
+  }
+  else
+  {
+    if (!S_ISDIR(info.st_mode))
+    {
+      I_FatalError ("%s must be a directory", path.GetChars());
+    }
+  }
+  path += file;
+  return path;
+}
+
+//===========================================================================
+//
+// M_GetCachePath                           Unix
+//
+// Returns the path for cache GL nodes.
+//
+//===========================================================================
+
+FString M_GetCachePath(bool create)
+{
+  // Don't use GAME_DIR and such so that ZDoom and its child ports can
+  // share the node cache.
+  FString path = NicePath("./gzdoom_cache");
+  if (create)
+  {
+    CreatePath(path);
+  }
+  return path;
+}
+
+//===========================================================================
+//
+// M_GetAutoexecPath                          Unix
+//
+// Returns the expected location of autoexec.cfg.
+//
+//===========================================================================
+
+FString M_GetAutoexecPath()
+{
+  return GetUserFile("autoexec.cfg");
+}
+
+//===========================================================================
+//
+// M_GetCajunPath                           Unix
+//
+// Returns the location of the Cajun Bot definitions.
+//
+//===========================================================================
+
+FString M_GetCajunPath(const char *botfilename)
+{
+  FString path;
+
+  // Check first in ~/.config/zdoom/botfilename.
+  path = GetUserFile(botfilename);
+  if (!FileExists(path))
+  {
+    // Then check in SHARE_DIR/botfilename.
+    path = SHARE_DIR;
+    path << botfilename;
+    if (!FileExists(path))
+    {
+      path = "";
+    }
+  }
+  return path;
+}
+
+//===========================================================================
+//
+// M_GetConfigPath                            Unix
+//
+// Returns the path to the config file. On Windows, this can vary for reading
+// vs writing. i.e. If $PROGDIR/zdoom-<user>.ini does not exist, it will try
+// to read from $PROGDIR/zdoom.ini, but it will never write to zdoom.ini.
+//
+//===========================================================================
+
+FString M_GetConfigPath(bool for_reading)
+{
+  return GetUserFile("zdoom.ini");
+}
+
+//===========================================================================
+//
+// M_GetScreenshotsPath                         Unix
+//
+// Returns the path to the default screenshots directory.
+//
+//===========================================================================
+
+FString M_GetScreenshotsPath()
+{
+  return NicePath("./");
+}
+
+//===========================================================================
+//
+// M_GetSavegamesPath                         Unix
+//
+// Returns the path to the default save games directory.
+//
+//===========================================================================
+
+FString M_GetSavegamesPath()
+{
+  return NicePath("~/" GAME_DIR);
+}
 
+#else
 FString GetUserFile (const char *file)
 {
-	FString path;
-	struct stat info;
+  FString path;
+  struct stat info;
 
-	path = NicePath("~/" GAME_DIR "/");
+  path = NicePath("~/" GAME_DIR "/");
 
-	if (stat (path, &info) == -1)
-	{
-		struct stat extrainfo;
-
-		// Sanity check for ~/.config
-		FString configPath = NicePath("~/.config/");
-		if (stat (configPath, &extrainfo) == -1)
-		{
-			if (mkdir (configPath, S_IRUSR | S_IWUSR | S_IXUSR) == -1)
-			{
-				I_FatalError ("Failed to create ~/.config directory:\n%s", strerror(errno));
-			}
-		}
-		else if (!S_ISDIR(extrainfo.st_mode))
-		{
-			I_FatalError ("~/.config must be a directory");
-		}
-
-		// This can be removed after a release or two
-		// Transfer the old zdoom directory to the new location
-		bool moved = false;
-		FString oldpath = NicePath("~/." GAMENAMELOWERCASE "/");
-		if (stat (oldpath, &extrainfo) != -1)
-		{
-			if (rename(oldpath, path) == -1)
-			{
-				I_Error ("Failed to move old " GAMENAMELOWERCASE " directory (%s) to new location (%s).",
-					oldpath.GetChars(), path.GetChars());
-			}
-			else
-				moved = true;
-		}
-
-		if (!moved && mkdir (path, S_IRUSR | S_IWUSR | S_IXUSR) == -1)
-		{
-			I_FatalError ("Failed to create %s directory:\n%s",
-				path.GetChars(), strerror (errno));
-		}
-	}
-	else
-	{
-		if (!S_ISDIR(info.st_mode))
-		{
-			I_FatalError ("%s must be a directory", path.GetChars());
-		}
-	}
-	path += file;
-	return path;
+  if (stat (path, &info) == -1)
+  {
+    struct stat extrainfo;
+
+    // Sanity check for ~/.config
+    FString configPath = NicePath("~/.config/");
+    if (stat (configPath, &extrainfo) == -1)
+    {
+      if (mkdir (configPath, S_IRUSR | S_IWUSR | S_IXUSR) == -1)
+      {
+        I_FatalError ("Failed to create ~/.config directory:\n%s", strerror(errno));
+      }
+    }
+    else if (!S_ISDIR(extrainfo.st_mode))
+    {
+      I_FatalError ("~/.config must be a directory");
+    }
+
+    // This can be removed after a release or two
+    // Transfer the old zdoom directory to the new location
+    bool moved = false;
+    FString oldpath = NicePath("~/." GAMENAMELOWERCASE "/");
+    if (stat (oldpath, &extrainfo) != -1)
+    {
+      if (rename(oldpath, path) == -1)
+      {
+        I_Error ("Failed to move old " GAMENAMELOWERCASE " directory (%s) to new location (%s).",
+          oldpath.GetChars(), path.GetChars());
+      }
+      else
+        moved = true;
+    }
+
+    if (!moved && mkdir (path, S_IRUSR | S_IWUSR | S_IXUSR) == -1)
+    {
+      I_FatalError ("Failed to create %s directory:\n%s",
+        path.GetChars(), strerror (errno));
+    }
+  }
+  else
+  {
+    if (!S_ISDIR(info.st_mode))
+    {
+      I_FatalError ("%s must be a directory", path.GetChars());
+    }
+  }
+  path += file;
+  return path;
 }
 
 //===========================================================================
 //
-// M_GetCachePath														Unix
+// M_GetCachePath                           Unix
 //
 // Returns the path for cache GL nodes.
 //
@@ -108,19 +267,19 @@
 
 FString M_GetCachePath(bool create)
 {
-	// Don't use GAME_DIR and such so that ZDoom and its child ports can
-	// share the node cache.
-	FString path = NicePath("~/.config/zdoom/cache");
-	if (create)
-	{
-		CreatePath(path);
-	}
-	return path;
+  // Don't use GAME_DIR and such so that ZDoom and its child ports can
+  // share the node cache.
+  FString path = NicePath("~/.config/zdoom/cache");
+  if (create)
+  {
+    CreatePath(path);
+  }
+  return path;
 }
 
 //===========================================================================
 //
-// M_GetAutoexecPath													Unix
+// M_GetAutoexecPath                          Unix
 //
 // Returns the expected location of autoexec.cfg.
 //
@@ -128,12 +287,12 @@
 
 FString M_GetAutoexecPath()
 {
-	return GetUserFile("autoexec.cfg");
+  return GetUserFile("autoexec.cfg");
 }
 
 //===========================================================================
 //
-// M_GetCajunPath														Unix
+// M_GetCajunPath                           Unix
 //
 // Returns the location of the Cajun Bot definitions.
 //
@@ -141,26 +300,26 @@
 
 FString M_GetCajunPath(const char *botfilename)
 {
-	FString path;
+  FString path;
 
-	// Check first in ~/.config/zdoom/botfilename.
-	path = GetUserFile(botfilename);
-	if (!FileExists(path))
-	{
-		// Then check in SHARE_DIR/botfilename.
-		path = SHARE_DIR;
-		path << botfilename;
-		if (!FileExists(path))
-		{
-			path = "";
-		}
-	}
-	return path;
+  // Check first in ~/.config/zdoom/botfilename.
+  path = GetUserFile(botfilename);
+  if (!FileExists(path))
+  {
+    // Then check in SHARE_DIR/botfilename.
+    path = SHARE_DIR;
+    path << botfilename;
+    if (!FileExists(path))
+    {
+      path = "";
+    }
+  }
+  return path;
 }
 
 //===========================================================================
 //
-// M_GetConfigPath														Unix
+// M_GetConfigPath                            Unix
 //
 // Returns the path to the config file. On Windows, this can vary for reading
 // vs writing. i.e. If $PROGDIR/zdoom-<user>.ini does not exist, it will try
@@ -170,12 +329,12 @@
 
 FString M_GetConfigPath(bool for_reading)
 {
-	return GetUserFile(GAMENAMELOWERCASE ".ini");
+  return GetUserFile(GAMENAMELOWERCASE ".ini");
 }
 
 //===========================================================================
 //
-// M_GetScreenshotsPath													Unix
+// M_GetScreenshotsPath                         Unix
 //
 // Returns the path to the default screenshots directory.
 //
@@ -183,12 +342,12 @@
 
 FString M_GetScreenshotsPath()
 {
-	return NicePath("~/" GAME_DIR "/screenshots/");
+  return NicePath("~/" GAME_DIR "/screenshots/");
 }
 
 //===========================================================================
 //
-// M_GetSavegamesPath													Unix
+// M_GetSavegamesPath                         Unix
 //
 // Returns the path to the default save games directory.
 //
@@ -196,5 +355,6 @@
 
 FString M_GetSavegamesPath()
 {
-	return NicePath("~/" GAME_DIR);
+  return NicePath("~/" GAME_DIR);
 }
+#endif
