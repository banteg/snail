# draw_font_text_instance

Initial relationship scratch for the text queue renderer at `0x44a360`.

Recovered relationships:

- The native argument is a `cFontPrintBuffer*`; the old `float arg1` decompiler
  type is wrong.
- `horizontal_align` values `1/2/3` adjust the local x cursor from `anchor_x +
  320.0f`, with value `2` centering by half the measured width.
- Each glyph maps through `font_slot_index_for_char`, uses `FontSheet` atlas
  UVs/texture-page lanes, then calls `draw_textured_quad_immediate`.
- `FontSheet::shadow_offset_pixels` is the positive shadow offset used only when
  `shadow_enabled` is set; it is not a font-family enum.
- Slot `0x35` advances the cursor without drawing.

Initial match: 32.66%, 224 candidate instructions versus 272 target
instructions. The residual is mostly source scheduling/register shape around
the glyph loop, shadow draw, and per-glyph advance. No masked operands were
unresolved or mismatched in the initial run.

2026-06-21 glyph-loop shape pass:

- Reading the initial atlas UV/page fields directly through
  `g_font_sheets[font_id]`, while keeping a `FontSheet*` for the later texture,
  sizing, and advance fields, improves the per-glyph setup from 32.66% to
  33.47%.
- Replacing the staged `ch` local with a direct cursor-deref loop recovers the
  native `0x38` frame and the first instruction prefix. Combined with the
  direct initial atlas reads, the focused matcher improves to 35.67%, with
  227/272 candidate instructions, a 1/272 prefix, and 19 clean masked operands.
- Fully removing the `FontSheet*` pointer only reaches 32.68%, and combining it
  with the direct atlas reads stays there. Delaying the sheet pointer past the
  direct reads was not a valid source shape because later advance code still
  needs the sheet outside the draw block.
- Register hints, a copied `cFontPrintBuffer*`, a copied or volatile text cursor,
  and register/copy combinations are all codegen-neutral at 35.67%; they do not
  move the top-level entry pointer from candidate `edi` to native `esi`.
- Returning zero regresses to 35.34%, and explicit byte/int return locals are
  neutral. The independent Android symbol is
  `FontPrintReal(cFontPrintBuffer*)`; its incidental terminating-byte result is
  ignored by `FontPrintRender`, exactly as the Windows queue drain ignores EAX.
  Recovering the authored `void` contract removes the synthetic return and
  moves the honest focused result marginally from 35.67% (227/272) to 35.70%
  (221/272), with the same 19 clean masked operands.

2026-07-14 analysis ownership closure:

- Android's `cFontPrintBuffer` name is now backed by the exact Windows
  `0x84`-byte queue record, including its authored `tColour` member at `+0x6c`.
- Binary Ninja and IDA now agree on the `void(cFontPrintBuffer*)` contract and
  expose the text, alignment, scale, color, and `FontSheet` fields throughout
  the tracked decompiles.
- No matcher source changed. The honest 35.70% result remains visible; this
  slice recovers durable ownership rather than forcing a compiler schedule.

## 2026-07-23 horizontal cursor lifetime

VC6 copies the borrowed `cFontPrintBuffer*` argument into `esi`, then reuses
the incoming `[esp+4]` argument slot as the float horizontal cursor. IDA
independently exposes that recycled slot as `entrya`; Binary Ninja previously
rendered its stores and arithmetic as assignments to, and floating-point
conversions of, the entry pointer.

The canonical Binary Ninja replay now pins this function against analysis
skipping and merges all five cursor definitions plus the three SSA joins into
one `float cursor_x` lifetime. The tracked decompile consequently preserves
`entry->...` for queue-record ownership while using `cursor_x` for alignment,
wave displacement, and per-glyph advance. No matcher source changed, so the
honest 35.70% result and 19 clean masked operands remain unchanged.

## 2026-07-23 glyph-loop lifetimes

The native `eax` register has three unrelated owners: initial horizontal
alignment, the current text byte, and the integer glyph-width advance. Its
intervening calls also clobber `eax`. Binary Ninja previously folded the byte
and width result back into `horizontal_align`; IDA independently keeps them as
the loop byte and integer advance.

The canonical replay now splits the four byte/PHI definitions into
`current_char` and the terminal conversion into `glyph_advance`, without
merging either with alignment or call-clobber state. Stable locals additionally
name the borrowed `text_cursor`, its shadow-call resume slot, `glyph_slot`,
wave index, atlas UV/page tuple, draw coordinates, shadow offset, and shadow
color. These are value lifetimes over the existing `FontSheet` and
`cFontPrintBuffer` owners, not new storage or a synthetic aggregate.

No matcher source changed. Focused Wibo remains 35.70%, with 221 candidate
instructions versus 272 target instructions, a 1/272 prefix, and all 19 masked
operands clean.

## 2026-07-24 atlas and texture-borrow ownership

The shared `draw_textured_quad_immediate` prototype fixes the UV argument order
as U0, V0, U1, V1. The registrar independently shows that its two per-glyph
arrays contain centered horizontal bounds, while its two sheet-wide scalars
contain the vertical bounds. `FontSheet` therefore now names these lanes
`glyph_u0`, `glyph_u1`, `glyph_v0`, and `glyph_v1`; the former `v0`,
`line_step`, and `line_marker_fraction` names mixed axes and producer syntax.

The guarded Binary Ninja replay also retains the short-lived borrowed
`shadow_texture` and `glyph_texture` handles plus the two wave phases and
horizontal wave offset. IDA independently preserves the same texture-array
loads and reused phase stack slot. These are values borrowed from the one
registered `FontSheet`; neither draw call owns or releases a texture.

Matcher code only follows the corrected field vocabulary. Focused output is
expected to remain the honest 35.70%, 221/272-instruction frontier with all 19
operands clean; no register-shaped source or dummy dependency is introduced.

## 2026-07-24 font-shadow ownership

The wave and shadow controls are independent. Both Windows decompilers show
that `text_wave_amplitude +0x34` always scales the per-character sine/cosine
offsets, while byte `+0x38` gates only the optional second glyph draw. That
second draw uses black at 0.8 alpha, blend mode 2, and the positive
`FontSheet::shadow_offset_pixels` before the normal colored glyph draw. The queue
record field is therefore `shadow_enabled`, not `text_wave_enabled`.

A fresh IDA 9.3 export from a temporary database copy independently reproduces
the same nested gate and two draw calls. Android retains the `+0x38` queue
byte but its port-specific renderer submits only the colored glyph pass, so no
mobile-only behavior was transplanted into Windows. The vocabulary correction
is codegen-neutral here: focused Wibo remains the honest 35.70%, 221/272
instructions, with all 19 masked operands clean.

## 2026-07-24 proof-grade render-pass ownership

The exact VC6 source shape does not retain one `FontSheet*`, resolved texture,
or width/height pair across the two render passes. Each pass independently
reborrows the texture ref selected by the saved integer texture page and
re-evaluates its glyph width, line marker, text scale, and sheet spacing. The
same direct sheet ownership is used again for the integer cursor advance.

The shadow block supplies two further source-level proofs:

- `shadow_offset_pixels` remains an integer field for the positive gate. Its
  float casts are written directly in the x/y arguments; VC6 common-subexpression
  elimination emits the one converted temporary seen by both decompilers.
- `tColour::set_color_rgba(0, 0, 0, 0.8)` is the color argument to
  `draw_textured_quad_immediate`, not a separate setter statement. VC6 therefore
  evaluates it after pushing the outer call's rotation and blend arguments,
  exactly as the native instruction stream does.

Removing the cross-pass aliases and retaining those direct argument expressions
raises the focused result from the honest 35.70% frontier to 100.00%:
272/272 instructions, a 272-instruction prefix, and all 41 masked operands
resolved with no mismatches. Binary Ninja reproduces the borrowed queue entry,
saved texture page, two sheet-backed passes, and integer advance. A fresh IDA
9.3 export from a temporary database copy is byte-for-byte identical to the
tracked export apart from the database-path banner. No register hints,
volatile spills, dummy relocations, or other fakematching are present.
