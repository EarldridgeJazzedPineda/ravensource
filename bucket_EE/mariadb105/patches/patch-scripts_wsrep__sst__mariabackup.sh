--- scripts/wsrep_sst_mariabackup.sh.orig	2024-05-08 18:05:54 UTC
+++ scripts/wsrep_sst_mariabackup.sh
@@ -803,8 +803,7 @@ recv_joiner()
     if [ $tmt -gt 0 ]; then
         if [ -n "$(commandex timeout)" ]; then
             local koption=0
-            if [ "$OS" = 'FreeBSD' -o "$OS" = 'NetBSD' -o "$OS" = 'OpenBSD' -o \
-                 "$OS" = 'DragonFly' ]; then
+            if [ 1 eq 1 ]; then
                 if timeout 2>&1 | grep -qw -F -- '-k'; then
                     koption=1
                 fi
