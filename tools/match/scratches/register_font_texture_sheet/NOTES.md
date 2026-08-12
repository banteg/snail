# register_font_texture_sheet

Current recovery: semantic-complete (`compiler` residual). The live Windows
function, its sole startup caller, the exact TGA pixel sampler, and every
native font consumer establish the complete Windows marker-atlas registrar,
including the split-page path, 128 glyph lanes, scaling, shadow displacement,
and returned font index. Android/iOS `FontLoad(char*, int, float, float)`
bodies corroborate the parameter and single-font ownership model but use a
metadata file rather than Windows' marker scan, so they are not claimed as
implementation-identical. All 57 Windows references are clean; the 275/274
candidate's remaining delta is equivalent glyph-slot versus split-coordinate
stack/register allocation.

Initial relationship scratch for the font atlas registration helper at
`0x449f50`.

Recovered relationships:

- The helper loads a TGA-like font atlas and scans row 0 for white marker pixels.
  Those markers seed `FontSheet::glyph_width`, `glyph_u0`, `glyph_u1`, and
  `texture_page`.
- `TgaImageView` is shared with `sample_tga_pixel_rgb` in
  `tools/match/include/tga_image_view.h`.
- Width `0x800` is a two-page atlas. Native rewrites the source basename into
  `...0.tga` and `...1.tga`, uses split x `0x3c0`, and marks both texture refs
  with `TEXTURE_REF_REGISTERED | TEXTURE_REF_RETAIN_SOURCE_BYTES` (`0x420`).
- Non-split atlases store only `texture_ref_a` and reassert
  `TEXTURE_REF_REGISTERED` (`0x400`).
- Both scale parameters are floats. The third argument is stored directly in
  `FontSheet::width_scale`; the exact forwarding wrapper confirms the ABI.
- `shadow_offset_pixels` is later read by `draw_font_text_instance` as the
  positive X/Y displacement of the black glyph pass.

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
  `slot_count`/`shadow_offset_pixels` tail: native keeps split x in `ebx` and the glyph
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
the existing `slot_count`/`shadow_offset_pixels` owner mismatch).

The analysis databases now agree on the two float scale parameters, the
`FontSheet` owner, and the one-sheet bank boundary at `g_registered_font_count`.
The refreshed snapshots expose the atlas, texture-reference, marker, and scale
fields without altering the matcher source or hiding the documented register
ownership residual.

## 2026-07-23 atlas image lifetime

The restarted Binary Ninja database initially skipped this function after
exceeding its analysis-time budget. The canonical font replay now pins the
registrar to `NeverSkipFunctionAnalysis`, restores HLIL, types the
`load_file_bytes` result as `TgaImageView*`, and records its sole retained
lifetime as `image`. The decompile consequently exposes `image->width`,
`image->height`, both typed `sample_tga_pixel_rgb(image, ...)` calls, and the
terminal `free_tracked_memory(image)` ownership release.

IDA independently corroborates the same `+0x0c` width, `+0x0e` height, and two
sampler callsites in its tracked artifact; its replay now carries the shared
typed helper prototype as well. This is analysis-only: the matcher source is
unchanged, so the honest 75.41% result (`275/274`, 51 clean operands) and the
documented `slot_count`/`shadow_offset_pixels` register-owner residual remain intact.

## 2026-07-23 registrar value ownership

The atlas producer now names its durable native values without introducing a
long-lived `FontSheet*` that the executable does not carry. The split-page
branch owns two `0x100`-byte stack paths plus `split_x`, `path_char`, and
`path_index`; the row-0 scan owns `run_width`, its stack-published
`glyph_run_width`, `last_x`, `glyph_left`, `glyph_slot`, `pixel_color`, and the
two centered atlas coordinates. The column-0 scan separately owns
`line_marker_y`.

The texture registry returns borrowed handles. The split branch retains its
first handle as `page0_texture_ref`, while `flagged_texture_ref` is the final
handle whose flags are committed in both the split-page and single-page paths.
The loaded `TgaImageView` remains the function's sole released allocation.

IDA independently corroborates EBX as the split boundary, EDI/EBP and the
three adjacent stack slots as the x/run/slot scan state, and its two texture
return values as registry handles. One rejected annotation briefly named only
the hidden stack spill of `glyph_left`; the canonical replay explicitly retires
that annotation and names the visible ECX lifetime instead.

No matcher source changed. Focused Wibo therefore remains the honest 75.41%
result (`275/274`, prefix `0/274`, 51 clean masked operands) with the existing
`slot_count`/`shadow_offset_pixels` compiler-owner mismatch still documented rather than
forced.

## 2026-07-24 atlas-coordinate ownership correction

The marker scan publishes centered horizontal run bounds, so the two
per-glyph arrays are `glyph_u0` and `glyph_u1`, not `u0` and `v0`. The
column marker then produces the two shared vertical bounds:
`glyph_v0 = 3 / (height - 1)` and
`glyph_v1 = line_marker_y / (height - 1)`. Both `draw_font_text_instance`
and the vertically flipped Font3D materializer independently consume that
exact U0/V0/U1/V1 contract.

This is a shared-struct naming correction, not a source-shape probe. Focused
Wibo remains honestly at 75.41% with 51 clean operands and the existing
compiler-owner residual.

## 2026-07-24 shadow-offset producer

The sole Windows registration call forwards integer 2 for
`Objects/Font/Font-menu-hover.tga`. The registrar stores it unchanged at
`FontSheet +0x824`; the text renderer requires it to be positive, converts it
to float, and adds it to both glyph coordinates for the black shadow pass.
That producer/consumer chain closes the field and parameter as
`shadow_offset_pixels`, replacing the misleading `font_kind` vocabulary.
The registrar remains at the honest 75.41% frontier with 51 clean operands.

## 2026-07-26 mobile ABI boundary

Android and iOS both retain `FontLoad(char*, int, float, float)` but decompile
their mobile implementation as void. Projecting that return onto Windows was
explicitly tested and rejected: it perturbs the complete VC6 register-lifetime
shape, lowers the focused result from 75.41% to 74.09%, and worsens the
masked-operand residuals.
The native Windows post-increment deliberately leaves the pre-increment sheet
index in EAX, and its exact forwarding wrapper preserves that integer result.

Windows therefore keeps its locally proved integer ABI. Mobile still supplies
the authored owner name and parameter roles, but its `0xa28` metadata-driven
font sheet is also layout-incompatible with the Windows `0x828` atlas owner;
neither the mobile return nor its offsets are transplanted.

## 2026-07-29 bounded glyph-slot ownership sweeps

Two recorded mutation sweeps tested 60 unique source shapes around the sole
remaining register-allocation split. The first exhaustively combined scan-local
declaration orders, three equivalent glyph-slot increments, and three
glyph-run publication orders. The second separated the currently published
glyph index from the next-slot counter, including explicit snapshot,
snapshot-plus-next, and post-increment forms.

No variant improved the 75.41% baseline: 14 compiled byte-for-byte equivalently
and 46 regressed, with no reference-debt tradeoff. In particular, all three
semantic glyph-slot snapshots canonicalized to the existing 275-instruction
candidate. Declaration order and increment spelling therefore do not explain
why native retains `split_x` in EBX while this source lets VC6 cache the glyph
slot there.

The remaining route is evidence recovery, not a wider syntax search: identify
the missing source-level owner that makes the native glyph slot genuinely
memory-resident. A `register` keyword, `volatile`, dummy address escape, or
other forced spill would only encode the desired register assignment and
remains out of scope.

## 2026-07-29 native and mobile provenance closure

Native local storage closes the allocation relationship precisely:
`split_x` is the EBX register owner, `run_width` is carried in EBP, and
`glyph_slot` is a real stack owner at frame offset `-0x204`. The current
candidate instead gives EBX to the glyph slot and spills `split_x`; this is an
owner swap, not evidence for another glyph counter.

The paired mobile `FontLoad(char*, int, float, float)` bodies do not contain
the Windows marker scan. They rewrite the atlas path to a `.txt` metadata path,
parse `SetNumber:` records, and populate a port-specific `0xa28` sheet. They
therefore corroborate the public ABI but cannot supply the missing Windows scan
owner. The Windows-only pixel sampler still has exactly the registrar's two
expected callsites.

Four lexical-lifetime probes hoisted `run_width`, `slot`, and then the complete
`x`/`run_width`/`slot`/`last_x` group to function scope. VC6 emitted the
baseline bytes for every form. Moving the capacity check ahead of `split_x`
initialization moved the exact prefix from zero to one instruction but
regressed focused agreement to 73.95%. A synthetic common glyph-lane cursor is
also rejected: native computes the shared byte offset as an optimizer result,
and no producer or consumer exposes such an authored object.

No source change is retained. At this snapshot the proof-grade frontier was
**75.41%** (`275/274`, 54 accepted operands, one mismatch, and four unaudited
operands); the current matcher now accepts all 57 references as recorded at
the top. Further source-shape work needs Windows provenance for a genuinely
memory-resident glyph index; the recorded declaration and cursor probes do
not supply one.

## 2026-07-29 entry split-lifetime boundary

A final five-variant family records the remaining entry-order question instead
of leaving it as an informal probe. Adding braces around the capacity check is
byte-identical to the 75.41% baseline. Moving `split_x` initialization after
that check—whether declared early or late, and with or without braces—moves the
exact prefix from zero to one instruction but regresses weighted agreement by
15 bytes to 73.95%. All five forms preserve the same 54 accepted operands, one
mismatch, and four unaudited operands, so none resolves the glyph-slot owner
swap.

The ledger contains 65 unique variants across three sweeps: 0 improve, 15 are
byte-identical, and 50 regress. This records the tested declaration, increment,
publication, snapshot, lexical-scope, and entry-order families. The retained
frontier is 75.41%; a
useful future probe needs new Windows provenance or a genuinely different
glyph-index ownership model.
