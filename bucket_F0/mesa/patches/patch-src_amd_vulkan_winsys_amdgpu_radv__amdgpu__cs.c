- Define ETIME if missing

--- src/amd/vulkan/winsys/amdgpu/radv_amdgpu_cs.c.orig	2024-10-30 18:12:27 UTC
+++ src/amd/vulkan/winsys/amdgpu/radv_amdgpu_cs.c
@@ -41,6 +41,10 @@
 
 enum { VIRTUAL_BUFFER_HASH_TABLE_SIZE = 1024 };
 
+#ifndef ETIME
+#define ETIME ETIMEDOUT
+#endif
+
 struct radv_amdgpu_ib {
    struct radeon_winsys_bo *bo; /* NULL when not owned by the current CS object */
    uint64_t va;
