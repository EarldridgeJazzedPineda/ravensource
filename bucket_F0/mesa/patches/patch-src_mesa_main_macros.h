--- src/mesa/main/macros.h.orig	2020-01-09 18:12:10 UTC
+++ src/mesa/main/macros.h
@@ -36,6 +36,7 @@
 #include "util/rounding.h"
 #include "imports.h"
 
+#undef ALIGN
 
 /**
  * \name Integer / float conversion for colors, normals, etc.
