--- deps/lua/src/lua_cjson.c.orig	2023-02-28 16:32:34 UTC
+++ deps/lua/src/lua_cjson.c
@@ -46,7 +46,9 @@
 #include "strbuf.h"
 #include "fpconv.h"
 
+#if defined(__sun)
 #include "../../../src/solarisfixes.h"
+#endif
 
 #ifndef CJSON_MODNAME
 #define CJSON_MODNAME   "cjson"
