--- src/common/translation.cpp.orig	2017-04-29 12:00:38 UTC
+++ src/common/translation.cpp
@@ -1471,7 +1471,7 @@ wxArrayString wxTranslations::GetAvailab
 
 bool wxTranslations::AddStdCatalog()
 {
-    if ( !AddCatalog(wxS("wxstd")) )
+    if ( !AddCatalog(wxS("wxstd") wxSTRINGIZE(wxMAJOR_VERSION) wxSTRINGIZE(wxMINOR_VERSION)) )
         return false;
 
     // there may be a catalog with toolkit specific overrides, it is not
