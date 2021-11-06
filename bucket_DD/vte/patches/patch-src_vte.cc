--- src/vte.cc.orig	2021-10-08 17:27:02 UTC
+++ src/vte.cc
@@ -34,6 +34,13 @@
 #ifdef HAVE_SYS_STREAM_H
 #include <sys/stream.h>
 #endif
+#ifdef HAVE_TERMIOS_H
+#include <termios.h>
+#endif
+#if defined(__sun__)
+#include <sys/ioccom.h>
+#include <sys/ptyvar.h>
+#endif
 
 #include <glib.h>
 #include <glib-unix.h>
