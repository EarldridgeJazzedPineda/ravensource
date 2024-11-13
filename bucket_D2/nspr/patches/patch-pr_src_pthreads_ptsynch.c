--- pr/src/pthreads/ptsynch.c.orig	2024-10-21 11:31:57 UTC
+++ pr/src/pthreads/ptsynch.c
@@ -25,7 +25,7 @@ static pthread_condattr_t _pt_cvar_attr;
 extern PTDebug pt_debug; /* this is shared between several modules */
 #  endif                 /* defined(DEBUG) */
 
-#  if defined(FREEBSD)
+#  if defined(FREEBSD) && (defined(DEBUG) || defined(FORCE_PR_ASSERT))
 /*
  * On older versions of FreeBSD, pthread_mutex_trylock returns EDEADLK.
  * Newer versions return EBUSY.  We still need to support both.
@@ -863,7 +863,7 @@ PR_IMPLEMENT(PRStatus) PR_DeleteSemaphor
  * From the semctl(2) man page in glibc 2.0
  */
 #    if (defined(__GNU_LIBRARY__) && !defined(_SEM_SEMUN_UNDEFINED)) || \
-        (defined(FREEBSD) && __FreeBSD_version < 1200059) ||            \
+        defined(__DragonFly__) || \
         defined(OPENBSD) || defined(DARWIN)
 /* union semun is defined by including <sys/sem.h> */
 #    else
