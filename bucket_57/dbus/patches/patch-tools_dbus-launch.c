--- tools/dbus-launch.c.orig	2022-10-02 14:06:53 UTC
+++ tools/dbus-launch.c
@@ -851,6 +851,12 @@ main (int argc, char **argv)
   exit_with_session = FALSE;
   config_file = NULL;
 
+  if (getenv("RAVENADM") != NULL)
+    {
+      fprintf (stderr, "Package building detected, launch not executed.\n");
+      exit (0);
+    }
+
   /* Ensure that the first three fds are open, to ensure that when we
    * create other file descriptors (for example for epoll, inotify or
    * a socket), they never get assigned as fd 0, 1 or 2. If they were,
