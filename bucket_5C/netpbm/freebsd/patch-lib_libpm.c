--- lib/libpm.c.orig	2021-09-25 20:34:05 UTC
+++ lib/libpm.c
@@ -17,6 +17,7 @@
 #include <unistd.h>
 #include <stdio.h>
 #include <stdarg.h>
+#include <stdlib.h>
 #include <string.h>
 #include <errno.h>
 #include <setjmp.h>
@@ -832,7 +833,7 @@ pm_arg0toprogname(const char arg0[]) {
 unsigned int
 pm_randseed(void) {
 
-    return time(NULL) ^ getpid();
+    return arc4random();
 
 }
 
