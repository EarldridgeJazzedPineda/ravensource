--- src/tds/sec_negotiate_openssl.h.orig	2019-02-04 19:03:20 UTC
+++ src/tds/sec_negotiate_openssl.h
@@ -37,6 +37,11 @@
 #error HAVE_OPENSSL not defines, this file should not be included
 #endif
 
+#if defined(LIBRESSL_VERSION_NUMBER) && LIBRESSL_VERSION_NUMBER < 0x2070000fL
+#undef OPENSSL_VERSION_NUMBER
+#define OPENSSL_VERSION_NUMBER 0x1000107fL
+#endif
+
 static inline const BIGNUM*
 rsa_get_n(const RSA *rsa)
 {
