--- src/gn/args.cc.orig	2021-12-17 12:22:18 UTC
+++ src/gn/args.cc
@@ -308,8 +308,12 @@ void Args::SetSystemVarsLocked(Scope* de
   os = "mac";
 #elif defined(OS_LINUX)
   os = "linux";
+#elif defined(OS_DRAGONFLY)
+  os = "freebsd";
 #elif defined(OS_FREEBSD)
   os = "freebsd";
+#elif defined(OS_NETBSD)
+  os = "netbsd";
 #elif defined(OS_AIX)
   os = "aix";
 #elif defined(OS_OPENBSD)
