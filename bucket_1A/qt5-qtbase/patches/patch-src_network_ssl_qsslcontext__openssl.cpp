--- src/network/ssl/qsslcontext_openssl.cpp.orig	2018-05-14 04:46:28 UTC
+++ src/network/ssl/qsslcontext_openssl.cpp
@@ -248,7 +248,7 @@ void QSslContext::applyBackendConfig(QSs
     if (sslContext->sslConfiguration.backendConfiguration().isEmpty())
         return;
 
-#if OPENSSL_VERSION_NUMBER >= 0x10002000L
+#if OPENSSL_VERSION_NUMBER >= 0x10002000L && !defined(LIBRESSL_VERSION_NUMBER)
     if (QSslSocket::sslLibraryVersionNumber() >= 0x10002000L) {
         QSharedPointer<SSL_CONF_CTX> cctx(q_SSL_CONF_CTX_new(), &q_SSL_CONF_CTX_free);
         if (cctx) {
