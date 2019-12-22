--- tools/llvm-objcopy/MachO/MachOReader.cpp.orig	2019-12-11 19:15:30 UTC
+++ tools/llvm-objcopy/MachO/MachOReader.cpp
@@ -13,6 +13,18 @@
 #include "llvm/Object/MachO.h"
 #include <memory>
 
+#ifdef __sun__
+static size_t
+strnlen(const char *s, size_t maxlen)
+{
+	size_t len;
+	for (len = 0; len < maxlen; len++, s++) {
+		if (!*s) break;
+	}
+	return (len);
+}
+#endif
+
 namespace llvm {
 namespace objcopy {
 namespace macho {
