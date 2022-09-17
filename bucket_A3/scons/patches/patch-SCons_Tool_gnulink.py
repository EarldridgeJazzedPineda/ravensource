--- SCons/Tool/gnulink.py.orig	2021-11-15 19:50:26 UTC
+++ SCons/Tool/gnulink.py
@@ -48,7 +48,7 @@ def generate(env):
 
     # __RPATH is set to $_RPATH in the platform specification if that
     # platform supports it.
-    env['RPATHPREFIX'] = '-Wl,-rpath='
+    env['RPATHPREFIX'] = '-Wl,-rpath,'
     env['RPATHSUFFIX'] = ''
     env['_RPATH'] = '${_concat(RPATHPREFIX, RPATH, RPATHSUFFIX, __env__)}'
 
