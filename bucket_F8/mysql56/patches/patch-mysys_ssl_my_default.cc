--- mysys_ssl/my_default.cc.orig	2019-11-26 16:53:45 UTC
+++ mysys_ssl/my_default.cc
@@ -122,7 +122,7 @@ static my_bool defaults_already_read= FA
 
 /* Which directories are searched for options (and in which order) */
 
-#define MAX_DEFAULT_DIRS 6
+#define MAX_DEFAULT_DIRS 7
 #define DEFAULT_DIRS_SIZE (MAX_DEFAULT_DIRS + 1)  /* Terminate with NULL */
 static const char **default_directories = NULL;
 
@@ -915,6 +915,14 @@ static int search_default_file_with_ext(
       return 1;                                 /* Ignore wrong files */
   }
 
+  if (strstr(name, "/etc") == name)
+  {
+    fprintf(stderr,
+             "error: Config file %s in invalid location, please move to or merge with /usr/local%s\n",
+             name,name);
+      goto err;
+  }
+
   while (mysql_file_getline(buff, sizeof(buff) - 1, fp, is_login_file))
   {
     line++;
@@ -1253,7 +1261,8 @@ void my_print_default_files(const char *
             end[(strlen(end)-1)] = ' ';
           else
             strxmov(end, conf_file, *ext , " ",  NullS);
-          fputs(name, stdout);
+          if (strstr(name, "/etc") != name)
+            fputs(name, stdout);
         }
       }
     }
@@ -1412,13 +1421,8 @@ static const char **init_default_directo
 
 #else
 
-  errors += add_directory(alloc, "/etc/", dirs);
-  errors += add_directory(alloc, "/etc/mysql/", dirs);
-
-#if defined(DEFAULT_SYSCONFDIR)
-  if (DEFAULT_SYSCONFDIR[0])
-    errors += add_directory(alloc, DEFAULT_SYSCONFDIR, dirs);
-#endif /* DEFAULT_SYSCONFDIR */
+  errors += add_directory(alloc, "/usr/local/etc/", dirs);
+  errors += add_directory(alloc, "/usr/local/etc/mysql/", dirs);
 
 #endif
 
@@ -1489,7 +1493,7 @@ int check_file_permissions(const char *f
   MY_STAT stat_info;
 
   if (!my_stat(file_name,&stat_info,MYF(0)))
-    return 1;
+    return 0;
   /*
     Ignore .mylogin.cnf file if not exclusively readable/writable
     by current user.
