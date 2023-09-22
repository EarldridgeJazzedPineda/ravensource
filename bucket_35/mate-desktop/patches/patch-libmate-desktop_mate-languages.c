--- libmate-desktop/mate-languages.c.orig	2023-09-15 10:22:12 UTC
+++ libmate-desktop/mate-languages.c
@@ -47,6 +47,10 @@
 #define ISO_CODES_DATADIR ISO_CODES_PREFIX "/share/xml/iso-codes"
 #define ISO_CODES_LOCALESDIR ISO_CODES_PREFIX "/share/locale"
 
+#ifndef DTTOIF
+#define DTTOIF(dirtype) ((dirtype) << 12)
+#endif
+
 typedef struct _MateLocale {
         char *id;
         char *name;
