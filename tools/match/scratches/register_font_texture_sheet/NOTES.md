# register_font_texture_sheet

Initial relationship scratch for the font atlas registration helper at
`0x449f50`.

Recovered relationships:

- The helper loads a TGA-like font atlas and scans row 0 for white marker pixels.
  Those markers seed `FontSheet::glyph_width`, `u0`, `v0`, and `texture_page`.
- `TgaImageView` is shared with `sample_tga_pixel_rgb` in
  `tools/match/include/tga_image_view.h`.
- Width `0x800` is a two-page atlas. Native rewrites the source basename into
  `...0.tga` and `...1.tga`, uses split x `0x3c0`, and marks both texture refs
  with `0x420`.
- Non-split atlases store only `texture_ref_a` and mark it with `0x400`.
- `width_scale_bits` is stack-compatible raw float bits from the one known
  caller; the stored field is `FontSheet::width_scale`.
- `font_kind` is later read by `draw_font_text_instance` as a positive shadow
  pixel offset.

Initial match: 27.78%, 230 candidate instructions versus 274 target
instructions. The residual is source order/register ownership around the atlas
scan and line-marker discovery; the current source intentionally favors named
`FontSheet` fields and the shared `TgaImageView` over raw address arithmetic.
No masked operands were unresolved or mismatched in the initial run.
