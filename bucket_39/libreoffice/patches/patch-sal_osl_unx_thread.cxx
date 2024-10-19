--- sal/osl/unx/thread.cxx.orig	2024-09-23 13:53:35 UTC
+++ sal/osl/unx/thread.cxx
@@ -38,6 +38,10 @@
 #define pthread_setname_np pthread_set_name_np
 #endif
 #endif
+#ifdef __DragonFly__
+#include <pthread_np.h>
+#define pthread_setname_np pthread_set_name_np
+#endif
 #include <config_options.h>
 #include <o3tl/safeint.hxx>
 #include <osl/thread.h>
