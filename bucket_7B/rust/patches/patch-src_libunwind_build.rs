--- src/libunwind/build.rs.orig	2020-02-24 22:45:57 UTC
+++ src/libunwind/build.rs
@@ -31,7 +31,7 @@ fn main() {
     } else if target.contains("solaris") {
         println!("cargo:rustc-link-lib=gcc_s");
     } else if target.contains("dragonfly") {
-        println!("cargo:rustc-link-lib=gcc_pic");
+        println!("cargo:rustc-link-lib=gcc_s");
     } else if target.contains("pc-windows-gnu") {
         println!("cargo:rustc-link-lib=static-nobundle=gcc_eh");
         println!("cargo:rustc-link-lib=static-nobundle=pthread");
