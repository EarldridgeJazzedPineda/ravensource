--- Source/WebCore/Modules/fetch/FetchBodyConsumer.cpp.orig	2024-08-19 06:28:38 UTC
+++ Source/WebCore/Modules/fetch/FetchBodyConsumer.cpp
@@ -44,6 +44,32 @@
 #include <wtf/URLParser.h>
 #include <wtf/text/MakeString.h>
 
+#ifdef __sun
+static void *memmem(
+		const void *big, size_t big_len,
+		const void *little, size_t little_len)
+{
+	const char *bp = (const char *)big;
+	const char *lp = (const char *)little;
+	size_t l;
+
+	if (big_len < little_len || little_len == 0 || big_len == 0)
+		return NULL;
+
+	while (big_len > 0) {
+		for (l = 0; l < little_len; l++) {
+			if (bp[l] != lp[l])
+				break;
+		}
+		if (l == little_len)
+			return (void *)bp;
+		bp++;
+	}
+
+	return NULL;
+}
+#endif
+
 namespace WebCore {
 
 static inline Ref<Blob> blobFromData(ScriptExecutionContext* context, Vector<uint8_t>&& data, const String& contentType)
