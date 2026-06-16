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
the object pointer field at `data_77550c`, the scale cache at `data_7770e8`,
and the atlas arrays as separate cursors. The current scratch keeps those as
narrow named globals; two masked operands remain unresolved for those globals.
