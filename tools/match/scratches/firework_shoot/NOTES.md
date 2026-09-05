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

## Countdown lifetime before position publication (2026-08-13)

Live Windows disassembly shows the loop countdown becoming dead while the
final trivial `Vector3` position copy is still being published: VC6 loads and
decrements `remaining` between the three position-lane stores. Expressing that
ordinary local lifetime by decrementing before the copy improves focused Wibo
from **94.17% to 95.15%** (+4 fuzzy bytes), with exact 103/103 instruction
parity, the same 78-instruction prefix, and all 21 references clean.

A recorded six-variant sweep covers the natural depth, velocity, countdown,
and position publication orders. Only the two spellings that end the countdown
lifetime before the position copy improve; moving the depth write after the
copy regresses. Follow-up direct-copy, reference, source-pointer, and subtraction
spellings are byte-identical to the accepted form, while component-wise copying
regresses sharply. The remaining five-instruction tail drift begins where VC6
chooses when to advance the sprite base while the last x87 multiply is live;
no artificial storage or register constraint is justified.

## 2026-09-04 source-expression diagnostics

Two recorded products against `94f05adb8` test position/count lifetimes
(8 alternatives) and velocity temporary/count interaction (5 alternatives).
Direct position assignment and direct velocity construction can preserve the
95.15% baseline; moving the decrement to the loop condition gives 94.17%.
The float-pointer position constructor changes allocation more broadly. No
source is promoted; the specifications preserve the tested source forms.

## 2026-09-05 goal-600 source ownership campaign

Sixteen whole-motion publication forms test named velocity construction, depth publication, position-copy shape and count-decrement lifetime. None improves 95.15%; canonical source is unchanged.

The recorded probes describe the tested source forms only; they do not establish exhaustion.

## 2026-09-05 continued loop-owner campaign

Four loop-vector scope combinations and eight emitter counter/position ownership combinations do not improve 95.15%. Moving the velocity outside the loop is neutral here, unlike the two fringe builders. Canonical source is unchanged.

## 2026-09-05 continued source-shape investigation

Two diagnostic XYZ constructor-body forms are non-improving. XYZ assignment is neutral and reversed assignment regresses. The shared vector header remains unchanged.
