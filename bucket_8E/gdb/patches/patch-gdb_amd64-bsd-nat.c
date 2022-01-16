--- gdb/amd64-bsd-nat.c.orig	2022-01-16 11:21:18 UTC
+++ gdb/amd64-bsd-nat.c
@@ -28,6 +28,7 @@
 #include <sys/types.h>
 #include <sys/ptrace.h>
 #include <machine/reg.h>
+#include <machine/psl.h>
 
 #include "amd64-tdep.h"
 #include "amd64-nat.h"
@@ -142,12 +143,25 @@ amd64bsd_store_inferior_registers (struc
   if (regnum == -1 || amd64_native_gregset_supplies_p (gdbarch, regnum))
     {
       struct reg regs;
+#ifndef __NetBSD__
+      register_t old_rflags;
+#endif
 
       if (gdb_ptrace (PT_GETREGS, ptid, (PTRACE_TYPE_ARG3) &regs, 0) == -1)
 	perror_with_name (_("Couldn't get registers"));
 
+#ifndef __NetBSD__
+      old_rflags = regs.r_rflags;
+#endif
       amd64_collect_native_gregset (regcache, &regs, regnum);
 
+#ifndef __NetBSD__
+      /* This is a workaround about the PSL_USERCHANGE posix limitation. */
+      if ((regs.r_rflags ^ old_rflags ) & ~PSL_USERCHANGE)
+      {
+         regs.r_rflags ^= (regs.r_rflags ^ old_rflags ) & ~PSL_USERCHANGE;
+      }
+#endif
       if (gdb_ptrace (PT_SETREGS, ptid, (PTRACE_TYPE_ARG3) &regs, 0) == -1)
 	perror_with_name (_("Couldn't write registers"));
 
