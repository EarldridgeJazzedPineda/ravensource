$NetBSD: patch-node__modules_node-gyp_gyp_pylib_gyp_generator_make.py,v 1.1 2018/05/02 17:03:09 fhajny Exp $

Ensure we use the system libtool on OSX.

--- node_modules/node-gyp/gyp/pylib/gyp/generator/make.py.orig	1985-10-26 08:15:00 UTC
+++ node_modules/node-gyp/gyp/pylib/gyp/generator/make.py
@@ -208,7 +208,7 @@ cmd_solink_module = $(LINK.$(TOOLSET)) -
 
 LINK_COMMANDS_MAC = """\
 quiet_cmd_alink = LIBTOOL-STATIC $@
-cmd_alink = rm -f $@ && ./gyp-mac-tool filter-libtool libtool $(GYP_LIBTOOLFLAGS) -static -o $@ $(filter %.o,$^)
+cmd_alink = rm -f $@ && ./gyp-mac-tool filter-libtool /usr/bin/libtool $(GYP_LIBTOOLFLAGS) -static -o $@ $(filter %.o,$^)
 
 quiet_cmd_link = LINK($(TOOLSET)) $@
 cmd_link = $(LINK.$(TOOLSET)) $(GYP_LDFLAGS) $(LDFLAGS.$(TOOLSET)) -o "$@" $(LD_INPUTS) $(LIBS)
