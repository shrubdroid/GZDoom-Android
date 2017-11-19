--- gzdoom/src/sound/i_sound.cpp	2017-11-17 17:53:39.252185871 -0600
+++ gzdoom_android/src/sound/i_sound.cpp	2017-11-18 00:02:50.352275495 -0600
@@ -63,8 +63,69 @@
 #include "doomdef.h"
 
 EXTERN_CVAR (Float, snd_sfxvolume)
+
+#ifdef __ANDROID__
+
+CVAR (Int, snd_buffersize, 1024, CVAR_ARCHIVE|CVAR_GLOBALCONFIG)
+CVAR (Int, snd_buffercount, 4, CVAR_ARCHIVE|CVAR_GLOBALCONFIG)
+
+
+static void setBufferFromSampleRate(int rate)
+{
+  LOGI(("setBufferFromSampleRate"));
+  if (rate <= 22050)
+  {
+    snd_buffersize = 1024;
+    snd_buffercount = 4;
+  }
+  else if (rate <= 44100)
+  {
+    snd_buffersize = 1024;
+    snd_buffercount = 6;
+  }
+  else if(rate <= 48000)
+  {
+    snd_buffersize = 1024;
+    snd_buffercount = 8;
+  }
+  else //?
+  {
+    snd_buffersize = 1024;
+    snd_buffercount = 8;
+  }
+}
+
+extern int android_audio_rate;
+static int sample_rate_last = 0;
+CUSTOM_CVAR (Int, snd_samplerate, 0, CVAR_ARCHIVE|CVAR_GLOBALCONFIG)
+{
+  int rate = self;
+  LOGI("samplerate 1 Custom %d (last = %d)", rate,sample_rate_last);
+  
+  if (self == 0)
+  {
+    int rate = android_audio_rate;
+    setBufferFromSampleRate(rate);
+    sample_rate_last = self;
+    self = rate;
+  }
+  else if (sample_rate_last == 0)
+    sample_rate_last = self;
+  
+  
+  rate = self;
+  LOGI("samplerate 2 Custom %d (last = %d)", rate,sample_rate_last);
+  
+  if (sample_rate_last != self)
+  {
+    setBufferFromSampleRate(self);
+    sample_rate_last = self;
+  }
+}
+#else
 CVAR (Int, snd_samplerate, 0, CVAR_ARCHIVE|CVAR_GLOBALCONFIG)
 CVAR (Int, snd_buffersize, 0, CVAR_ARCHIVE|CVAR_GLOBALCONFIG)
+#endif
 CVAR (Int, snd_hrtf, -1, CVAR_ARCHIVE|CVAR_GLOBALCONFIG)
 
 #if !defined(NO_OPENAL)
