--- src/event/modules/ngx_kqueue_module.c.orig	2023-05-23 15:08:20 UTC
+++ src/event/modules/ngx_kqueue_module.c
@@ -429,8 +429,7 @@ ngx_kqueue_set_event(ngx_event_t *ev, ng
     if (filter == EVFILT_VNODE) {
         kev->fflags = NOTE_DELETE|NOTE_WRITE|NOTE_EXTEND
                                  |NOTE_ATTRIB|NOTE_RENAME
-#if (__FreeBSD__ == 4 && __FreeBSD_version >= 430000) \
-    || __FreeBSD_version >= 500018
+#if __FreeBSD_version >= 430000
                                  |NOTE_REVOKE
 #endif
                       ;
