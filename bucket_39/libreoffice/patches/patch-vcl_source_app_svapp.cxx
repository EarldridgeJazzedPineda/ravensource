--- vcl/source/app/svapp.cxx.orig	2019-04-10 10:10:51 UTC
+++ vcl/source/app/svapp.cxx
@@ -1103,7 +1103,7 @@ OUString Application::GetHWOSConfInfo()
         aDetails.append( VclResId(SV_APP_DEFAULT) );
     aDetails.append( "; " );
 
-#if (defined LINUX || defined _WIN32 || defined MACOSX)
+#if (defined LINUX || defined _WIN32 || defined MACOSX || defined FREEBSD || defined __DragonFly__)
     aDetails.append( SV_APP_VCLBACKEND );
     aDetails.append( GetToolkitName() );
     aDetails.append( "; " );
