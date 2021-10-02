--- lib/Driver/ToolChains/DragonFly.h.orig	2021-09-24 16:18:10 UTC
+++ lib/Driver/ToolChains/DragonFly.h
@@ -52,6 +52,7 @@ class LLVM_LIBRARY_VISIBILITY DragonFly
 public:
   DragonFly(const Driver &D, const llvm::Triple &Triple,
             const llvm::opt::ArgList &Args);
+  bool HasNativeLLVMSupport() const override;
 
   bool IsMathErrnoDefault() const override { return false; }
 
