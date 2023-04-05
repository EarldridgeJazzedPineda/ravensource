--- CMake/functions/devilutionx_library.cmake.orig	2023-04-05 20:06:24 UTC
+++ CMake/functions/devilutionx_library.cmake
@@ -48,7 +48,7 @@ function(add_devilutionx_library NAME)
     target_compile_options(${NAME} PUBLIC -fsigned-char)
   endif()
 
-  if(NOT WIN32 AND NOT APPLE AND NOT ${CMAKE_SYSTEM_NAME} STREQUAL FreeBSD)
+  if(NOT WIN32 AND NOT APPLE AND NOT ${CMAKE_SYSTEM_NAME} MATCHES "BSD|DragonFly")
     # Enable POSIX extensions such as `readlink` and `ftruncate`.
     add_definitions(-D_POSIX_C_SOURCE=200809L)
   endif()
