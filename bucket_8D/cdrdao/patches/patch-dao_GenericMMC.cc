--- dao/GenericMMC.cc.orig	2023-02-03 14:46:06 UTC
+++ dao/GenericMMC.cc
@@ -2075,7 +2075,7 @@ CdRawToc *GenericMMC::getRawToc(int sess
     return NULL;
   }
 
-  dataLen = ((reqData[0] << 8) | reqData[1]) + 2;
+  dataLen = (dataLen + 1) & ~1;
   
   log_message(4, "Raw toc data len: %d", dataLen);
 
