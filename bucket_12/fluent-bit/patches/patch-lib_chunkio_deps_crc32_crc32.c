--- lib/chunkio/deps/crc32/crc32.c.orig	2024-03-21 15:26:52 UTC
+++ lib/chunkio/deps/crc32/crc32.c
@@ -34,7 +34,7 @@
 #  define __BIG_ENDIAN 1
 #  define __LITTLE_ENDIAN 2
 #  define __BYTE_ORDER __LITTLE_ENDIAN
-#elif defined(__FreeBSD__)
+#elif defined(__FreeBSD__) || defined(__DragonFly__)
 #  include <sys/endian.h>
 #elif defined(__sun) || defined(sun)
 # include <sys/byteorder.h>
