--- dbus/dbus-sysdeps-unix.c.orig	2017-10-30 12:26:18 UTC
+++ dbus/dbus-sysdeps-unix.c
@@ -24,6 +24,14 @@
 
 #include <config.h>
 
+#ifdef __sun
+#  if __STDC_VERSION__ - 0 < 199901L
+#define	_XOPEN_SOURCE	500
+#  else
+#define	_XOPEN_SOURCE	600
+#  endif
+#endif
+
 #include "dbus-internals.h"
 #include "dbus-sysdeps.h"
 #include "dbus-sysdeps-unix.h"
