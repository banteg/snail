# queue_textured_quad_corners

Initial scratch for the arbitrary four-corner textured quad queue helper at
`0x44aac0`.

Wibo result: 64.29%, 69 target instructions versus 71 candidate instructions,
masked operands 11 ok. The helper's entry/overflow gates, queue stores, and
caller stack layout are pinned; remaining residual is the same shared-zero
epilogue distance plus queue-store register scheduling seen in the other quad
producers.

Recovered relationships:

- Uses the shared `g_render_queue_active` gate and `g_font_queue_count` maximum
  as the other 2D queue producers.
- Appends a quad entry (`flags | 2`) into the shared `cFontPrintBuffer` array.
- Stores texture id (`+0x50`), all four authored corner pairs (`+0x04/+0x08`,
  `+0x10/+0x14`, `+0x1c/+0x20`, `+0x28/+0x2c`), explicit UV bounds
  (`+0x5c..+0x68`), `tColour` (`+0x6c`), integer blend mode (`+0x7c`), and
  float rotation (`+0x80`).
- Both known callers pass two zero stack slots after the corner pairs and
  before the flags/color arguments; the helper does not consume them.
- Clears the axis-aligned width/height lanes (`+0x54/+0x58`) so the draw
  forwarder uses the stored corner coordinates instead.

2026-06-20 render-queue chunk: removing the final `return 0` matches the
decompiler's incidental-return shape in spirit, but Wibo aborts through the
MSVC missing-return warning path (`missing import lstrcpynA`) before producing
an object. This is the same harness limitation documented for other incidental
return scratches, so the explicit final zero remains. The residual masked
operand mismatches are still queue-store scheduling around the
UV/blend-mode/rotation
tail, not evidence that the two unused zero arguments are consumed.

2026-06-21 count-store sweep: moving `g_font_queue_count = index + 1` later in
the entry-fill sequence improves focused Wibo from 64.29% to 87.14%, with 71
candidate instructions versus 69 target instructions and 18 clean masked
operands. The best-scoring spelling publishes the count after the final corner
coordinate (`y3`) and before clearing the axis-aligned width/height lanes;
placing it after the height clear removed the residual masked mismatches but
scored lower at 81.43%. Keep the corner-coordinate placement as the retained
shape for now.

2026-06-21 color/count split retry: native publishes the queue count between
the RGB and alpha lanes of the aggregate `tColour` copy, but spelling that
split in source is much worse. RGB/count/alpha, earlier split points, explicit
RGBA then count, and delayed alpha variants all collapse to the 20-45% family
with a different prologue and many offset mismatches. The aggregate color copy
plus post-`y3` count store remains the best corner-quad source shape.

2026-07-09 field-order campaign: count-after-width/height still cleans the
masked audit at 81.43% (worse score). Count-at-end, color-after-corners,
UV-helper order, rotation-before-blend-mode, and early width/height all score
≤87.14% and usually dirty the UV/blend-mode/rotation offsets. Keep post-`y3`
count at 87.14%
with the two known masked schedule mismatches.

## 2026-07-14 font queue ownership closure

The recovered producer ABI now names the final fields as integer `blend_mode`
and float `rotation`, matching their downstream renderer types in both
analysis databases. The focused candidate stays at `87.14%` (`71/69`, 18 clean
operands and two real scheduling mismatches). No source distortion was added
to conceal the remaining aggregate-color/count-store ordering gap.

## 2026-07-23 embedded color owner

The native `esi` lifetime starts at the embedded queue-entry color and advances
through its four float lanes. Binary Ninja now types that destination as
`tColour* entry_color`, in agreement with IDA's named `p_color` RGBA stores.
The matcher source remains untouched and focused Wibo stays honestly at 87.14%
(`71/69`, prefix `3/69`, 20 clean operands and no masked mismatches).

## 2026-07-24 partial return contract

The corner producer likewise leaves its appended byte offset or the overflow
reporter result in EAX, while an inactive queue falls through with incidental
register state. Binary Ninja's two callers do not establish a shared authored
result: `render_backdrop` discards it, and the now-void `cRGalaxy::Line`
member merely lets the successful tail value survive incidentally.

Disabling only C4715 locally lets VC6 emit that native fallthrough without
changing compiler flags. Removing the invented zero epilogue raises focused
matching from 87.14% (`71/69`) to 89.86% with exact `69/69` instruction parity,
a 33-instruction prefix, and all 20 operands clean. The remaining differences
are queue-count and argument-load scheduling after the aggregate color copy,
not missing queue fields or a forced skip result.

## 2026-07-25 long OSDPrintUV ABI closure

iOS 1.5, iOS 1.9, and Android all retain the authored long overload as
`OSDPrintUV(int, float, float, float, float, float, float, float, float,`
` float, float, int, tColour, float, float, float, float, int, float)`.
Their bodies copy the first eight floats into the four x/y corner pairs, ignore
the final two pre-flag floats, and explicitly clear the queued width/height
fields. The Windows `unused_28` and `unused_2c` formals are consequently floats,
not integers.

The same three ports preserve four 12-byte x/y/third-lane coordinate cadences
inside `cFontPrintBuffer`; the dormant third lanes are now typed as float
`z0..z3`. Neither mobile nor Windows code consumes those lanes. These are
ABI/type corrections only: the focused Windows scratch stays at the honest
89.86% frontier with no scheduling barrier or fake data access.

## 2026-07-26 platform return ABI audit

Android and iOS both declare the long `OSDPrintUV` overload void. Windows still
requires its integer queue-offset signature to reproduce the native append
address schedule: a natural void probe falls from 89.86% to 57.97%.

The mobile declaration does, however, resolve its caller: Android
`cRGalaxy::Line` is explicitly void, every Windows line caller discards EAX,
and changing only that enclosing member preserves its exact 67/67 body. The
queue helper stays integer on Windows while the recovered galaxy owner becomes
void; neither boundary is fakematched.

## 2026-07-29 bounded publication and tail-lifetime audit

Four recorded sweeps cover 26 source variants across the embedded color owner,
queue-count expression, seven publication positions, and the
UV/blend/rotation tail. Fifteen pointer, reference, count-carrier, and named
zero forms are byte-identical to the 89.86%, 69/69, prefix-33 baseline. A full
color value snapshot and three tail value-snapshot families regress; every
publication move is worse, including the target-motivated placement directly
after the aggregate color assignment.

That early placement does publish the count near native, but frees `ecx` and
causes all eight corner loads plus alternating tail lanes to move out of their
native registers. Recomputing the returned byte offset from `index` does not
preserve the lost lifetime. Conversely, the retained post-`y3` placement keeps
the native corner schedule while leaving two independent backend residuals:
native interleaves count publication before the aggregate alpha store and uses
one sequential `edx` chain for the UV/blend/rotation arguments; VC6 emits the
count after `y3` and pipelines those arguments through `ecx`/`edx`.

The short verified `OSDPrintUV` sibling emits the sequential tail naturally
from the same direct field assignments, so no missing queue field or invented
setter is justified here. The long overload remains at its honest frontier
without a barrier, volatile carrier, fake helper, or ABI distortion.

## 2026-08-12 recovery classification

The recovery is semantic-complete. The live Windows decompile and both mobile
symbols agree on the full long `OSDPrintUV` ABI, including the two unused float
slots. The Windows body accounts for the queue gate and limit, every corner,
UV, color, blend, rotation, texture, flag, width/height, count-publication, and
incidental queue-offset result. All 69 native instructions and all 24
references are represented.

The remaining 89.86% delta is only aggregate-color/count publication and
argument-load scheduling. It does not leave a queue field, formal, or caller
contract unresolved, and the historical mutation count is not used to decide
completeness.
