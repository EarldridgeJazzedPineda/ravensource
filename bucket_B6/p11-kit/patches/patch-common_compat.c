--- common/compat.c.orig	2019-06-18 15:25:53 UTC
+++ common/compat.c
@@ -38,7 +38,11 @@
  * This is needed to expose pthread_mutexattr_settype and PTHREAD_MUTEX_DEFAULT
  * on older pthreads implementations
  */
+#ifdef __sun__
+#define _XOPEN_SOURCE 600
+#else
 #define _XOPEN_SOURCE 700
+#endif
 
 #include "compat.h"
 #include "debug.h"
@@ -48,6 +52,7 @@
 #include <errno.h>
 #include <stdint.h>
 #include <stdlib.h>
+#include <stdint.h>
 #include <string.h>
 
 /*-
