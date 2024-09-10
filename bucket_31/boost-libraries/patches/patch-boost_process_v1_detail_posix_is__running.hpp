--- boost/process/v1/detail/posix/is_running.hpp.orig	2024-08-07 22:07:40 UTC
+++ boost/process/v1/detail/posix/is_running.hpp
@@ -17,10 +17,12 @@ namespace boost { namespace process { BO
 // This bit arrangement of status codes is not guaranteed by POSIX, but (according to comments in
 // the glibc <bits/waitstatus.h> header) is the same across systems in practice.
 constexpr int still_active = 0x017f;
+#if !defined(__NetBSD__)
 static_assert(WIFSTOPPED(still_active), "Expected still_active to indicate WIFSTOPPED");
 static_assert(!WIFEXITED(still_active), "Expected still_active to not indicate WIFEXITED");
 static_assert(!WIFSIGNALED(still_active), "Expected still_active to not indicate WIFSIGNALED");
 static_assert(!WIFCONTINUED(still_active), "Expected still_active to not indicate WIFCONTINUED");
+#endif
 
 inline bool is_running(int code)
 {
