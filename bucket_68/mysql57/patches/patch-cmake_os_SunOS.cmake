$NetBSD: patch-cmake_os_SunOS.cmake,v 1.3 2019/10/31 12:04:22 jperkin Exp $

Do not attempt to detect ISA, it conflicts with wrappers.
Disable HAVE_SOLARIS_LARGE_PAGES, only supported on Oracle Solaris.

--- cmake/os/SunOS.cmake.orig	2022-12-07 18:10:52 UTC
+++ cmake/os/SunOS.cmake
@@ -87,6 +87,7 @@ ADD_DEFINITIONS(-D__EXTENSIONS__)
 # http://docs.oracle.com/cd/E19455-01/806-5257/6je9h033k/index.html
 ADD_DEFINITIONS(-D_POSIX_PTHREAD_SEMANTICS -D_REENTRANT -D_PTHREADS)
 
+IF (0)
 IF (NOT "${CMAKE_C_FLAGS}${CMAKE_CXX_FLAGS}" MATCHES "-m32|-m64")
   EXECUTE_PROCESS(COMMAND isainfo -b
     OUTPUT_VARIABLE ISAINFO_B
@@ -111,6 +112,7 @@ ELSE()
     SET(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -m64")
   ENDIF()
 ENDIF()
+ENDIF()
 
 # On  Solaris, use of intrinsics will screw the lib search logic
 # Force using -lm, so rint etc are found.
@@ -121,7 +123,7 @@ SET(LIBM m)
 SET(CMAKE_THREAD_LIBS_INIT -lpthread CACHE INTERNAL "" FORCE)
 
 # Solaris specific large page support
-CHECK_SYMBOL_EXISTS(MHA_MAPSIZE_VA sys/mman.h  HAVE_SOLARIS_LARGE_PAGES)
+#CHECK_SYMBOL_EXISTS(MHA_MAPSIZE_VA sys/mman.h  HAVE_SOLARIS_LARGE_PAGES)
 
 # Solaris atomics
 CHECK_C_SOURCE_RUNS(
