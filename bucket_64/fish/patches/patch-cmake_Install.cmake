--- cmake/Install.cmake.orig	2023-12-05 14:16:18 UTC
+++ cmake/Install.cmake
@@ -104,7 +104,7 @@ install(FILES share/config.fish
 fish_create_dirs(${rel_datadir}/fish/vendor_completions.d ${rel_datadir}/fish/vendor_functions.d
     ${rel_datadir}/fish/vendor_conf.d)
 
-fish_try_create_dirs(${rel_datadir}/pkgconfig)
+fish_try_create_dirs(${rel_datadir}/../lib/pkgconfig)
 configure_file(fish.pc.in fish.pc.noversion @ONLY)
 
 add_custom_command(OUTPUT fish.pc
@@ -117,7 +117,7 @@ add_custom_command(OUTPUT fish.pc
 add_custom_target(build_fish_pc ALL DEPENDS fish.pc)
 
 install(FILES ${CMAKE_CURRENT_BINARY_DIR}/fish.pc
-        DESTINATION ${rel_datadir}/pkgconfig)
+        DESTINATION ${rel_datadir}/../lib/pkgconfig)
 
 install(DIRECTORY share/completions/
         DESTINATION ${rel_datadir}/fish/completions
