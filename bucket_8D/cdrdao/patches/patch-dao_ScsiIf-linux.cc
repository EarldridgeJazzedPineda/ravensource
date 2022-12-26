--- dao/ScsiIf-linux.cc.orig	2018-05-16 10:46:39 UTC
+++ dao/ScsiIf-linux.cc
@@ -33,6 +33,7 @@
 #include <asm/param.h>
 #include <scsi/scsi.h>
 #include <scsi/sg.h>
+#include <sys/stat.h>
 
 #include "ScsiIf.h"
 #include "sg_err.h"
@@ -276,7 +277,13 @@ int ScsiIf::inquiry()
     for (i = 3; i >= 0 && revision_[i] == ' '; i--) {
 	revision_[i] = 0;
     }
-  
+
+    if (vendor_[0] == 0)
+	strncpy(vendor_, "UNKNOWN", 8);
+
+    if (product_[0] == 0)
+	strncpy(product_, "UNKNOWN", 8); 
+
     return 0;
 }
 
