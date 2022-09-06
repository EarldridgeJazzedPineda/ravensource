Add NAME_MAX compat.

--- include/c.h.orig	2022-08-04 08:21:36 UTC
+++ include/c.h
@@ -37,6 +37,10 @@
 # define NAME_MAX PATH_MAX
 #endif
 
+#ifndef NAME_MAX
+# define NAME_MAX PATH_MAX
+#endif
+
 /*
  * __GNUC_PREREQ is deprecated in favour of __has_attribute() and
  * __has_feature(). The __has macros are supported by clang and gcc>=5.
