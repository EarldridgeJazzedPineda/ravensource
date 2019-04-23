--- qmake/generators/makefile.cpp.orig	2019-04-09 09:51:26 UTC
+++ qmake/generators/makefile.cpp
@@ -3376,7 +3376,7 @@ MakefileGenerator::writePkgConfigFile()
         pkgConfiglibName = bundle.toQString();
     } else {
         if (!project->values("QMAKE_DEFAULT_LIBDIRS").contains(libDir))
-            t << "-L${libdir} ";
+            t << "-L${libdir} -Wl,-rpath,${libdir} ";
         pkgConfiglibName = "-l" + project->first("QMAKE_ORIG_TARGET");
         if (project->isActiveConfig("shared"))
             pkgConfiglibName += project->first("TARGET_VERSION_EXT").toQString();
