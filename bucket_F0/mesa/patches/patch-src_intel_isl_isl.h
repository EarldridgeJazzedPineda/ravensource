--- src/intel/isl/isl.h.orig	2022-11-07 18:01:13 UTC
+++ src/intel/isl/isl.h
@@ -47,6 +47,9 @@
 #include "util/format/u_format.h"
 
 #ifdef __cplusplus
+# ifdef __sun__
+# define restrict	__restrict__
+# endif
 extern "C" {
 #endif
 
