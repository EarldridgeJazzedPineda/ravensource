--- mesonbuild/compilers/compilers.py.orig	2019-10-06 17:01:35 UTC
+++ mesonbuild/compilers/compilers.py
@@ -348,9 +348,6 @@ def get_base_link_args(options, linker,
     # -bitcode_bundle is incompatible with -undefined and -bundle
     if bitcode and not is_shared_module:
         args.extend(linker.bitcode_args())
-    elif as_needed:
-        # -Wl,-dead_strip_dylibs is incompatible with bitcode
-        args.extend(linker.get_asneeded_args())
 
     # Apple's ld (the only one that supports bitcode) does not like any
     # -undefined arguments at all, so don't pass these when using bitcode
@@ -544,10 +541,6 @@ class CompilerArgs(list):
                 if group_start < 0:
                     # First occurrence of a library
                     group_start = i
-            if group_start >= 0:
-                # Last occurrence of a library
-                new.insert(group_end + 1, '-Wl,--end-group')
-                new.insert(group_start, '-Wl,--start-group')
         # Remove system/default include paths added with -isystem
         if hasattr(self.compiler, 'get_default_include_dirs'):
             default_dirs = self.compiler.get_default_include_dirs()
