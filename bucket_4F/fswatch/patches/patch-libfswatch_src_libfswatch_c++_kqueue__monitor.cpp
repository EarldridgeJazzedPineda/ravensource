--- libfswatch/src/libfswatch/c++/kqueue_monitor.cpp.orig	2025-01-27 11:14:35 UTC
+++ libfswatch/src/libfswatch/c++/kqueue_monitor.cpp
@@ -131,7 +131,7 @@ namespace fsw
     nanoseconds *= 1000000000;
 
     struct timespec ts{};
-    ts.tv_sec = static_cast<__darwin_time_t>(seconds);
+    ts.tv_sec = static_cast<time_t>(seconds);
     ts.tv_nsec = static_cast<long>(nanoseconds);
 
     return ts;
