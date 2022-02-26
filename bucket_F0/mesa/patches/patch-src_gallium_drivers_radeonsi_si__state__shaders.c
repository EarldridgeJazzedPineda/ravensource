--- src/gallium/drivers/radeonsi/si_state_shaders.c.orig	2022-02-09 20:10:39 UTC
+++ src/gallium/drivers/radeonsi/si_state_shaders.c
@@ -2228,6 +2228,7 @@ static void si_build_shader_variant(stru
       return;
    }
 
+#ifndef __sun
    if (shader->compiler_ctx_state.is_debug_context) {
       FILE *f = open_memstream(&shader->shader_log, &shader->shader_log_size);
       if (f) {
@@ -2235,6 +2236,7 @@ static void si_build_shader_variant(stru
          fclose(f);
       }
    }
+#endif
 
    si_shader_init_pm4_state(sscreen, shader);
 }
