--- include/tables_contained_in.h.orig	2024-06-13 07:46:31 UTC
+++ include/tables_contained_in.h
@@ -27,9 +27,14 @@
 
 #include <string.h>
 
+#include "my_config.h"
 #include "my_inttypes.h"
 #include "sql/sql_optimizer.h"
 
+#ifndef HAVE_FFSLL
+int ffsll(longlong);
+#endif
+
 #ifdef _MSC_VER
 #include <intrin.h>
 #pragma intrinsic(_BitScanForward64)
