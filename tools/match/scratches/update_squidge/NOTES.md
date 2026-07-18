# update_squidge @ 0x4449c0

Source-shaped match: 84.15%, 80/84 candidate instructions with a 6-instruction
prefix.

This helper advances the player squidge presentation spring for the y and z
lanes. Each active lane integrates phase by velocity, damps velocity with the
native `0.15`/`0.82` constants, writes the negated phase to the output lane,
and zeros the lane once both velocity and output are below `0.001`.

Residual:

- Native stores the negated phase to the stack local and output field from a
  single x87 value, then reloads the local around the output absolute-value
  threshold. The scratch's clear local-copy spelling preserves the same
  semantics but emits an extra `fld`/`fstp st(0)` pair in each lane.
- Rejected variant: mutating the output local in place removed that duplicate
  local but regressed the earlier velocity store shape from 84.15% to 75.15%.

2026-06-21 exact match: spelling the output absolute-value source as an
explicit negative/positive assignment,
`if (new_output < 0.0f) abs_output = -new_output; else abs_output = new_output`,
matches the native x87 reload schedule in both y and z lanes. Focused Wibo now
reports 100.00%, 80/80 instructions, with 14 clean masked operands. Rejected
nearby spellings during the retry: `0.0f > abs_output` regressed to 79.27%,
copying from the output field improved only to 84.81% while changing instruction
count, mutating `new_output` in place reproduced the old 75.15% regression, and
volatile locals regressed badly.

## 2026-07-18 analyzer replay

The four-function `cRSquidge` family now exports through the canonical
`Squidge` owner in both analyzers. Binary Ninja resolves the 0x18-byte
initializer and all Y/Z spring fields; IDA retires the port-side
`SquidgeState` compatibility name and the raw `sub_444960(_DWORD *this)` view.
The tracked owner checks cover the initializer, both start methods, and AI.
