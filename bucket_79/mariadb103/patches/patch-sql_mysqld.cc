--- sql/mysqld.cc.orig	2022-11-02 11:52:42 UTC
+++ sql/mysqld.cc
@@ -5047,8 +5047,9 @@ static void init_ssl()
       while ((err= ERR_get_error()))
         sql_print_warning("SSL error: %s", ERR_error_string(err, NULL));
     }
-    else
+    else {
       ERR_remove_state(0);
+    }
   }
   else
   {
