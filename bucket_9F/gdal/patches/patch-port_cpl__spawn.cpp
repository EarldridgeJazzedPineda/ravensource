--- port/cpl_spawn.cpp.orig	2022-11-06 20:09:21 UTC
+++ port/cpl_spawn.cpp
@@ -57,7 +57,7 @@
         #include <crt_externs.h>
         #define environ (*_NSGetEnviron())
     #else
-        #if defined(__FreeBSD__)
+        #if defined(__FreeBSD__) || defined(__DragonFly__)
             extern __attribute__((__weak__)) char **environ;
         #else
             extern char** environ;
