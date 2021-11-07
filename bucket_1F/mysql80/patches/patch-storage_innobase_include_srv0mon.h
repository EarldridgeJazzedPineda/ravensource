--- storage/innobase/include/srv0mon.h.orig	2021-09-28 11:46:34 UTC
+++ storage/innobase/include/srv0mon.h
@@ -40,6 +40,10 @@ Foundation, Inc., 51 Franklin St, Fifth
 /* Required for FreeBSD so that INT64_MAX is defined. */
 #define __STDC_LIMIT_MACROS
 #endif /* __STDC_LIMIT_MACROS */
+#ifdef __DragonFly__
+/* The hack above doen't work for dragonfly, stdint.h already imported */
+#include <machine/int_limits.h>
+#endif
 
 #include <stdint.h>
 
