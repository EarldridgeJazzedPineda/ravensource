--- common/libBuffer/include/CommonFWriteBufferFlusher.h.orig	2018-01-13 00:23:52 UTC
+++ common/libBuffer/include/CommonFWriteBufferFlusher.h
@@ -35,7 +35,7 @@ namespace std {
 #ifdef __GNUC__
 #   include <cstdlib> /* size_t */
 #   include <cstdio>  /* FILE */
-#ifdef __FreeBSD__
+#if defined __FreeBSD__ || defined __DragonFly__ || defined __NetBSD__
 #include <stdint.h> /* int64_t */
 #endif
 #endif
