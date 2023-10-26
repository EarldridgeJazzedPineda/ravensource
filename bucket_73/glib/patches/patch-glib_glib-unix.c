--- glib/glib-unix.c.orig	2023-10-25 11:33:59 UTC
+++ glib/glib-unix.c
@@ -29,6 +29,9 @@
 
 #include <string.h>
 #include <sys/types.h>
+#ifdef __sun
+#define _POSIX_PTHREAD_SEMANTICS 1
+#endif
 #include <pwd.h>
 
 G_STATIC_ASSERT (sizeof (ssize_t) == GLIB_SIZEOF_SSIZE_T);
