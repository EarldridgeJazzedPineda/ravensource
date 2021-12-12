--- src/master/main.c.orig	2021-12-03 11:48:47 UTC
+++ src/master/main.c
@@ -886,6 +886,8 @@ int main(int argc, char *argv[])
 		i_fatal("dup2(dev_null_fd) failed: %m");
 	if (!foreground && dup2(dev_null_fd, STDOUT_FILENO) < 0)
 		i_fatal("dup2(dev_null_fd) failed: %m");
+	if (!foreground && dup2(dev_null_fd, STDERR_FILENO) < 0)
+		i_fatal("dup2(dev_null_fd) failed: %m");
 
 	pidfile_path =
 		i_strconcat(set->base_dir, "/"MASTER_PID_FILE_NAME, NULL);
