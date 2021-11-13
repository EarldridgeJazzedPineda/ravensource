# the defintion of ERESTART is behind a check for _KERNEL, but
# defining that causes errno to not be defined. fortunately, there's
# an alternative switch. unfortunately, those differ by platform and
# _WANT_KERNEL_ERRNO is too recent to be part of any release, so just
# define ERESTART if we still don't have it after including errno.h 
#
--- libkms/vmwgfx.c.orig	2021-11-08 16:35:03 UTC
+++ libkms/vmwgfx.c
@@ -29,10 +29,18 @@
 #define _WANT_KERNEL_ERRNO
 #endif
 
+#if defined (__FreeBSD__) || defined (__FreeBSD_kernel__)
+#define _WANT_KERNEL_ERRNO
+#elif defined(__DragonFly__)
+#define _KERNEL_STRUCTURES
+#endif
 #include <errno.h>
 #include <stdlib.h>
 #include <string.h>
 #include "internal.h"
+#ifndef ERESTART
+#define ERESTART (-1)
+#endif
 
 #include "xf86drm.h"
 #include "libdrm_macros.h"
