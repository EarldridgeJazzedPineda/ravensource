--- lib/xml.c.orig	2020-12-07 18:37:03 UTC
+++ lib/xml.c
@@ -38,7 +38,11 @@
 #endif
 #include <sys/stat.h>
 #include <sys/types.h>
-#if defined(__linux__)
+#if defined(__linux__) || defined(__DragonFly__) || defined(__FreeBSD__)
+#define __BSD_VISIBLE 1
+#include <dlfcn.h>
+#elif defined(__NetBSD__)
+#define _NETBSD_SOURCE
 #include <dlfcn.h>
 #elif defined(__APPLE__)
 #define _DARWIN_C_SOURCE
@@ -2137,7 +2141,7 @@ default_udunits2_xml_path()
     if (absXmlPathname[0] == 0) {
         const char* prefix = NULL; // Installation directory
 
-#       if defined(__APPLE__) || defined(__linux__)
+#       if defined(__APPLE__) || defined(__linux__) || defined(__FreeBSD__) || defined(__DragonFly__) || defined(__NetBSD__)
             Dl_info     info;
             const char  sep = '/'; // Pathname component separator
             char        buf[PATH_MAX];
