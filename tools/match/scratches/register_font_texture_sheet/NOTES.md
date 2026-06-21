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

2026-06-21 atlas field-order pass: focused Wibo improves to 72.46%, with
267/274 candidate/target instructions and 48 clean masked operands, by dropping
the long-lived `FontSheet* sheet` pointer and writing
`g_font_sheets[g_registered_font_count]` fields directly. This matches native's
habit of reloading the registered-font index and recomputing the sheet base at
each write site instead of carrying a sheet pointer through the scan. The
initial non-split coordinate stores are also reversed relative to the earlier
source (`v0` gets the centered left edge, `u0` gets the centered current-x edge);
that removes the atlas-coordinate masked mismatch while leaving the split-atlas
override stores in their previous order. Rejected neighbors: a count snapshot,
late `FontSheet*` declarations, `register`/uninitialized `split_x`, swapping all
`u0`/`v0` writes, and pointer/direct hybrids were either much lower or kept the
same operand debt. The remaining masked mismatch is the adjacent
`slot_count`/`font_kind` tail: both stores are present, but VC6 keeps the slot
count in `ebx` while native reloads it into `ecx` before writing
`FontSheet +0x000`.
