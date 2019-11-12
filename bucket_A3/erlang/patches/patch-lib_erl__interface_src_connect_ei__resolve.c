--- lib/erl_interface/src/connect/ei_resolve.c.orig	2019-11-08 11:19:37 UTC
+++ lib/erl_interface/src/connect/ei_resolve.c
@@ -661,7 +661,8 @@ struct hostent *ei_gethostbyname_r(const
 
   return result;
 #else
-  return gethostbyname_r(name,hostp,buffer,buflen,h_errnop);
+  struct hostent *dummy;
+  return gethostbyname_r(name,hostp,buffer,buflen,&dummy,h_errnop);
 #endif
 #endif
 #endif
