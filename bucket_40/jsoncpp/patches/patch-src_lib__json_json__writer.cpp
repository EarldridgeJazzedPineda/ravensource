--- src/lib_json/json_writer.cpp.orig	2019-07-11 21:38:06 UTC
+++ src/lib_json/json_writer.cpp
@@ -3,6 +3,11 @@
 // recognized in your jurisdiction.
 // See file LICENSE for detail or copy at http://jsoncpp.sourceforge.net/LICENSE
 
+// fix for lang/gcc5+
+#if __GNUC__ == 5
+#include <cstdio>
+#endif
+
 #if !defined(JSON_IS_AMALGAMATION)
 #include "json_tool.h"
 #include <json/writer.h>
