--- external/skia/Library_skia.mk.orig	2023-08-23 11:52:34 UTC
+++ external/skia/Library_skia.mk
@@ -107,6 +107,14 @@ $(eval $(call gb_Library_add_libs,skia,\
 ))
 endif
 
+ifneq (,$(filter DRAGONFLY FREEBSD NETBSD,$(OS)))
+$(eval $(call gb_Library_add_libs,skia,\
+    -lm \
+    -lX11-xcb \
+    -lX11 \
+))
+endif
+
 $(eval $(call gb_Library_use_libraries,skia,\
     sal \
 ))
