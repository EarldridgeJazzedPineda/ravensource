--- src/corelib/io/qfilesystemwatcher.cpp.orig	2022-02-16 13:13:47 UTC
+++ src/corelib/io/qfilesystemwatcher.cpp
@@ -58,6 +58,8 @@
 #  include "qfilesystemwatcher_inotify_p.h"
 #elif defined(Q_OS_FREEBSD) || defined(Q_OS_NETBSD) || defined(Q_OS_OPENBSD) || defined(QT_PLATFORM_UIKIT)
 #  include "qfilesystemwatcher_kqueue_p.h"
+#elif defined(__DragonFly__)
+#  include "qfilesystemwatcher_kqueue_p.h"
 #elif defined(Q_OS_MACOS)
 #  include "qfilesystemwatcher_fsevents_p.h"
 #endif
