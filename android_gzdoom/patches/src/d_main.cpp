--- gzdoom/src/d_main.cpp	2017-11-20 12:23:26.000000000 -0600
+++ gzdoom_android/src/d_main.cpp	2017-11-21 09:41:03.000000000 -0600
@@ -2392,10 +2392,12 @@
 		gameinfo.ConfigName = iwad_info->Configname;
 		lastIWAD = iwad;
 
+#ifndef __ANDROID__
 		if ((gameinfo.flags & GI_SHAREWARE) && pwads.Size() > 0)
 		{
 			I_FatalError ("You cannot -file with the shareware version. Register!");
 		}
+#endif
 
 		FBaseCVar::DisableCallbacks();
 		GameConfig->DoGameSetup (gameinfo.ConfigName);
