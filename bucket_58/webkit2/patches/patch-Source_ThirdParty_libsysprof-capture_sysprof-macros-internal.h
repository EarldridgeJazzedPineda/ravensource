--- Source/ThirdParty/libsysprof-capture/sysprof-macros-internal.h.orig	2024-08-19 06:28:36 UTC
+++ Source/ThirdParty/libsysprof-capture/sysprof-macros-internal.h
@@ -64,6 +64,13 @@
 #ifdef __APPLE__
 # include <libkern/OSByteOrder.h>
 # include <architecture/byte_order.h>
+#elif defined(__DragonFly__) || defined(__NetBSD__)
+# include <sys/endian.h>
+#elif defined(__FreeBSD__)
+# include <sys/endian.h>
+# define __BIG_ENDIAN            _BIG_ENDIAN
+# define __BYTE_ORDER            _BYTE_ORDER
+# define __LITTLE_ENDIAN         _LITTLE_ENDIAN
 #else
 # include <byteswap.h>
 # include <endian.h>
