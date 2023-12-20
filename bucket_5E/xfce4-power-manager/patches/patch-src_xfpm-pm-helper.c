--- src/xfpm-pm-helper.c.orig	2023-05-08 18:20:55 UTC
+++ src/xfpm-pm-helper.c
@@ -77,6 +77,10 @@
 #define UP_BACKEND_SUSPEND_COMMAND  "/usr/sbin/zzz"
 #define UP_BACKEND_HIBERNATE_COMMAND "/usr/sbin/ZZZ"
 #endif
+#ifdef __NetBSD__
+#define UP_BACKEND_SUSPEND_COMMAND      "/sbin/sysctl -w hw.acpi.sleep.state=1"
+#define UP_BACKEND_HIBERNATE_COMMAND    "/sbin/sysctl -w hw.acpi.sleep.state=4"
+#endif
 
 
 static gboolean
