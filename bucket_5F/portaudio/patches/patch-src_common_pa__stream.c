--- src/common/pa_stream.c.orig	2021-04-01 00:35:42 UTC
+++ src/common/pa_stream.c
@@ -93,6 +93,8 @@ void PaUtil_InitializeStreamRepresentati
     streamRepresentation->streamInfo.inputLatency = 0.;
     streamRepresentation->streamInfo.outputLatency = 0.;
     streamRepresentation->streamInfo.sampleRate = 0.;
+
+    streamRepresentation->hostApiType = 0;
 }
 
 
