--- storage/rocksdb/rocksdb/port/jemalloc_helper.h.orig	2023-11-19 07:42:00 UTC
+++ storage/rocksdb/rocksdb/port/jemalloc_helper.h
@@ -26,6 +26,10 @@
 #include <jemalloc/jemalloc.h>
 #endif
 
+#ifdef __FreeBSD__
+#define JEMALLOC_USABLE_SIZE_CONST const
+#endif
+
 #ifndef JEMALLOC_CXX_THROW
 #define JEMALLOC_CXX_THROW
 #endif
