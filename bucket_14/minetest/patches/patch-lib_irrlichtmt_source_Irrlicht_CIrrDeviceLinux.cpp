--- lib/irrlichtmt/source/Irrlicht/CIrrDeviceLinux.cpp.orig	2022-02-05 15:24:05 UTC
+++ lib/irrlichtmt/source/Irrlicht/CIrrDeviceLinux.cpp
@@ -715,7 +715,7 @@ EKEY_CODE CIrrDeviceLinux::getKeyCode(XE
 	}
 	if (keyCode == 0)
 	{
-		keyCode = KEY_UNKNOWN;
+		keyCode = (EKEY_CODE)KEY_UNKNOWN;
 		if ( !mp.X11Key )
 		{
 			os::Printer::log("No such X11Key, event keycode", core::stringc(event.xkey.keycode).c_str(), ELL_INFORMATION);
