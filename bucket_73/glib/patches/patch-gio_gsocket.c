--- gio/gsocket.c.orig	2021-10-28 12:34:36 UTC
+++ gio/gsocket.c
@@ -56,6 +56,10 @@
 #include <sys/uio.h>
 #endif
 
+#ifdef __sun__
+#define _XPG4_2	1
+#endif
+
 #define GOBJECT_COMPILATION
 #include "gobject/gtype-private.h" /* For _PRELUDE type define */
 #undef GOBJECT_COMPILATION
