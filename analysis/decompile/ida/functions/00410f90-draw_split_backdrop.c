/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: draw_split_backdrop @ 0x410f90 */
/* selector: draw_split_backdrop */

// Queues the split `_A` / `_B` backdrop textures directly into the sprite renderer when a background script points at a split menu or splash layout.
void __thiscall draw_split_backdrop(int *this)
{
  tColour *v2; // eax
  tColour *v3; // eax
  Color4f color; // [esp+4h] [ebp-10h] BYREF

  v2 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
  queue_axis_aligned_textured_quad_uv(*(this + 15), 0.0, 0.0, 512.0, 512.0, 0x8000000u, v2, 0.0, 0.0, 1.0, 1.0, 0, 0.0);
  v3 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
  queue_axis_aligned_textured_quad_uv(
    *(this + 17),
    512.0,
    0.0,
    128.0,
    512.0,
    0x8000000u,
    v3,
    0.0,
    0.0,
    1.0,
    1.0,
    0,
    0.0);
}
