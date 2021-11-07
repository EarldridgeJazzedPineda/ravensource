--- router/src/harness/include/mysql/harness/tty.h.orig	2021-09-28 11:46:34 UTC
+++ router/src/harness/include/mysql/harness/tty.h
@@ -37,6 +37,10 @@
 #include <unistd.h>
 #endif
 
+#ifndef TABDLY
+#define TABDLY	0
+#endif
+
 class HARNESS_EXPORT Tty {
  public:
   using fd_type = int;
