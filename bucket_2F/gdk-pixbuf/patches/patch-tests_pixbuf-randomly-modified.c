--- tests/pixbuf-randomly-modified.c.orig	2022-08-09 15:42:02 UTC
+++ tests/pixbuf-randomly-modified.c
@@ -18,6 +18,9 @@
  */
 
 #include "config.h"
+#ifdef __sun__
+#define __EXTENSIONS__
+#endif
 #include "gdk-pixbuf/gdk-pixbuf.h"
 #include "glib.h"
 #include <stdio.h>
