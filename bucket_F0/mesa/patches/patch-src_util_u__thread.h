--- src/util/u_thread.h.orig	2022-06-16 16:17:53 UTC
+++ src/util/u_thread.h
@@ -40,6 +40,7 @@
 #include <signal.h>
 #ifdef HAVE_PTHREAD_NP_H
 #include <pthread_np.h>
+#undef ALIGN
 #endif
 #endif
 
@@ -125,7 +126,7 @@ static inline thrd_t u_thread_create(int
 static inline void u_thread_setname( const char *name )
 {
 #if defined(HAVE_PTHREAD)
-#if DETECT_OS_LINUX || DETECT_OS_CYGWIN || DETECT_OS_SOLARIS
+#if DETECT_OS_LINUX || DETECT_OS_CYGWIN
    int ret = pthread_setname_np(pthread_self(), name);
    if (ret == ERANGE) {
       char buf[16];
@@ -134,7 +135,7 @@ static inline void u_thread_setname( con
       buf[len] = '\0';
       pthread_setname_np(pthread_self(), buf);
    }
-#elif DETECT_OS_FREEBSD || DETECT_OS_OPENBSD
+#elif DETECT_OS_FREEBSD || DETECT_OS_OPENBSD || DETECT_OS_DRAGONFLY
    pthread_set_name_np(pthread_self(), name);
 #elif DETECT_OS_NETBSD
    pthread_setname_np(pthread_self(), "%s", (void *)name);
@@ -142,8 +143,6 @@ static inline void u_thread_setname( con
    pthread_setname_np(name);
 #elif DETECT_OS_HAIKU
    rename_thread(find_thread(NULL), name);
-#else
-#warning Not sure how to call pthread_setname_np
 #endif
 #endif
    (void)name;
@@ -238,7 +237,7 @@ util_set_current_thread_affinity(const u
 static inline int64_t
 util_thread_get_time_nano(thrd_t thread)
 {
-#if defined(HAVE_PTHREAD) && !defined(__APPLE__) && !defined(__HAIKU__)
+#if defined(HAVE_PTHREAD) && !defined(__APPLE__) && !defined(__HAIKU__) && !defined(__sun)
    struct timespec ts;
    clockid_t cid;
 
