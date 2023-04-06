--- hw/xfree86/os-support/xf86_OSlib.h.orig	2023-03-29 12:55:03 UTC
+++ hw/xfree86/os-support/xf86_OSlib.h
@@ -241,7 +241,7 @@ extern _X_HIDDEN char xf86SolarisFbDev[P
 #ifdef SYSCONS_SUPPORT
 #define COMPAT_SYSCONS
 #if defined(__FreeBSD__) || defined(__FreeBSD_kernel__) || defined(__DragonFly__)
-#if defined(__DragonFly__)  || (__FreeBSD_kernel_version >= 410000)
+#if defined(__DragonFly__)  || (__FreeBSD_kernel_version >= 410000) || defined(__MidnightBSD__)
 #include <sys/consio.h>
 #include <sys/kbio.h>
 #else
