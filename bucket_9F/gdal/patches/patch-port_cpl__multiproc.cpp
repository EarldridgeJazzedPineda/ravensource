--- port/cpl_multiproc.cpp.orig	2024-01-04 18:08:58 UTC
+++ port/cpl_multiproc.cpp
@@ -1423,7 +1423,11 @@ int CPLGetNumCPUs()
     nCPUs = 1;
 #endif
 
-#ifdef HAVE_SCHED_GETAFFINITY
+#if defined(HAVE_SCHED_GETAFFINITY) \
+ && defined(CPU_ALLOC) \
+ && defined(CPU_ALLOC_SIZE) \
+ && defined(CPU_ZERO_S) \
+ && defined(CPU_COUNT_S)
     if (nCPUs > 1)
     {
         cpu_set_t *set = CPU_ALLOC(nCPUs);
