--- gzdoom/src/textures/textures.h	2017-11-20 12:23:26.000000000 -0600
+++ gzdoom_android/src/textures/textures.h	2017-11-21 10:07:03.000000000 -0600
@@ -359,9 +359,10 @@
 
 	struct MiscGLInfo
 	{
		FMaterial *Material[2];
		FGLTexture *SystemTexture[2];
 		FTexture *Brightmap;
+    FTexture *DecalTexture;
 		PalEntry GlowColor;
 		int GlowHeight;
 		FloatRect *areas;
