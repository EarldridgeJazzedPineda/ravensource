--- lib/signal.in.h.orig	2017-03-07 13:51:20 UTC
+++ lib/signal.in.h
@@ -60,6 +60,7 @@
    But avoid namespace pollution on glibc systems.*/
 #if (@GNULIB_PTHREAD_SIGMASK@ || defined GNULIB_POSIXCHECK) \
     && ((defined __APPLE__ && defined __MACH__) \
+	|| defined __DragonFly__ || defined __NetBSD__ \
         || defined __FreeBSD__ || defined __OpenBSD__ || defined __osf__ \
         || defined __sun || defined __ANDROID__) \
     && ! defined __GLIBC__
