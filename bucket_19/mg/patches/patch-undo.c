--- undo.c.orig	2018-07-13 09:16:01 UTC
+++ undo.c
@@ -246,7 +246,11 @@ undo_add_modified(void)
 {
 	struct undo_rec *rec, *trec;
 
+#ifdef __DragonFly__
+	TAILQ_FOREACH_MUTABLE(rec, &curbp->b_undo, next, trec)
+#else
 	TAILQ_FOREACH_SAFE(rec, &curbp->b_undo, next, trec)
+#endif
 		if (rec->type == MODIFIED) {
 			TAILQ_REMOVE(&curbp->b_undo, rec, next);
 			free_undo_record(rec);
