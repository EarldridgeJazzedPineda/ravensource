--- libs/process/src/ext/env.cpp.orig	2024-12-05 00:53:35 UTC
+++ libs/process/src/ext/env.cpp
@@ -48,6 +48,7 @@
 #include <algorithm>
 #include <cstring>
 #include <sys/types.h>
+#include <sys/sysctl.h>
 #include <kvm.h>
 #endif
 
