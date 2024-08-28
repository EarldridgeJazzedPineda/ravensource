--- src/freebsd/up-device-supply.c.orig	2024-04-08 15:36:47 UTC
+++ src/freebsd/up-device-supply.c
@@ -250,7 +250,7 @@ up_device_supply_battery_set_properties
 		      "energy", cap,
 		      "energy-full", lastfull,
 		      "energy-full-design", dcap,
-		      "energy-rate", rate,
+		      "energy-rate", (battinfo.battinfo.state & ACPI_BATT_STAT_CHARGING) ? -rate : rate,
 		      "energy-empty", lcap,
 		      "voltage", volt,
 		      "capacity", capacity,
