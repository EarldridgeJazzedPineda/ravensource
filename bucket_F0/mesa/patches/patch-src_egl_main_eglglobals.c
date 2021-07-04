--- src/egl/main/eglglobals.c.orig	2021-06-30 18:18:55 UTC
+++ src/egl/main/eglglobals.c
@@ -138,7 +138,7 @@ _eglPointerIsDereferencable(void *p)
 {
    uintptr_t addr = (uintptr_t) p;
    const long page_size = getpagesize();
-#ifdef HAVE_MINCORE
+#if defined(HAVE_MINCORE) && !defined(__DragonFly__)
    unsigned char valid = 0;
 
    if (p == NULL)
