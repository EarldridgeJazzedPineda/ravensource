--- tests/drmdevice.c.orig	2018-10-04 14:50:03 UTC
+++ tests/drmdevice.c
@@ -31,6 +31,9 @@
 #include <unistd.h>
 #include <xf86drm.h>
 
+#ifndef O_CLOEXEC
+#define O_CLOEXEC 0
+#endif
 
 static void
 print_device_info(drmDevicePtr device, int i, bool print_revision)
