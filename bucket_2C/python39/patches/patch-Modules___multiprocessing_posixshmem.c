--- Modules/_multiprocessing/posixshmem.c.orig	2022-05-17 11:12:56 UTC
+++ Modules/_multiprocessing/posixshmem.c
@@ -8,6 +8,9 @@ posixshmem - A Python extension that pro
 
 // for shm_open() and shm_unlink()
 #ifdef HAVE_SYS_MMAN_H
+# ifdef __sun__
+# define _XPG4_2
+# endif
 #include <sys/mman.h>
 #endif
 
