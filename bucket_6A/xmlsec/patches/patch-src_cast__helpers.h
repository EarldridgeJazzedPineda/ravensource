--- src/cast_helpers.h.orig	2022-10-29 02:12:11 UTC
+++ src/cast_helpers.h
@@ -16,6 +16,7 @@
 #error "private.h file contains private xmlsec definitions and should not be used outside xmlsec or xmlsec-$crypto libraries"
 #endif /* XMLSEC_PRIVATE */
 
+#include <stdint.h>
 #include <limits.h>
 #include <stdint.h>
 #include "errors_helpers.h"
