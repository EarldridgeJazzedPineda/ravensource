--- src/packer.h.orig	2023-08-08 08:38:12 UTC
+++ src/packer.h
@@ -221,7 +221,7 @@ protected:
     void addLoader(C, C, C, C, C, C, C, C, C);
     void addLoader(C, C, C, C, C, C, C, C, C, C);
 #undef C
-#if (ACC_CC_CLANG || ACC_CC_GNUC)
+#if 0 && (ACC_CC_CLANG || ACC_CC_GNUC)
     void addLoaderVA(const char *s, ...) __attribute__((__sentinel__));
 #else
     void addLoaderVA(const char *s, ...);
