--- pr/include/md/prosdep.h.orig	2014-06-05 21:42:08.000000000 +0000
+++ pr/include/md/prosdep.h
@@ -43,6 +43,9 @@ PR_BEGIN_EXTERN_C
 #elif defined(OPENBSD)
 #include "md/_openbsd.h"
 
+#elif defined(__DragonFly__)
+#include "md/_dragonfly.h"
+
 #elif defined(BSDI)
 #include "md/_bsdi.h"
 
