--- enchant.c.orig	2023-11-21 14:40:35 UTC
+++ enchant.c
@@ -23,7 +23,7 @@
 #include "php_ini.h"
 #include "ext/standard/info.h"
 #include "Zend/zend_exceptions.h"
-#include "../spl/spl_exceptions.h"
+#include "ext/spl/spl_exceptions.h"
 #include <enchant.h>
 #include "php_enchant.h"
 
