# cRBorder::RePosition @ 0x4024a0

Current recovery: exact. Binary Ninja types
the Windows entry as `void __thiscall(FrontendWidget*)`; all 24 Windows callers
discard `eax`. Android and iOS independently retain the same owner and method as
`cRBorder::RePosition()` in `Border.o`.

The body selects sprite, authored-rectangle, or measured-text geometry; clamps
the hit rectangle unless off-screen placement is allowed; and recursively
repositions the attached slider children. The shared field layout is supported
by the initializers, draw path, mouse path, and mobile bodies.

Focused VC6 result: **100%**, 177/177 instructions, prefix 177, with all
20 reference operands clean. The dated partial results below are historical;
the September recursive-source recovery disproves the earlier compiler-only
attribution.

The matcher source now uses the authored `RePosition` method and exact VC6
symbol `?RePosition@cRBorder@@QAEXXZ`; `layout_frontend_widget` remains only the
stable scratch and Windows-address identity.

## 2026-09-04 source-shape reopening

The compiler-only attribution above is withdrawn; the source residual is open.
Three recorded overlays leave the canonical source unchanged. Replacing the
hit-coordinate integer casts with direct float assignments preserves 99.44%,
177/177 instructions, prefix 66, and all 20 clean references. Restoring the
final recursive `RePosition()` call, removing the enclosing `while`, and turning
its exits into returns gives the same result: VC6 performs the tail-recursion
elimination itself. Neither the explicit loop nor these copy casts are therefore
required source constructs.

Snapshotting both coordinates as float locals before publishing them reaches
92.09% with the same instruction and reference counts. That isolated score does
not establish a compiler limitation or rule out a coordinated owner change.
The three labels in `experiments.jsonl` record the current-baseline probes.

## 2026-09-04 source-expression diagnostics

Three `coordinate-source-owner-mutations.json` probes against `94f05adb8`
remove explicit coordinate-pointer owners, replace all coordinate bit-copy
casts with float copies (including the sprite branch), or combine both.
Direct fields reach 97.74%; the float-copy forms give 61.02-63.28%, all at
177 instructions. No source is retained. These whole-function variants differ
from the earlier hit-copy-only neutral probe and do not invalidate it.

## 2026-09-05 hit-copy and flag-lifetime probes

Twelve combinations in `hit-copy-and-flag-lifetimes-20260905.json` test direct
float fields, borrowed fields, paired integer snapshots, flag-read timing, and
the redundant clamped-top local. None improves 99.44%; the twenty references
remain clean. Canonical source is unchanged. This only bounds those tested
copy/lifetime combinations.

## 2026-09-05 goal-600 source ownership campaign

Seven whole-coordinate ownership combinations remove integer bit-copy carriers, replace layout-pointer borrows with direct fields, and move flag publication. None improves 99.44%; canonical source is unchanged. Direct fields repair the initial load ordering but introduce later differences, so that tradeoff is not retained.

The recorded probes describe the tested source forms only; they do not establish exhaustion.

Twelve hit-position setter/value-pair forms, including sprite-copy interactions, do not improve 99.44%. No synthetic point owner is retained.

## 2026-09-05 additional source-shape checks

Eight coordinate-pair copy forms (memcpy, aggregate snapshots and field construction, with or without the sprite-anchor pair) regress from 99.44%. No pair type or copy helper is retained.

## 2026-09-05 paired loads and scalar-copy boundaries

Four complete paired-coordinate snapshots explicitly place the live flags
read between or before the destination stores, using integer bits or floats.
They regress from 99.44% to 92.09–97.74%; recovering the early Y load alone
alters later register allocation. Six separate scalar-copy forms then test
4-byte memcpy and ordinary pointer/reference copy operations. Four are neutral
and two regress to 98.87%. No helper, cast change, or snapshot is retained.
The native Y load before the X store remains the single scheduling gap.


## 2026-09-05 join ownership and late hit-publication follow-up

Twelve whole-source forms vary X-only, Y-only, and paired direct member reads
with paired versus interleaved copies and float versus bit carriers. One is
neutral at 99.44%; eleven regress. Twelve further pointer/reference forms
begin destination-field borrows at each hit-coordinate publication. All are
neutral at 99.44%, 177/177 instructions, prefix 66, and 20 clean references.
The successful late field borrow in parcel placement does not transfer to
this load/store region. No source change is retained.

## 2026-09-05 exact recursive layout ownership

The source now calls the value widget's `RePosition()` recursively, using the
receiver's own layout fields throughout. It no longer expresses the compiler's
tail-recursion elimination as a mutable widget pointer and an explicit loop.
The combination restores the native coordinate-load order and all 177
instructions, with 20 clean references. Recursion, direct field access, and
copy lifetimes must be considered together: isolated earlier versions did not
establish the limits of the combined source shape.

The hit-position stores are ordinary float assignments, and the redundant
clamped-top local is removed. The paired integer-bit copies in the sprite
branch remain: direct sequential float copies produce 98.87%, while paired
float snapshots produce 63.28%. Neither alternative changes the shared field
layout or justifies a type change. No compiler flags or shared headers changed.

The corrected recursive recipe has eight compiling cases, including two exact
combinations. Three subsequent copy simplifications retain one exact result.
The first generated recipe accidentally replaced the `widget` substring in
slider member names; all eight C2039 errors are explicitly marked as invalid
mutation-plan evidence in ledger record 18. The separate corrected recipe is
the reproducible source evidence, not those rejected generated names.
