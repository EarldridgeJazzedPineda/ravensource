--- hw/ppc/mac_newworld.c.orig	2019-12-12 18:20:47 UTC
+++ hw/ppc/mac_newworld.c
@@ -75,6 +75,11 @@
 #include "hw/sysbus.h"
 #include "trace.h"
 
+/* FreeBSD headers define this */
+#ifdef round_page
+#undef round_page
+#endif
+
 #define MAX_IDE_BUS 2
 #define CFG_ADDR 0xf0000510
 #define TBFREQ (100UL * 1000UL * 1000UL)
