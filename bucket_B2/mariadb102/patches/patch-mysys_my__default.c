--- mysys/my_default.c.orig	2021-11-05 18:07:43 UTC
+++ mysys/my_default.c
@@ -784,7 +784,7 @@ static int search_default_file_with_ext(
   {
     MY_STAT stat_info;
     if (!my_stat(name,&stat_info,MYF(0)))
-      return 1;
+      return 0;
     /*
       Ignore world-writable regular files.
       This is mainly done to protect us to not read a file created by
@@ -802,6 +802,14 @@ static int search_default_file_with_ext(
   if (!(fp= mysql_file_fopen(key_file_cnf, name, O_RDONLY, MYF(0))))
     return 1;					/* Ignore wrong files */
 
+  if (strstr(name, "/etc") == name)
+  {
+    fprintf(stderr,
+             "error: Config file %s in invalid location, please move to or merge with %%PREFIX%%%s\n",
+             name,name);
+      goto err;
+  }
+
   while (mysql_file_fgets(buff, sizeof(buff) - 1, fp))
   {
     line++;
@@ -1076,7 +1084,8 @@ void my_print_default_files(const char *
           if (name[0] == FN_HOMELIB)	/* Add . to filenames in home */
             *end++= '.';
           strxmov(end, conf_file, *ext, " ", NullS);
-          fputs(name, stdout);
+          if (strstr(name, "/etc") != name)
+            fputs(name, stdout);
         }
       }
     }
@@ -1203,13 +1212,10 @@ static const char **init_default_directo
 
 #else
 
-#if defined(DEFAULT_SYSCONFDIR)
-  if (DEFAULT_SYSCONFDIR[0])
-    errors += add_directory(alloc, DEFAULT_SYSCONFDIR, dirs);
-#else
   errors += add_directory(alloc, "/etc/", dirs);
   errors += add_directory(alloc, "/etc/mysql/", dirs);
-#endif /* DEFAULT_SYSCONFDIR */
+  errors += add_directory(alloc, "%%PREFIX%%/etc/", dirs);
+  errors += add_directory(alloc, "%%PREFIX%%/etc/mysql/", dirs);
 
 #endif
 
