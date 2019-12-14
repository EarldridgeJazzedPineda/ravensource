--- scheduler/auth.c.orig	2019-12-13 14:44:10 UTC
+++ scheduler/auth.c
@@ -441,7 +441,7 @@ cupsdAuthorize(cupsd_client_t *con)	/* I
 
     peersize = sizeof(peercred);
 
-#  ifdef __APPLE__
+#  if defined(__APPLE__) || defined(__FreeBSD__)
     if (getsockopt(httpGetFd(con->http), 0, LOCAL_PEERCRED, &peercred, &peersize))
 #  else
     if (getsockopt(httpGetFd(con->http), SOL_SOCKET, SO_PEERCRED, &peercred, &peersize))
@@ -839,7 +839,7 @@ cupsdAuthorize(cupsd_client_t *con)	/* I
 
       peersize = sizeof(peercred);
 
-#    ifdef __APPLE__
+#    if defined(__APPLE__) || defined(__FreeBSD__)
       if (getsockopt(httpGetFd(con->http), 0, LOCAL_PEERCRED, &peercred, &peersize))
 #    else
       if (getsockopt(httpGetFd(con->http), SOL_SOCKET, SO_PEERCRED, &peercred,
