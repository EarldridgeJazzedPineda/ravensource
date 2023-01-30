--- libguile/numbers.c.orig	2023-01-16 21:58:25 UTC
+++ libguile/numbers.c
@@ -192,7 +192,7 @@ static double atanh (double x) { return
 
 
 #if defined (GUILE_I)
-#if defined HAVE_COMPLEX_DOUBLE
+#if defined HAVE_COMPLEX_DOUBLE && (HAVE_CLOG || HAVE_CLOG10 || HAVE_CEXP || HAVE_USABLE_CSQRT) && defined (SCM_COMPLEX_VALUE)
 
 /* For an SCM object Z which is a complex number (ie. satisfies
    SCM_COMPLEXP), return its value as a C level "complex double". */
