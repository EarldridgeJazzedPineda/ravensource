The /usr/local value is replaced by post-patch target

--- gio/xdgmime/xdgmime.c.orig	2021-05-11 10:57:23 UTC
+++ gio/xdgmime/xdgmime.c
@@ -235,7 +235,7 @@ xdg_init_dirs (void)
   xdg_data_dirs = getenv ("XDG_DATA_DIRS");
 
   if (xdg_data_dirs == NULL)
-    xdg_data_dirs = "/usr/local/share/:/usr/share/";
+    xdg_data_dirs = "/usr/local/share/";
 
   /* Work out how many dirs we’re dealing with. */
   if (xdg_data_home != NULL || home != NULL)
