--- glib/tests/utils.c.orig	2022-10-25 12:53:22 UTC
+++ glib/tests/utils.c
@@ -697,7 +697,7 @@ test_xdg_dirs (void)
 
   xdg = (gchar *)g_getenv ("XDG_CONFIG_DIRS");
   if (!xdg)
-    xdg = "/etc/xdg";
+    xdg = "/usr/local/etc/xdg:/etc/xdg";
 
   dirs = g_get_system_config_dirs ();
 
