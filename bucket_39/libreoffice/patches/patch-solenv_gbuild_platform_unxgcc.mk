--- solenv/gbuild/platform/unxgcc.mk.orig	2024-09-23 13:53:35 UTC
+++ solenv/gbuild/platform/unxgcc.mk
@@ -55,8 +55,7 @@ endif
 gb_CXXFLAGS := \
 	$(gb_CXXFLAGS_COMMON) \
 	-fPIC \
-	-Wshadow \
-	-Woverloaded-virtual \
+	$(CXXFLAGS_WARN) \
 	$(CXXFLAGS_CXX11) \
 	$(gb_CXX_LINKFLAGS) \
 
