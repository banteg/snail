/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: draw_split_backdrop @ 0x410f90 */
/* selector: draw_split_backdrop */

// Queues the split `_A` / `_B` backdrop textures directly into the sprite renderer when a background script points at a split menu or splash layout.
void __thiscall sub_410F90(int *this)
{
  int *v2; // eax
  int *v3; // eax
  _DWORD v4[4]; // [esp+4h] [ebp-10h] BYREF

  v2 = set_color_rgba(v4, 1065353216, 1065353216, 1065353216, 1065353216);
  queue_axis_aligned_textured_quad_uv(
    *(this + 15),
    0,
    0,
    1140850688,
    1140850688,
    0x8000000,
    v2,
    0,
    0,
    1065353216,
    1065353216,
    0,
    0);
  v3 = set_color_rgba(v4, 1065353216, 1065353216, 1065353216, 1065353216);
  queue_axis_aligned_textured_quad_uv(
    *(this + 17),
    1140850688,
    0,
    1124073472,
    1140850688,
    0x8000000,
    v3,
    0,
    0,
    1065353216,
    1065353216,
    0,
    0);
}

