# cRBorder::RePosition @ 0x4024a0

Current recovery: semantic-complete (`compiler` residual). Binary Ninja types
the Windows entry as `void __thiscall(FrontendWidget*)`; all 24 Windows callers
discard `eax`. Android and iOS independently retain the same owner and method as
`cRBorder::RePosition()` in `Border.o`.

The body selects sprite, authored-rectangle, or measured-text geometry; clamps
the hit rectangle unless off-screen placement is allowed; and recursively
repositions the attached slider children. The shared field layout is supported
by the initializers, draw path, mouse path, and mobile bodies.

Focused VC6 result: **99.44%**, exact 177/177 instruction parity, prefix 66/177,
with all 20 relocation operands audited and clean. The sole residual is the
ordering of two independent loads around the first hit-rectangle stores.

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
