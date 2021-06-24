--- deps/v8/src/trap-handler/trap-handler.h.orig	2021-06-03 01:45:31 UTC
+++ deps/v8/src/trap-handler/trap-handler.h
@@ -29,6 +29,8 @@ namespace trap_handler {
 #define V8_TRAP_HANDLER_SUPPORTED true
 #elif V8_HOST_ARCH_ARM64 && V8_TARGET_ARCH_ARM64 && V8_OS_MACOSX
 #define V8_TRAP_HANDLER_SUPPORTED true
+#elif V8_TARGET_ARCH_X64 && V8_OS_DRAGONFLYBSD
+#define V8_TRAP_HANDLER_SUPPORTED true
 #else
 #define V8_TRAP_HANDLER_SUPPORTED false
 #endif
