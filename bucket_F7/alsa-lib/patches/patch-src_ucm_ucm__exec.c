--- src/ucm/ucm_exec.c.orig	2023-09-01 15:35:48 UTC
+++ src/ucm/ucm_exec.c
@@ -35,8 +35,9 @@
 
 #if defined(__NetBSD__) || defined(__OpenBSD__) || defined(__FreeBSD__) || defined(__DragonFly__)
 #include <signal.h>
-#if defined(__DragonFly__)
-#define environ NULL /* XXX */
+#include <unistd.h>
+#if defined(__FreeBSD__) || defined(__DragonFly__)
+char *environ[] = { 0 };
 #else
 extern char **environ;
 #endif
