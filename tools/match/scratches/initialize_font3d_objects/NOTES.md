# initialize_font3d_objects

Initial relationship scratch for the 3D font object builder at `0x44ae10`.

Recovered relationships:

- This is not a sprite path. It allocates one BOD/object record per registered
  glyph and loads `Objects/Font3D`.
- The scratch uses the promoted `BodBase` render-object fields: `set_bod_object`
  fills `object +0x24`, then the font setup clears render arguments `+0x1c` and
  `+0x20` before populating the object quad.
- `FontSheet::glyph_width[index] / line_marker_y` is cached in
  `g_font3d_scales[index]` and scales four x-coordinate lanes in the object
  vertex array.
- The facequad texture pointer is selected from `texture_ref_a/texture_ref_b`
  through `FontSheet::texture_page[index]`.
- The UV quad uses `u0[index]`, `v0[index]`, `1.0f - line_step`, and
  `1.0f - line_marker_fraction`.

Initial match: 40.00%, 94 candidate instructions versus 126 target
instructions. The residual is mostly cursor/register ownership: native walks
the object pointer field at `data_77550c`, the scale cache at
`g_font3d_scales`, and the atlas arrays as separate cursors. The current
scratch keeps those as narrow named globals; masked audit is `8 ok / 0
unresolved / 1 mismatch`.

2026-06-20 scale-cache curation: `0x7770e8` is now named `g_font3d_scales`.
The remaining named mismatch is the native `ebp` scale-cache cursor aligned
against the candidate's `g_font3d_bods+0x1c` cursor. A scale-only cursor source
rewrite was neutral at 40.00%, while a broader object/atlas/scale cursor
rewrite regressed to 32.00%, so the register-ownership residual is left visible.

2026-06-21 object-call reload pass:

- Reloading `bod->object` for the `load_object_definition("Objects/Font3D", ...)`
  call, while keeping the existing `object` local for the following quad,
  vertex, ready, and flag writes, improves the focused matcher from 40.00% to
  44.34%. The candidate grows from 94 to 95 instructions, keeps the 3/126
  prefix, and adds one clean masked operand.
- Reloading the object again for the final flag OR clears the old
  `g_font3d_scales` versus `g_font3d_bods` mask mismatch, but scores lower at
  43.24%, so the higher-scoring loader-call reload is retained and the cursor
  mismatch remains documented.
- Removing the cached facequad pointer, removing the cached vertices pointer,
  combining those removals, and removing the texture-ref local all regress or
  stay neutral. Those forms add instructions but lose the current register
  skeleton, so the scratch keeps the local `object`, `quad`, and `vertices`
  views after the loader call.
- Moving the `object` local until after the load/clear block collapses the
  prologue and drops below 30%, while scale-cursor variants around
  `g_font3d_scales` regress to roughly 36%. Keep the indexed scale store until
  a stronger object-field cursor lead appears.
