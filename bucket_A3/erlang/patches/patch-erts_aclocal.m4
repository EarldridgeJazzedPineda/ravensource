--- erts/aclocal.m4.orig	2019-06-17 14:51:22 UTC
+++ erts/aclocal.m4
@@ -3028,7 +3028,7 @@ case $host_os in
 			DED_LDFLAGS="-m32 $DED_LDFLAGS"
 		fi
 	;;	
-	freebsd*)
+	freebsd*|dragonfly*)
 		DED_LD="$CC"
 		DED_LD_FLAG_RUNTIME_LIBRARY_PATH="$CFLAG_RUNTIME_LIBRARY_PATH"
 		DED_LDFLAGS="-shared"
