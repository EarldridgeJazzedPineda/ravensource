--- main.c.orig	2017-10-28 21:58:53 UTC
+++ main.c
@@ -1187,6 +1187,12 @@ main(int argc, char **argv)
 	    Var_Set(".MAKE.PID", tmp, VAR_GLOBAL, 0);
 	    snprintf(tmp, sizeof(tmp), "%u", getppid());
 	    Var_Set(".MAKE.PPID", tmp, VAR_GLOBAL, 0);
+	    Var_Set(".MAKE.OS.NAME",          OSNAME,    VAR_GLOBAL, 0);
+	    Var_Set(".MAKE.OS.VERSION",       OSVERSION, VAR_GLOBAL, 0);
+	    Var_Set(".MAKE.OS.RELEASE",       OSRELEASE, VAR_GLOBAL, 0);
+	    Var_Set(".MAKE.OS.MAJOR",         OSMAJOR,   VAR_GLOBAL, 0);
+	    Var_Set(".MAKE.OS.ARCHITECTURE",  OSARCH,    VAR_GLOBAL, 0);
+	    Var_Set(".MAKE.OS.ARCH.STANDARD", STDARCH,   VAR_GLOBAL, 0);
 	}
 	if (makelevel > 0) {
 		char pn[1024];
