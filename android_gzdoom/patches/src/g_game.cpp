--- gzdoom/src/g_game.cpp	2017-11-20 12:23:26.000000000 -0600
+++ gzdoom_android/src/g_game.cpp	2017-11-21 09:39:44.000000000 -0600
@@ -556,6 +556,10 @@
 	}
 }
 
+#ifdef __ANDROID__
+extern void Android_IN_Move(ticcmd_t* cmd);
+#endif
+
 //
 // G_BuildTiccmd
 // Builds a ticcmd from all of the available inputs
@@ -713,6 +717,10 @@
 		forward += (int)((float)mousey * m_forward);
 	}
 
+#ifdef __ANDROID__
+  Android_IN_Move(cmd);
+#endif
+
 	cmd->ucmd.pitch = LocalViewPitch >> 16;
 
 	if (SendLand)
