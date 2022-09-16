--- pr/include/md/_freebsd.h.orig	2022-05-25 21:34:56 UTC
+++ pr/include/md/_freebsd.h
@@ -59,7 +59,15 @@
 #define _PR_HAVE_LARGE_OFF_T
 
 #if defined(_PR_PTHREADS)
-#if __FreeBSD_version >= 400008
+#if defined(__DragonFly__) || __FreeBSD_version >= 602000
+#define _PR_HAVE_GETPROTO_R
+#define _PR_HAVE_5_ARG_GETPROTO_R
+#endif
+#if __FreeBSD_version >= 700016
+#define _PR_HAVE_GETHOST_R
+#define _PR_HAVE_GETHOST_R_INT
+#endif
+#if defined(__DragonFly__) || __FreeBSD_version >= 400008
 /*
  * libc_r before this version of FreeBSD doesn't have poll().
  * Although libc has poll(), it is not thread-safe so we can't
@@ -68,7 +76,7 @@
 #define _PR_POLL_AVAILABLE
 #endif
 #else
-#if __FreeBSD_version >= 300000
+#if defined(__DragonFly__) || __FreeBSD_version >= 300000
 #define _PR_POLL_AVAILABLE
 #define _PR_USE_POLL
 #endif
@@ -77,7 +85,7 @@
 #define _PR_HAVE_SYSV_SEMAPHORES
 #define PR_HAVE_SYSV_NAMED_SHARED_MEMORY
 
-#if __FreeBSD_version >= 400014
+#if defined(__DragonFly__) || __FreeBSD_version >= 400014
 #define _PR_INET6
 #define _PR_HAVE_INET_NTOP
 #define _PR_HAVE_GETHOSTBYNAME2
