--- shell/source/unix/exec/shellexec.cxx.orig	2022-01-12 19:09:02 UTC
+++ shell/source/unix/exec/shellexec.cxx
@@ -172,7 +172,7 @@ void SAL_CALL ShellExec::execute( const
         aBuffer.append(" --");
 #else
         // Just use xdg-open on non-Mac
-        aBuffer.append("xdg-open");
+        aBuffer.append("%%LOCALBASE%%/bin/xdg-open");
 #endif
         aBuffer.append(" ");
         escapeForShell(aBuffer, OUStringToOString(aURL, osl_getThreadTextEncoding()));
