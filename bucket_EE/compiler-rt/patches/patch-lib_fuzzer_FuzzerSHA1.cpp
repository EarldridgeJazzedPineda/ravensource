--- lib/fuzzer/FuzzerSHA1.cpp.orig	2022-04-29 00:10:18 UTC
+++ lib/fuzzer/FuzzerSHA1.cpp
@@ -40,7 +40,11 @@ namespace {  // Added for LibFuzzer
 # define SHA_BIG_ENDIAN
 # endif
 #else // ! defined __LITTLE_ENDIAN__
+# if LIBFUZZER_FREEBSD
+# include <sys/endian.h>
+# else
 # include <endian.h> // machine/endian.h
+# endif
 # if __BYTE_ORDER__ ==  __ORDER_BIG_ENDIAN__
 #  define SHA_BIG_ENDIAN
 # endif
