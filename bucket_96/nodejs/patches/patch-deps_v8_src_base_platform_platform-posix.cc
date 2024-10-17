--- deps/v8/src/base/platform/platform-posix.cc.orig	2024-10-16 03:44:59 UTC
+++ deps/v8/src/base/platform/platform-posix.cc
@@ -55,7 +55,7 @@
 #if V8_OS_DARWIN
 #include <mach/mach.h>
 #include <malloc/malloc.h>
-#elif !V8_OS_ZOS
+#elif !V8_OS_ZOS && !V8_OS_FREEBSD && !V8_OS_DRAGONFLYBSD
 #include <malloc.h>
 #endif
 
@@ -73,17 +73,10 @@
 #include <sys/syscall.h>
 #endif
 
-#if V8_OS_FREEBSD || V8_OS_DARWIN || V8_OS_OPENBSD || V8_OS_SOLARIS
+#if V8_OS_FREEBSD || V8_OS_DARWIN || V8_OS_OPENBSD || V8_OS_SOLARIS || V8_OS_DRAGONFLYBSD
 #define MAP_ANONYMOUS MAP_ANON
 #endif
 
-#if defined(V8_OS_SOLARIS)
-#if (defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE > 2) || defined(__EXTENSIONS__)
-extern "C" int madvise(caddr_t, size_t, int);
-#else
-extern int madvise(caddr_t, size_t, int);
-#endif
-#endif
 
 #ifndef MADV_FREE
 #define MADV_FREE MADV_DONTNEED
@@ -138,7 +131,7 @@ int GetFlagsForMemoryPermission(OS::Memo
   flags |= (page_type == PageType::kShared) ? MAP_SHARED : MAP_PRIVATE;
   if (access == OS::MemoryPermission::kNoAccess ||
       access == OS::MemoryPermission::kNoAccessWillJitLater) {
-#if !V8_OS_AIX && !V8_OS_FREEBSD && !V8_OS_QNX
+#if !V8_OS_AIX && !V8_OS_FREEBSD && !V8_OS_QNX && !V8_OS_DRAGONFLYBSD
     flags |= MAP_NORESERVE;
 #endif  // !V8_OS_AIX && !V8_OS_FREEBSD && !V8_OS_QNX
 #if V8_OS_QNX
@@ -406,6 +399,13 @@ void* OS::GetRandomMmapAddr() {
 #endif
 #endif
 #endif
+#if V8_OS_NETBSD
+ /*
+  * Avoid using a random hint, some low numbers cause spurious ENOMEM on netbsd
+  * (PR port-arm/55533)
+  */
+  raw_addr = 0;
+#endif
   return reinterpret_cast<void*>(raw_addr);
 }
 
@@ -571,14 +571,11 @@ bool OS::DiscardSystemPages(void* addres
     // MADV_FREE_REUSABLE sometimes fails, so fall back to MADV_DONTNEED.
     ret = madvise(address, size, MADV_DONTNEED);
   }
-#elif defined(_AIX) || defined(V8_OS_SOLARIS)
-  int ret = madvise(reinterpret_cast<caddr_t>(address), size, MADV_FREE);
+#elif defined(POSIX_MADV_DONTNEED)
+  int ret = posix_madvise(address, size, POSIX_MADV_DONTNEED);
   if (ret != 0 && errno == ENOSYS) {
     return true;  // madvise is not available on all systems.
   }
-  if (ret != 0 && errno == EINVAL) {
-    ret = madvise(reinterpret_cast<caddr_t>(address), size, MADV_DONTNEED);
-  }
 #else
   int ret = madvise(address, size, MADV_DONTNEED);
 #endif
@@ -1138,7 +1135,11 @@ Thread::Thread(const Options& options)
       stack_size_(options.stack_size()),
       priority_(options.priority()),
       start_semaphore_(nullptr) {
+#if V8_OS_NETBSD
+  const int min_stack_size = sysconf(_SC_THREAD_STACK_MIN);
+#else
   const int min_stack_size = static_cast<int>(PTHREAD_STACK_MIN);
+#endif
   if (stack_size_ > 0) stack_size_ = std::max(stack_size_, min_stack_size);
   set_name(options.name());
 }
@@ -1153,7 +1154,7 @@ static void SetThreadName(const char* na
   pthread_set_name_np(pthread_self(), name);
 #elif V8_OS_NETBSD
   static_assert(Thread::kMaxThreadNameLength <= PTHREAD_MAX_NAMELEN_NP);
-  pthread_setname_np(pthread_self(), "%s", name);
+  pthread_setname_np(pthread_self(), "%s", (void *)name);
 #elif V8_OS_DARWIN
   // pthread_setname_np is only available in 10.6 or later, so test
   // for it at runtime.
@@ -1329,6 +1330,7 @@ void Thread::SetThreadLocal(LocalStorage
 // support it. MacOS and FreeBSD are different here.
 #if !defined(V8_OS_FREEBSD) && !defined(V8_OS_DARWIN) && !defined(_AIX) && \
     !defined(V8_OS_SOLARIS)
+#if !defined(V8_OS_DRAGONFLYBSD)
 
 namespace {
 #if DEBUG
@@ -1382,6 +1384,7 @@ Stack::StackSlot Stack::ObtainCurrentThr
 #endif  // V8_OS_ZOS
 }
 
+#endif  // !defined(V8_OS_DRAGONFLYBSD)
 #endif  // !defined(V8_OS_FREEBSD) && !defined(V8_OS_DARWIN) &&
         // !defined(_AIX) && !defined(V8_OS_SOLARIS)
 
