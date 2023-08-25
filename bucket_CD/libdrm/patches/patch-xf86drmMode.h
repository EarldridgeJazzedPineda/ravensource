--- xf86drmMode.h.orig	2023-08-23 09:57:39 UTC
+++ xf86drmMode.h
@@ -429,7 +429,7 @@ extern drmModePlaneResPtr drmModeGetPlan
 extern drmModePlanePtr drmModeGetPlane(int fd, uint32_t plane_id);
 extern int drmModeSetPlane(int fd, uint32_t plane_id, uint32_t crtc_id,
 			   uint32_t fb_id, uint32_t flags,
-			   int32_t crtc_x, int32_t crtc_y,
+			   uint32_t crtc_x, int32_t crtc_y,
 			   uint32_t crtc_w, uint32_t crtc_h,
 			   uint32_t src_x, uint32_t src_y,
 			   uint32_t src_w, uint32_t src_h);
