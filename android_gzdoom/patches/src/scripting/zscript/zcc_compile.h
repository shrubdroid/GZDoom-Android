--- gzdoom/src/scripting/zscript/zcc_compile.h	2017-11-17 17:53:39.252185871 -0600
+++ gzdoom_android/src/scripting/zscript/zcc_compile.h	2017-11-17 23:08:00.862077503 -0600
@@ -1,6 +1,22 @@
 #ifndef ZCC_COMPILE_H
 #define ZCC_COMPILE_H
 
+/* from tools/re2c/src/util/c99_stdint.h --shrub */
+// C99-7.18.2.1 Limits of exact-width integer types
+#define INT8_MIN   (-128)                 // -2^(8 - 1)
+#define INT8_MAX   127                    //  2^(8 - 1) - 1
+#define INT16_MIN  (-32768)               // -2^(16 - 1)
+#define INT16_MAX  32767                  //  2^(16 - 1) - 1
+#define INT32_MIN  (-2147483648)          // -2^(32 - 1)
+#define INT32_MAX  2147483647             //  2^(32 - 1) - 1
+#define INT64_MIN  (-9223372036854775808) // -2^(64 - 1)
+#define INT64_MAX  9223372036854775807    //  2^(64 - 1) - 1
+#define UINT8_MAX  0xFF               // 2^8 - 1
+#define UINT16_MAX 0xFFFF             // 2^16 - 1
+#define UINT32_MAX 0xFFFFffff         // 2^32 - 1
+#define UINT64_MAX 0xFFFFffffFFFFffff // 2^64 - 1
+
+
 #include <memory>
 #include "backend/codegen.h"
 
