--- sql/mysqld.cc.orig	2023-10-30 12:36:20 UTC
+++ sql/mysqld.cc
@@ -4767,8 +4767,9 @@ static void init_ssl()
         sql_print_warning("SSL error: %s",buf);
       }
     }
-    else
+    else {
       ERR_remove_state(0);
+    }
   }
   else
   {
