--- Source/cmSystemTools.cxx.orig	2022-09-13 13:53:22 UTC
+++ Source/cmSystemTools.cxx
@@ -6,7 +6,8 @@
 // NOLINTNEXTLINE(bugprone-reserved-identifier)
 #  define _POSIX_C_SOURCE 200809L
 #endif
-#if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__QNX__)
+#if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__QNX__) \
+ || defined(__DragonFly__)
 // For isascii
 // NOLINTNEXTLINE(bugprone-reserved-identifier)
 #  define _XOPEN_SOURCE 700
