--- cursor/wayland-cursor.c.orig	2019-03-21 00:55:25 UTC
+++ cursor/wayland-cursor.c
@@ -98,7 +98,11 @@ shm_pool_resize(struct shm_pool *pool, i
 
 	pool->data = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED,
 			  pool->fd, 0);
+#if defined(__DragonFly__)
+	if (pool->data == MAP_FAILED)
+#else
 	if (pool->data == (void *)-1)
+#endif
 		return 0;
 	pool->size = size;
 
