--- include/urcu/syscall-compat.h.orig	2024-08-28 19:09:31 UTC
+++ include/urcu/syscall-compat.h
@@ -34,6 +34,7 @@
 
 #elif defined(__CYGWIN__) || defined(__APPLE__) || \
 	defined(__FreeBSD__) || defined(__DragonFly__) || \
+	defined(__NetBSD__) || \
 	defined(__OpenBSD__)
 /* Don't include anything on these platforms. */
 
