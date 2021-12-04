--- libsoup/auth/soup-auth-negotiate.c.orig	2021-11-24 18:15:58 UTC
+++ libsoup/auth/soup-auth-negotiate.c
@@ -13,7 +13,11 @@
 #include <string.h>
 
 #ifdef LIBSOUP_HAVE_GSSAPI
+#ifdef __FreeBSD__
+#include <gssapi/gssapi_krb5.h>
+#else
 #include <gssapi/gssapi.h>
+#endif
 #endif /* LIBSOUP_HAVE_GSSAPI */
 
 #include "soup-auth-negotiate.h"
