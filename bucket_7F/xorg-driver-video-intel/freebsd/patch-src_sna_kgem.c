--- src/sna/kgem.c.orig	2017-09-27 18:01:05 UTC
+++ src/sna/kgem.c
@@ -29,6 +29,9 @@
 #include "config.h"
 #endif
 
+#define _WITH_GETLINE	/* to expose getline() in stdio.h on FreeBSD */
+#include <stdio.h>	/* for getline() */
+
 #include "sna.h"
 #include "sna_reg.h"
 
@@ -70,7 +73,7 @@ search_snoop_cache(struct kgem *kgem, un
 #define DBG_NO_CREATE2 0
 #define DBG_NO_USERPTR 0
 #define DBG_NO_UNSYNCHRONIZED_USERPTR 0
-#define DBG_NO_LLC 0
+#define DBG_NO_LLC 1
 #define DBG_NO_SEMAPHORES 0
 #define DBG_NO_MADV 0
 #define DBG_NO_UPLOAD_CACHE 0
@@ -3299,7 +3302,9 @@ bool __kgem_ring_is_idle(struct kgem *kg
 	if (rq) {
 		struct kgem_request *tmp;
 
-		if (__kgem_busy(kgem, rq->bo->handle)) {
+		if (rq->bo == NULL)
+			fprintf(stderr, "__kgem_ring_is_idle: rq->bo == NULL\n");
+		if (rq->bo && __kgem_busy(kgem, rq->bo->handle)) {
 			DBG(("%s: last fence handle=%d still busy\n",
 			     __FUNCTION__, rq->bo->handle));
 			return false;
