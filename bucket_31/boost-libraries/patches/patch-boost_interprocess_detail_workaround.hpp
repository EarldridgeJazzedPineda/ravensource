--- boost/interprocess/detail/workaround.hpp.orig	2021-12-02 06:47:33 UTC
+++ boost/interprocess/detail/workaround.hpp
@@ -166,7 +166,7 @@
    //////////////////////////////////////////////////////
    //posix_fallocate
    //////////////////////////////////////////////////////
-   #if (_XOPEN_SOURCE >= 600 || _POSIX_C_SOURCE >= 200112L)
+   #if !defined __sun && (_XOPEN_SOURCE >= 600 || _POSIX_C_SOURCE >= 200112L)
    #define BOOST_INTERPROCESS_POSIX_FALLOCATE
    #endif
 
