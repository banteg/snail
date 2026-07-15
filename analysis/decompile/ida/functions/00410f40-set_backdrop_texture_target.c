/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_backdrop_texture_target @ 0x410f40 */
/* selector: set_backdrop_texture_target */

// Stable Windows harness identity for the authored cRBackdrop::SetWorld(int) member. It flips both owned world-blend fractions, shifts each current world into its previous slot, and installs the new world in both 0x20-byte BackdropWorldBlend records.
void __thiscall set_backdrop_texture_target(Backdrop *backdrop, int32_t world)
{
  double v2; // st7
  int32_t current_world; // edx
  double v4; // st7

  v2 = 1.0 - backdrop->primary_world_blend.blend;
  current_world = backdrop->secondary_world_blend.current_world;
  backdrop->primary_world_blend.previous_world = backdrop->primary_world_blend.current_world;
  backdrop->primary_world_blend.current_world = world;
  backdrop->secondary_world_blend.previous_world = current_world;
  backdrop->primary_world_blend.blend = v2;
  v4 = 1.0 - backdrop->secondary_world_blend.blend;
  backdrop->secondary_world_blend.current_world = world;
  backdrop->secondary_world_blend.blend = v4;
}
