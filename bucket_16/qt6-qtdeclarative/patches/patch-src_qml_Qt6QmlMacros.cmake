--- src/qml/Qt6QmlMacros.cmake.orig	2025-01-24 06:04:38 UTC
+++ src/qml/Qt6QmlMacros.cmake
@@ -2529,7 +2529,6 @@ function(qt6_add_qml_plugin target)
         string(REPLACE "/" ";" path "qml/${arg_TARGET_PATH}")
         list(LENGTH path path_count)
         string(REPEAT "../" ${path_count} rel_path)
-        string(APPEND rel_path "${CMAKE_INSTALL_LIBDIR}")
         if(APPLE)
             set(install_rpath
                 # If embedded in an app bundle, search in a bundle-local path
@@ -2545,7 +2544,7 @@ function(qt6_add_qml_plugin target)
                 "@loader_path/${rel_path}"
             )
         else()
-            set(install_rpath "$ORIGIN/${rel_path}")
+            set(install_rpath "${CMAKE_INSTALL_LIBDIR}:$ORIGIN/${rel_path}")
         endif()
         set_target_properties(${target} PROPERTIES INSTALL_RPATH "${install_rpath}")
     endif()
