--- dyn_load.c.orig	2014-06-03 09:08:02.000000000 +0300
+++ dyn_load.c
@@ -435,7 +435,7 @@ GC_INNER GC_bool GC_register_main_static
 # pragma weak dl_iterate_phdr
 #endif
 
-#if (defined(FREEBSD) && __FreeBSD__ >= 7)
+#if defined __FreeBSD__ || defined __DragonFly__
   /* On the FreeBSD system, any target system at major version 7 shall   */
   /* have dl_iterate_phdr; therefore, we need not make it weak as above. */
 # define HAVE_DL_ITERATE_PHDR
