--- port/cpl_port.h.orig	2023-09-05 09:06:01 UTC
+++ port/cpl_port.h
@@ -666,7 +666,7 @@ extern "C++"
 }
 #else
 #define CPLIsNan(x) isnan(x)
-#if defined(isinf) || defined(__FreeBSD__)
+#if defined(isinf) || defined(__FreeBSD__) || defined(__DragonFly__)
 /** Return whether a floating-pointer number is +/- infinity */
 #define CPLIsInf(x) isinf(x)
 /** Return whether a floating-pointer number is finite */
