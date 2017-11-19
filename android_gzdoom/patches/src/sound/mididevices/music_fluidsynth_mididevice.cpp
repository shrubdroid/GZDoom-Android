--- gzdoom/src/sound/mididevices/music_fluidsynth_mididevice.cpp	2017-11-17 17:53:39.252185871 -0600
+++ gzdoom_android/src/sound/mididevices/music_fluidsynth_mididevice.cpp	2017-11-18 23:14:09.866967064 -0600
@@ -466,7 +466,9 @@
 {
 	if (len > 1 && (data[0] == 0xF0 || data[0] == 0xF7))
 	{
+#ifndef __ANDROID__
 		fluid_synth_sysex(FluidSynth, (const char *)data + 1, len - 1, NULL, NULL, NULL, 0);
+#endif
 	}
 }
 
@@ -656,7 +658,11 @@
 
 	CritSec.Enter();
 	int polyphony = fluid_synth_get_polyphony(FluidSynth);
+#ifdef __ANDROID__
+  int voices = 1;
+#else
 	int voices = fluid_synth_get_active_voice_count(FluidSynth);
+#endif
 	double load = fluid_synth_get_cpu_load(FluidSynth);
 	char *chorus, *reverb;
 	int maxpoly;
