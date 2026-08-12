# cRPathFollowGoldy::Traverse @ 0x420cb0

Current recovery: semantic-complete (`compiler` residual).

Android and iOS `Path.o` independently export the exact authored method
`cRPathFollowGoldy::Traverse(float, tVector&, tVector*)`, with one body on
each platform. Live Windows analysis confirms the same three-argument
thiscall, integer mode return, 0x40-byte `cRPathFollowGoldy` owner, two native
callers, and the complete mode-switch consumer in `cRSubGoldy::AI`.

The matcher now uses the authored method and reference parameter directly.
VC6 emits
`?Traverse@cRPathFollowGoldy@@QAEHMAAUtVector@@PAU2@@Z`; selecting that exact
COFF symbol is byte-neutral at 75.66% (712/726 instructions), with a
122-instruction exact prefix and all 65 relocations resolved cleanly.

Recovered behavior covers path-sample stepping, ordinary and nonlinear
transforms, Goldy matrix publication, side exits, and the Supertramp terminal.
The remaining 14-instruction deficit is bounded to block layout, matrix
temporaries, and x87 scheduling. Recorded experiments preserve the rejected
source-shape frontier; obsolete runnable mutation recipes are not retained.
