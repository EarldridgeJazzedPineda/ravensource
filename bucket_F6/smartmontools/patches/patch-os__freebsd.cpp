--- os_freebsd.cpp.orig	2019-01-02 22:09:00 UTC
+++ os_freebsd.cpp
@@ -17,11 +17,13 @@
 #include <err.h>
 #include <errno.h>
 #include <camlib.h>
-#include <cam/scsi/scsi_message.h>
-#include <cam/scsi/scsi_pass.h>
 #if defined(__DragonFly__)
+#include <bus/cam/scsi/scsi_message.h>
+#include <bus/cam/scsi/scsi_pass.h>
 #include <sys/nata.h>
 #else
+#include <cam/scsi/scsi_message.h>
+#include <cam/scsi/scsi_pass.h>
 #include <sys/ata.h>
 #endif
 #include <sys/stat.h>
@@ -54,12 +56,15 @@
 #define FREEBSDVER __FreeBSD_kernel_version
 #endif
 
-#if (FREEBSDVER >= 800000)
+#ifdef __DragonFly__
+#define  DFU4B 1
+#include <libusb20_desc.h>
+#include <libusb20.h>
+#include <bus/u4b/usb.h>
+#include <bus/u4b/usbhid.h>
+#elif (FREEBSDVER >= 800000)
 #include <libusb20_desc.h>
 #include <libusb20.h>
-#elif defined(__DragonFly__)
-#include <bus/usb/usb.h>
-#include <bus/usb/usbhid.h>
 #else
 #include <dev/usb/usb.h>
 #include <dev/usb/usbhid.h>
@@ -1391,6 +1396,14 @@ smart_device * freebsd_scsi_device::auto
   if (len < 36)
     return this;
 
+#ifdef __DragonFly__
+  if (m_camdev == NULL) {
+      close();
+      set_err(EINVAL, "m_camdev not set");
+      return this;
+  }
+#endif
+
   // Use INQUIRY to detect type
 
   // 3ware ?
@@ -1797,7 +1810,7 @@ bool freebsd_smart_interface::get_nvme_d
   return true;
 }
 
-#if (FREEBSDVER < 800000) // without this build fail on FreeBSD 8
+#if (FREEBSDVER < 800000) && !defined(DFU4B)
 static char done[USB_MAX_DEVICES];
 
 static int usbdevinfo(int f, int a, int rec, int busno, unsigned short & vendor_id,
@@ -1853,7 +1866,7 @@ static int usbdevinfo(int f, int a, int
 static int usbdevlist(int busno,unsigned short & vendor_id,
   unsigned short & product_id, unsigned short & version)
 {
-#if (FREEBSDVER >= 800000) // libusb2 interface
+#if (FREEBSDVER >= 800000) || defined(DFU4B) // libusb2 interface
   struct libusb20_device *pdev = NULL;
   struct libusb20_backend *pbe;
   uint32_t matches = 0;
