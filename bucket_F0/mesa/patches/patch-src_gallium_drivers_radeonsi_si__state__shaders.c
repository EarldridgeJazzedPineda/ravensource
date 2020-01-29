--- src/gallium/drivers/radeonsi/si_state_shaders.c.orig	2020-01-28 19:07:35 UTC
+++ src/gallium/drivers/radeonsi/si_state_shaders.c
@@ -2115,6 +2115,7 @@ static void si_build_shader_variant(stru
 		return;
 	}
 
+#ifndef __sun__
 	if (shader->compiler_ctx_state.is_debug_context) {
 		FILE *f = open_memstream(&shader->shader_log,
 					 &shader->shader_log_size);
@@ -2123,6 +2124,7 @@ static void si_build_shader_variant(stru
 			fclose(f);
 		}
 	}
+#endif
 
 	si_shader_init_pm4_state(sscreen, shader);
 }
