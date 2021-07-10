--- tools/llvm-objcopy/MachO/MachOReader.cpp.orig	2021-06-28 16:23:38 UTC
+++ tools/llvm-objcopy/MachO/MachOReader.cpp
@@ -13,6 +13,18 @@
 #include "llvm/Support/Errc.h"
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
