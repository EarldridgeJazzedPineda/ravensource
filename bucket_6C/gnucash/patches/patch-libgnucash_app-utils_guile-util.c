--- libgnucash/app-utils/guile-util.c.orig	2019-01-11 23:57:38 UTC
+++ libgnucash/app-utils/guile-util.c
@@ -996,6 +996,8 @@ gnc_parse_time_to_time64 (const gchar *s
 
     g_return_val_if_fail(s && format, -1);
 
+    bzero(&tm, sizeof(tm));
+
     if (!strptime(s, format, &tm))
         return -1;
 
