--- src/platformsupport/input/evdevkeyboard/qevdevkeyboard_defaultmap_p.h.orig	2019-08-31 08:29:31 UTC
+++ src/platformsupport/input/evdevkeyboard/qevdevkeyboard_defaultmap_p.h
@@ -52,11 +52,7 @@
 //
 
 #include "qnamespace.h"
-#ifdef Q_OS_FREEBSD
-#include <dev/evdev/input.h>
-#else
 #include "linux/input.h"
-#endif
 
 // no QT_BEGIN_NAMESPACE, since we include it internally...
 
