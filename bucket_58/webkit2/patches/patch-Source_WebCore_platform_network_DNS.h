--- Source/WebCore/platform/network/DNS.h.orig	2023-09-19 08:27:49 UTC
+++ Source/WebCore/platform/network/DNS.h
@@ -35,6 +35,9 @@
 #include <ws2tcpip.h>
 #else
 #include <netinet/in.h>
+# if defined __DragonFly__ || defined __FreeBSD__ || defined __sun__ || defined __MidnightBSD__
+#  include <sys/socket.h>
+# endif
 #endif
 
 namespace WebCore {
