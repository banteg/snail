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
