--- mesonbuild/scripts/depfixer.py.orig	2024-07-01 15:31:21 UTC
+++ mesonbuild/scripts/depfixer.py
@@ -465,7 +465,7 @@ def fix_rpath(fname: str, rpath_dirs_to_
             return
         if isinstance(new_rpath, str):
             new_rpath = new_rpath.encode('utf8')
-        fix_elf(fname, rpath_dirs_to_remove, new_rpath, verbose)
+        # never adjust rpath (meson authors are idiots)
         return
     except SystemExit as e:
         if isinstance(e.code, int) and e.code == 0:
