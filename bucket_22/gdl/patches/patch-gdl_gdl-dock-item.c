--- gdl/gdl-dock-item.c.orig	2018-10-22 19:36:04 UTC
+++ gdl/gdl-dock-item.c
@@ -355,7 +355,7 @@ gdl_dock_item_class_init (GdlDockItemCla
     container_class->set_focus_child = gdl_dock_item_set_focus_child;
     gtk_container_class_handle_border_width (container_class);
 
-    gdl_dock_object_class_set_is_compound (object_class, FALSE);
+    gdl_dock_object_class_set_is_compound ((GdlDockObjectClass *)object_class, FALSE);
     dock_object_class->dock_request = gdl_dock_item_dock_request;
     dock_object_class->dock = gdl_dock_item_dock;
     dock_object_class->present = gdl_dock_item_present;
@@ -744,7 +744,7 @@ gdl_dock_item_set_property  (GObject
         case PROP_RESIZE:
             item->priv->resize = g_value_get_boolean (value);
             {
-                GObject * parent = gtk_widget_get_parent (GTK_WIDGET (item));
+                GObject * parent = (GObject *)gtk_widget_get_parent (GTK_WIDGET (item));
                 //if we docked update "resize" child_property of our parent
                 if(parent)
                 {
