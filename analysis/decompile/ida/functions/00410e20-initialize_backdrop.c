/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_backdrop @ 0x410e20 */
/* selector: initialize_backdrop */

// Initializes the shared backdrop renderer, seeds its texture-transition state, and primes its distortion grid. Cross-port Android and iOS symbols match this helper to `cRBackdrop::Init(int)`.
void __thiscall initialize_backdrop(Backdrop *backdrop, int32_t last_mode)
{
  backdrop->unknown_65c = 1;
  backdrop->unknown_660 = 0;
  backdrop->active_primary_texture_id = -1;
  backdrop->backdrop_change_queued = 0;
  backdrop->zoom = 0.0;
  backdrop->unknown_6c4 = 5;
  backdrop->unknown_6bc = 0.0;
  backdrop->unknown_6c0 = 0.0033333334;
  set_backdrop_texture_target(backdrop, 5);
  if ( (g_runtime_config.render_flags & 1) != 0 )
  {
    backdrop->backdrop_render_enabled = 1;
    backdrop->unknown_664 = 1.0;
  }
  else
  {
    backdrop->backdrop_render_enabled = 0;
    backdrop->unknown_664 = 0.0;
  }
  backdrop->unknown_668 = 0.020833334;
  if ( !last_mode )
  {
    backdrop->unknown_66c = 0.0;
    backdrop->unknown_670 = 0.0013089969;
    backdrop->unknown_674 = 0.0;
    backdrop->unknown_678 = 0.0017453294;
    goto LABEL_8;
  }
  if ( last_mode == 1 )
  {
    backdrop->unknown_66c = 0.0;
    backdrop->unknown_670 = -0.0026179939;
    backdrop->unknown_674 = 0.0;
    backdrop->unknown_678 = -0.0034906587;
LABEL_8:
    backdrop->primary_world_blend.previous_world = 0;
    backdrop->primary_world_blend.current_world = 0;
    backdrop->primary_world_blend.blend = 1.0;
    backdrop->primary_world_blend.blend_step = 0.0055555557;
    backdrop->secondary_world_blend.previous_world = 0;
    backdrop->secondary_world_blend.current_world = 0;
    backdrop->secondary_world_blend.blend = 1.0;
    backdrop->secondary_world_blend.blend_step = 0.0041666669;
  }
  set_backdrop_texture_target(backdrop, 0);
  set_backdrop_distort(backdrop, 0.0);
}
