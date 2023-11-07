--- uwsgiconfig.py.orig	2023-11-01 13:38:15 UTC
+++ uwsgiconfig.py
@@ -826,7 +826,7 @@ class uConf(object):
 
         global uwsgi_version
 
-        kvm_list = ['FreeBSD', 'OpenBSD', 'NetBSD', 'DragonFly']
+        kvm_list = ['FreeBSD', 'OpenBSD', 'NetBSD', 'DragonFly', 'MidnightBSD']
 
         if 'UWSGI_PROFILE_OVERRIDE' in os.environ:
             for item in os.environ['UWSGI_PROFILE_OVERRIDE'].split(';'):
@@ -841,7 +841,7 @@ class uConf(object):
             self.cflags.append('-DUWSGI_HAS_IFADDRS')
             report['ifaddrs'] = True
 
-        if uwsgi_os in ('FreeBSD', 'DragonFly', 'OpenBSD'):
+        if uwsgi_os in ('FreeBSD', 'DragonFly', 'OpenBSD', 'MidnightBSD'):
             if self.has_include('execinfo.h') or os.path.exists('/usr/local/include/execinfo.h'):
                 if os.path.exists('/usr/local/include/execinfo.h'):
                     self.cflags.append('-I/usr/local/include')
@@ -928,6 +928,8 @@ class uConf(object):
                      pass
             elif uwsgi_os == 'GNU':
                 locking_mode = 'posix_sem'
+            elif uwsgi_os == 'MidnightBSD':
+                locking_mode = 'posix_sem'
             elif uwsgi_os == 'Darwin':
                 locking_mode = 'osx_spinlock'
             elif uwsgi_os.startswith('CYGWIN'):
@@ -962,7 +964,7 @@ class uConf(object):
                 if int(sun_major) >= 5:
                     if int(sun_minor) >= 10:
                         event_mode = 'port'
-            elif uwsgi_os in ('Darwin', 'FreeBSD', 'GNU/kFreeBSD', 'OpenBSD', 'NetBSD', 'DragonFly'):
+            elif uwsgi_os in ('Darwin', 'FreeBSD', 'GNU/kFreeBSD', 'OpenBSD', 'NetBSD', 'DragonFly', 'MidnightBSD'):
                 event_mode = 'kqueue'
             elif uwsgi_os.startswith('CYGWIN') or uwsgi_os == 'GNU':
                 event_mode = 'poll'
@@ -1005,7 +1007,7 @@ class uConf(object):
                     if int(sun_minor) >= 10:
                         timer_mode = 'port'
 
-            elif uwsgi_os in ('Darwin', 'FreeBSD', 'GNU/kFreeBSD', 'OpenBSD', 'NetBSD', 'DragonFly'):
+            elif uwsgi_os in ('Darwin', 'FreeBSD', 'GNU/kFreeBSD', 'OpenBSD', 'NetBSD', 'DragonFly', 'MidnightBSD'):
                 timer_mode = 'kqueue'
 
         if timer_mode == 'timerfd':
@@ -1032,7 +1034,7 @@ class uConf(object):
                 if int(sun_major) >= 5:
                     if int(sun_minor) >= 10:
                         filemonitor_mode = 'port'
-            elif uwsgi_os in ('Darwin', 'FreeBSD', 'GNU/kFreeBSD', 'OpenBSD', 'NetBSD', 'DragonFly'):
+            elif uwsgi_os in ('Darwin', 'FreeBSD', 'GNU/kFreeBSD', 'OpenBSD', 'NetBSD', 'DragonFly', 'MidnightBSD'):
                 filemonitor_mode = 'kqueue'
 
         if filemonitor_mode == 'inotify':
