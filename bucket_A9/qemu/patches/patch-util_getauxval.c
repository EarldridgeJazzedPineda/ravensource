--- util/getauxval.c.orig	2024-06-10 18:35:25 UTC
+++ util/getauxval.c
@@ -98,7 +98,7 @@ unsigned long qemu_getauxval(unsigned lo
     return 0;
 }
 
-#elif defined(__FreeBSD__)
+#elif defined(__MidnightBSD__) || (defined(__FreeBSD__) && __FreeBSD_version__ > 1200001)
 #include <sys/auxv.h>
 
 unsigned long qemu_getauxval(unsigned long type)
