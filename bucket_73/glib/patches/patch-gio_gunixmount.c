--- gio/gunixmount.c.orig	2019-12-19 16:33:15 UTC
+++ gio/gunixmount.c
@@ -356,12 +356,17 @@ g_unix_mount_eject (GMount             *
                     gpointer             user_data)
 {
   GUnixMount *unix_mount = G_UNIX_MOUNT (mount);
+#if ! defined(__FreeBSD__) && ! defined(__DragonFly__)
   char *argv[] = {"eject", NULL, NULL};
 
   if (unix_mount->mount_path != NULL)
     argv[1] = unix_mount->mount_path;
   else
     argv[1] = unix_mount->device_path;
+#else
+   char *argv[] = {"cdcontrol", "-f", NULL, "eject", NULL};
+   argv[2] = unix_mount->device_path;
+#endif
 
   eject_unmount_do (mount, cancellable, callback, user_data, argv);
 }
