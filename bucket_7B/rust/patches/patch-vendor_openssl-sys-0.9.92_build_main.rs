--- vendor/openssl-sys-0.9.92/build/main.rs.orig	2024-10-15 19:22:50.000000000 +0200
+++ vendor/openssl-sys-0.9.92/build/main.rs	2024-10-20 12:23:43.193142000 +0200
@@ -273,6 +273,9 @@
             (3, 7, 1) => ('3', '7', '1'),
             (3, 7, _) => ('3', '7', 'x'),
             (3, 8, 0) => ('3', '8', '0'),
+            (3, 8, 1) => ('3', '8', '1'),
+            (3, 8, _) => ('3', '8', 'x'),
+            (3, 9, _) => ('3', '9', 'x'),
             _ => version_error(),
         };
 
@@ -315,7 +318,7 @@
         "
 
 This crate is only compatible with OpenSSL (version 1.0.1 through 1.1.1, or 3.0.0), or LibreSSL 2.5
-through 3.8.0, but a different version of OpenSSL was found. The build is now aborting
+through 3.9.x, but a different version of OpenSSL was found. The build is now aborting
 due to this version mismatch.
 
 "
