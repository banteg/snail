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
  with `TEXTURE_REF_REGISTERED | TEXTURE_REF_RETAIN_SOURCE_BYTES` (`0x420`).
- Non-split atlases store only `texture_ref_a` and reassert
  `TEXTURE_REF_REGISTERED` (`0x400`).
- Both scale parameters are floats. The third argument is stored directly in
  `FontSheet::width_scale`; the exact forwarding wrapper confirms the ABI.
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
each write site instead of carrying a sheet pointer through the scan. That pass
temporarily reversed the initial `u0`/`v0` stores based on the then-incomplete
run-width model; the later native dataflow audit below corrects them. Rejected
neighbors included a count snapshot, late `FontSheet*` declarations,
`register`/uninitialized `split_x`, and pointer/direct hybrids.

2026-07-12 delimiter-state and atlas ownership pass:

- Each row-0 white marker publishes the completed glyph run and resets
  `run_width` to zero. The missing reset was a real semantic bug: without it,
  VC6 correctly collapsed the counter to `x - 1`.
- The initial coordinates are `u0 = centered glyph-left / width` and
  `v0 = centered current-x / width`, consistent with both split-page branches.
  This clears the stale atlas-coordinate operand mismatch.
- The column-0 scan publishes `line_marker_y` only when it actually finds a
  white marker. Reaching the image height exits without inventing a marker.
- Split suffix bytes are written to page 1 then page 0 in the native order,
  both scale arguments retain float ownership, and the registrar returns the
  post-incremented registered-font index.
- Focused Wibo improves from 72.46% (267/274, 48 clean operands) to 75.41%
  (275/274, 51 clean operands). The only masked mismatch remains the adjacent
  `slot_count`/`font_kind` tail: native keeps split x in `ebx` and the glyph
  slot on the stack, while VC6 assigns those two owners oppositely in the
  candidate, adding one four-byte local. No forced spill or dummy dependency is
  used to hide that residual.

## 2026-07-14 fixed font-bank extents

The native globals close the remaining fixed capacities without inference:
one `0x828`-byte `FontSheet` starts at `0x7772f8` and ends exactly at
`g_registered_font_count` (`0x777b20`), while each sheet owns 128 entries in
all four glyph lanes. The registrar now checks `FONT_SHEET_CAPACITY` and
`FONT_GLYPH_CAPACITY`, and `g_font_sheets` carries its real one-element extent.

The source-only ownership change preserves the normalized candidate listing
byte-for-byte
(`35f3e3abff48d6ec831ea4e200f079034f640ba6b4e0c16d6668f4af4ed09e49`)
and the honest 75.41% result (`275/274`, prefix `0/274`, 51 clean operands and
the existing `slot_count`/`font_kind` owner mismatch).

The analysis databases now agree on the two float scale parameters, the
`FontSheet` owner, and the one-sheet bank boundary at `g_registered_font_count`.
The refreshed snapshots expose the atlas, texture-reference, marker, and scale
fields without altering the matcher source or hiding the documented register
ownership residual.
