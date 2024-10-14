--- misc/fts.c.orig	2024-10-07 09:35:46 UTC
+++ misc/fts.c
@@ -37,12 +37,14 @@ static char sccsid[] = "@(#)fts.c	8.6 (B
 #endif
 
 /* Conditional to set up proper fstat64 implementation */
-#if defined(hpux) || defined(sun) || (defined(__APPLE__) && defined(_DARWIN_FEATURE_ONLY_64_BIT_INODE))
+#if defined(hpux) || defined(sun) || defined(__FreeBSD__) || defined(__DragonFly__) || defined(__NetBSD__)
 #   define FTS_FSTAT64(_fd, _sbp)   fstat((_fd), (_sbp))
 #else
 #   define FTS_FSTAT64(_fd, _sbp)   fstat64((_fd), (_sbp))
 #endif
 
+#include "system.h"
+#include "rpmfts.h"
 #if defined(_LIBC)
 #include <sys/param.h>
 #include <include/sys/stat.h>
@@ -56,12 +58,16 @@ static char sccsid[] = "@(#)fts.c	8.6 (B
 #else
 
 /* Conditionals for working around non-GNU environments */
-#if defined(hpux)
+#if defined(hpux) || defined(__FreeBSD__)
 #   define        _INCLUDE_POSIX_SOURCE
 #   define __errno_location() 	(&errno)
 #   define dirfd(dirp)		-1
 #   define stat64		stat
 #endif
+#if defined(__DragonFly__)
+#   define dirfd(dirp)		-1
+#   define stat64		stat
+#endif
 #if defined(sun)
 #   define __errno_location()	(&errno)
 #   define dirfd(dirp)		-1
@@ -72,14 +78,17 @@ static char sccsid[] = "@(#)fts.c	8.6 (B
 #		define stat64	stat
 #endif
 #endif
+#if defined(__NetBSD__)
+#   define __errno_location()  (&errno)
+#   define stat64              stat
+#   define __fxstat64(_stat_ver, _fd, _sbp)    fstat((_fd), (_sbp))
+#endif
 
-#include "system.h"
 #include <fcntl.h>
 #include <stdlib.h>
 #include <string.h>
 #include <dirent.h>
 #include <errno.h>
-#include "rpmfts.h"
 #   define __set_errno(val) (*__errno_location ()) = (val)
 #   define __open	open
 #   define __close	close
