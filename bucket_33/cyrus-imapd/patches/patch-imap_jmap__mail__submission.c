--- imap/jmap_mail_submission.c.orig	2024-08-16 00:27:41 UTC
+++ imap/jmap_mail_submission.c
@@ -229,7 +229,7 @@ static int _emailsubmission_address_pars
             if (holduntil) {
                 if (!strcasecmp(key, "HOLDFOR")) {
                     char *endptr = (char *) val;
-                    ulong interval = val ? strtoul(val, &endptr, 10) : ULONG_MAX;
+                    unsigned long interval = val ? strtoul(val, &endptr, 10) : ULONG_MAX;
                     time_t now = time(0);
 
                     if (endptr == val || *endptr != '\0' ||
