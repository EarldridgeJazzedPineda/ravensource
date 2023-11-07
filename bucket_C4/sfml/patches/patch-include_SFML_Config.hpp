$NetBSD: patch-include_SFML_Config.hpp,v 1.1 2020/05/21 08:42:00 plunky Exp $

add NetBSD support

--- include/SFML/Config.hpp.orig	2023-10-30 00:03:26 UTC
+++ include/SFML/Config.hpp
@@ -86,6 +86,11 @@
         // FreeBSD
         #define SFML_SYSTEM_FREEBSD
 
+    #elif defined(__NetBSD__)
+
+        // NetBSD
+        #define SFML_SYSTEM_NETBSD
+
     #elif defined(__OpenBSD__)
 
         // OpenBSD
