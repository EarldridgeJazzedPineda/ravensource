--- pr/src/md/unix/uxrng.c.orig	2021-05-26 16:06:44 UTC
+++ pr/src/md/unix/uxrng.c
@@ -64,6 +64,7 @@ GetHighResClock(void *buf, size_t maxbyt
 
 #elif (defined(LINUX) || defined(FREEBSD) || defined(__FreeBSD_kernel__) \
     || defined(NETBSD) || defined(__NetBSD_kernel__) || defined(OPENBSD) \
+    || defined(__DragonFly__) \
     || defined(__GNU__))
 #include <sys/types.h>
 #include <sys/stat.h>
