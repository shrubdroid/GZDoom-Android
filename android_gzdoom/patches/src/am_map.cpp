--- gzdoom/src/am_map.cpp	2017-11-20 12:23:26.000000000 -0600
+++ gzdoom_android/src/am_map.cpp	2017-11-21 10:00:56.000000000 -0600
@@ -1592,6 +1592,10 @@
 	}
 }
 
+#ifdef __ANDROID__
+extern void Android_AM_controls(double *zoom, double *pan_x, double *pan_y);
+#endif
+
 //=============================================================================
 //
 // Updates on Game Tick
@@ -1618,6 +1622,10 @@
 		if (Button_AM_PanDown.bDown) m_paninc.y -= FTOM(F_PANINC);
 	}
 
+#ifdef __ANDROID__
+  Android_AM_controls(&am_zoomdir, &m_paninc.x, &m_paninc.y);
+#endif
+
 	// Change the zoom if necessary
 	if (Button_AM_ZoomIn.bDown || Button_AM_ZoomOut.bDown || am_zoomdir != 0)
 		AM_changeWindowScale();
