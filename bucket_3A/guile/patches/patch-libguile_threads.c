--- libguile/threads.c.orig	2017-11-30 11:57:46 UTC
+++ libguile/threads.c
@@ -1889,7 +1889,7 @@ scm_ia64_ar_bsp (const void *opaque)
   return (void *) ctx->uc_mcontext.sc_ar_bsp;
 }
 # endif /* linux */
-# ifdef __FreeBSD__
+# if defined __FreeBSD__ || defined __DragonFly__
 #  include <ucontext.h>
 void *
 scm_ia64_register_backing_store_base (void)
