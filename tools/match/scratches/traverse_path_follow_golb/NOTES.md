# cRPathFollowGolb::Traverse @ 0x4217b0

Current recovery: semantic-complete (`compiler` residual).

Android and iOS `Path.o` independently export the exact authored method
`cRPathFollowGolb::Traverse(float, tVector&, tVector*)`, with one body on each
platform. Live Windows analysis confirms the same three-argument thiscall,
integer mode return, sole `cRSubGolb::AI` caller, and complete return-mode
switch.

The matcher now uses the authored method and reference parameter directly.
VC6 emits `?Traverse@cRPathFollowGolb@@QAEHMAAUtVector@@PAU2@@Z`; selecting
that exact COFF symbol is byte-neutral at 85.82% (421/425 instructions), with
a 32-instruction exact prefix and all seven relocations resolved cleanly.

Recovered behavior covers borrowed path traversal, both transform branches,
Golb flight-transform publication, lateral exit, and terminal launch. The
remaining four-instruction deficit is bounded to vector-temporary folding and
stack coloring. Recorded experiments preserve the rejected source-shape
frontier; obsolete runnable mutation recipes are not retained.
