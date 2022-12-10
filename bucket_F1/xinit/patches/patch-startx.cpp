#
# generate displayname as dictated in the xauth manpage
#
--- startx.cpp.orig	2022-12-03 22:18:43 UTC
+++ startx.cpp
@@ -168,7 +168,7 @@ while [ x"$1" != x ]; do
 	else
 	    XCOMM display must be the FIRST server argument
 	    if [ x"$serverargs" = x ] && @@
-		 expr "$1" : ':[0-9][0-9]*$' > /dev/null 2>&1; then
+		expr \( "$1" \) : ':[0-9][0-9]*$' > /dev/null 2>&1; then
 		display="$1"
 	    else
 		serverargs="$serverargs $1"
@@ -287,9 +287,9 @@ EOF
     XCOMM now add the same credentials to the client authority file
     XCOMM if '$displayname' already exists do not overwrite it as another
     XCOMM server may need it. Add them to the '$xserverauthfile' instead.
-    for displayname in $authdisplay $hostname$authdisplay; do
+    for displayname in $authdisplay $hostname/unix$authdisplay; do
         authcookie=`XAUTH list "$displayname" @@
-        | sed -n "s/.*$displayname[[:space:]*].*[[:space:]*]//p"` 2>/dev/null;
+        | sed -n "s|.*$displayname[[:space:]*].*[[:space:]*]||p"` 2>/dev/null;
         if [ "z${authcookie}" = "z" ] ; then
             XAUTH -q << EOF 
 add $displayname . $mcookie
