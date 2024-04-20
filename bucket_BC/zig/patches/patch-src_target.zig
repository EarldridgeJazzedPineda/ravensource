--- src/target.zig.orig	2024-04-19 21:00:35 UTC
+++ src/target.zig
@@ -288,7 +288,7 @@ pub fn libcFullLinkFlags(target: std.Tar
     // The linking order of these is significant and should match the order other
     // c compilers such as gcc or clang use.
     return switch (target.os.tag) {
-        .netbsd, .openbsd => &[_][]const u8{
+        .netbsd, .openbsd, .freebsd, .dragonfly => &[_][]const u8{
             "-lm",
             "-lpthread",
             "-lc",
