--- lib/expr/exgram.h.orig	2024-08-11 22:33:48 UTC
+++ lib/expr/exgram.h
@@ -19,7 +19,7 @@ extern "C" {
  * with both yacc and bison
  */
 
-#if !defined(_EXGRAM_H) && ( defined(MINTOKEN) || defined(YYTOKENTYPE) )
+#if !defined(_EXGRAM_H)
 #define _EXGRAM_H
 
 #include <cgraph/agxbuf.h>
