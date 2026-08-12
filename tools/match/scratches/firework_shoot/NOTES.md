# cRFireWork::Shoot @ 0x441dd0

Current recovery: semantic-complete (`compiler` residual). Live Windows
analysis establishes a void `thiscall` on the exact one-byte `cRFireWork`
owner, with a `tVector*` and three integers. Android and iOS retain the same
method in `SubGame.o`; their ABI presents the vector by value. The receiver is
unused by the body but supplied by every native caller.

The recovered loop allocates each sprite, seeds render flags, lifetime, color,
size, randomized velocity, source position, owner, and texture, then emits the
requested count. The runtime particle-effects gate and all random ranges match
the native body.

Focused VC6 result: **94.17%**, exact 103/103 instruction parity, prefix
78/103, with all 21 relocation operands audited and clean. Remaining drift is
x87 lifetime and loop-register scheduling after velocity construction.

The matcher source now uses authored `Shoot` and exact VC6 symbol
`?Shoot@cRFireWork@@QAEXPAUtVector@@HHH@Z`; `firework_shoot` remains only the
stable scratch and Windows-address identity.
