O_CLOEXEC is not available on every platform (e.g. MacOS X < 10.7). It
was introduced in POSIX 2008.

--- lib/randutils.c.orig	2024-01-31 10:02:15 UTC
+++ lib/randutils.c
@@ -78,6 +78,10 @@ static void crank_random(void)
 		rand();
 }
 
+#if !defined(O_CLOEXEC)
+#define O_CLOEXEC 0
+#endif
+
 int random_get_fd(void)
 {
 	int fd;
