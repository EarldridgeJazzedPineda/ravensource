$NetBSD: patch-boost_math_special__functions_expm1.hpp,v 1.1 2017/05/29 14:39:29 ryoon Exp $

--- boost/math/special_functions/expm1.hpp.orig	2023-12-06 21:03:04 UTC
+++ boost/math/special_functions/expm1.hpp
@@ -293,7 +293,7 @@ inline typename tools::promote_args<T>::
 #endif
 
 #if defined(BOOST_HAS_EXPM1) && !(defined(__osf__) && defined(__DECCXX_VER))
-#  ifdef BOOST_MATH_USE_C99
+#  if defined(BOOST_MATH_USE_C99) && !defined(__NetBSD__)
 inline float expm1(float x, const policies::policy<>&){ return ::expm1f(x); }
 #     ifndef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
 inline long double expm1(long double x, const policies::policy<>&){ return ::expm1l(x); }
