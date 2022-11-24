--- src/corelib/io/qlockfile_unix.cpp.orig	2022-11-03 12:40:18 UTC
+++ src/corelib/io/qlockfile_unix.cpp
@@ -237,9 +237,15 @@ QString QLockFilePrivate::processNameByP
         return QString();
     QString name = QFile::decodeName(kp.p_comm);
 # else
+#  if defined __DragonFly__
+    if (kp.kp_pid != pid)
+        return QString();
+    QString name = QFile::decodeName(kp.kp_comm);
+#  else
     if (kp.ki_pid != pid)
         return QString();
     QString name = QFile::decodeName(kp.ki_comm);
+#  endif
 # endif
     return name;
 #elif defined(Q_OS_QNX)
