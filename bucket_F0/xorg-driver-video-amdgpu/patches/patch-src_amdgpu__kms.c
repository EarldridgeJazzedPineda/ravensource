--- src/amdgpu_kms.c.orig	2022-02-23 12:27:54 UTC
+++ src/amdgpu_kms.c
@@ -932,7 +932,7 @@ static void
 amdgpu_dirty_update(ScrnInfoPtr scrn)
 {
 	ScreenPtr screen = scrn->pScreen;
-	PixmapDirtyUpdatePtr ent;
+	PixmapDirtyUpdatePtr ent = NULL;
 	RegionPtr region;
 
 	xorg_list_for_each_entry(ent, &screen->pixmap_dirty_list, ent) {
