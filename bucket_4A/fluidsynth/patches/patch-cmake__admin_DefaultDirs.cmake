--- cmake_admin/DefaultDirs.cmake.orig	2022-01-23 14:33:33 UTC
+++ cmake_admin/DefaultDirs.cmake
@@ -58,7 +58,7 @@ set (INFO_INSTALL_DIR "share/info" CACHE
 mark_as_advanced (INFO_INSTALL_DIR) 
 
 # MAN_INSTALL_DIR - the man pages install dir
-if ( CMAKE_SYSTEM_NAME MATCHES "FreeBSD|DragonFly")
+if ( CMAKE_SYSTEM_NAME MATCHES "nothing")
   set (MAN_INSTALL_DIR "man/man1" CACHE STRING "The man pages install dir")
 else()
   set (MAN_INSTALL_DIR "share/man/man1" CACHE STRING "The man pages install dir")
