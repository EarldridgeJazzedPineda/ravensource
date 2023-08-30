--- libfreeipmi/driver/ipmi-semaphores.h.orig	2023-06-05 22:58:26 UTC
+++ libfreeipmi/driver/ipmi-semaphores.h
@@ -30,7 +30,7 @@
 #include <sys/ipc.h>
 #include <sys/sem.h>
 
-#if defined(__FreeBSD__) || defined(__APPLE__)
+#if defined(__FreeBSD__) || defined(__APPLE__) || defined(__DragonFly__)
 /* union semun is defined by including <sys/sem.h> */
 #else
 /* according to X/OPEN we have to define it ourselves */
