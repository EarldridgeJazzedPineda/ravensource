--- src/stty.c.orig	2021-09-24 11:31:05 UTC
+++ src/stty.c
@@ -288,10 +288,10 @@ static struct mode_info const mode_info[
 # ifdef TAB3
   {"tab3", output, SANE_UNSET, TAB3, TABDLY},
 # endif
-# ifdef TAB2
+# if 0
   {"tab2", output, SANE_UNSET, TAB2, TABDLY},
 # endif
-# ifdef TAB1
+# if 0
   {"tab1", output, SANE_UNSET, TAB1, TABDLY},
 # endif
 # ifdef TAB0
