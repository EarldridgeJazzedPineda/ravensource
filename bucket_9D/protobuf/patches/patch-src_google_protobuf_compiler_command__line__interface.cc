--- src/google/protobuf/compiler/command_line_interface.cc.orig	2023-11-15 18:52:57 UTC
+++ src/google/protobuf/compiler/command_line_interface.cc
@@ -55,7 +55,7 @@
 
 #if defined(__APPLE__)
 #include <mach-o/dyld.h>
-#elif defined(__FreeBSD__)
+#elif defined(__FreeBSD__) || defined(__DragonFly__)
 #include <sys/sysctl.h>
 #endif
 
@@ -206,7 +206,7 @@ bool GetProtocAbsolutePath(std::string*
     realpath(dirtybuffer, buffer);
     len = strlen(buffer);
   }
-#elif defined(__FreeBSD__)
+#elif defined(__FreeBSD__) || defined(__DragonFly__)
   char buffer[PATH_MAX];
   size_t len = PATH_MAX;
   int mib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_PATHNAME, -1};
