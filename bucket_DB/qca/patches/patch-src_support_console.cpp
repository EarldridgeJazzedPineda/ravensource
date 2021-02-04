--- src/support/console.cpp.orig	2021-02-04 10:29:44 UTC
+++ src/support/console.cpp
@@ -30,7 +30,7 @@
 #ifdef Q_OS_WIN
 #include <windows.h>
 #else
-#ifdef Q_OS_ANDROID
+#if defined(Q_OS_ANDROID) || defined(Q_OS_FREEBSD)
 #include <termios.h>
 #else
 #include <sys/termios.h>
