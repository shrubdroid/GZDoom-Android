--- gzdoom/src/zstrformat.cpp	2017-11-20 12:23:26.000000000 -0600
+++ gzdoom_android/src/zstrformat.cpp	2017-11-21 08:37:40.000000000 -0600
@@ -693,7 +693,11 @@
 			dblarg = va_arg(arglist, double);
 			obuff = dtoaresult = dtoa(dblarg, type != 'H' ? (expchar ? 2 : 3) : 0, precision, &expt, &signflag, &dtoaend);
 //fp_common:
-			decimal_point = localeconv()->decimal_point;
+#ifdef __ANDROID__
+			decimal_point = '.';
+#else
+      decimal_point = localeconv()->decimal_point;
+#endif
 			flags |= F_SIGNED;
 			if (signflag)
 			{
@@ -1053,9 +1057,13 @@
 {
 	va_list argptr;
 	va_start(argptr, format);
+#ifdef __ANDROID__
+  return vsnprintf(buffer,count,format,argptr);
+#else
 	int len = myvsnprintf(buffer, count, format, argptr);
 	va_end(argptr);
 	return len;
+#endif
 }
 
 }
