# Pinned - 98.41%, 63/63 insns exact

Semantics are fully covered:

- state becomes live (`+0x80 = 1`)
- live matrix is reset with `set_matrix_identity`
- origin is copied into the matrix position row at `+0x68`
- direction is copied into velocity at `+0x8c`
- sprite bob phase starts at zero and the bob step is
  `owner_game->track_center_x * 0.0055555557`
- slot is added after the `owner_game+0x355bd4` sub-lazer list head with
  list flag `0x200`, or reports `"List ADDafter"` if already linked
- matrix forward axis is rebuilt from velocity through
  `set_matrix_z_direction`

The only residual is scheduling around the velocity `z` copy versus the
`sprite_bob_phase = 0.0f` store. Native loads direction z, zeroes the phase,
then stores velocity z; the current vector-copy source keeps the pointer-copy
register pattern and exact instruction count but zeroes the phase after the
full velocity copy.

Rejected source-plausible variants:

- explicit component stores with a `float direction_z` temporary regressed to
  80.00% by forcing x87 load/store traffic
- direct component stores without the temporary regressed to 83.20% and lost
  the native pointer-copy register pattern
- moving `sprite_bob_phase = 0.0f` before the vector copy stayed at 98.41%
  but shifted the mismatch earlier
- `velocity_copy->x/y/z` field assignments regressed to 73.60% by changing
  register ownership

Do not force the remaining store scheduling with volatile fields or dummy
aliases; the current source is the closest honest shape found.

2026-06-16 vtable correction: `update_sub_lazer_projectile` is also a
`SubLazerSlot` view. The earlier separate `SubLazerRuntime` view was the
jetpack pickup parent updater at `0x43efb0`. A raw-word staging probe for the
velocity-z/phase store order regressed to 72.00% by changing register
ownership, so the vector-copy spelling remains pinned.

2026-06-16 BOD-list consolidation: `SubLazerSlot` now inherits the shared
`BodNode` prefix, and `SubLazerListAnchor` aliases `BodList`. Focused Wibo
still verifies 98.41%, 63/63 insns, with six masked operands OK. This confirms
the sub-lazer pool uses the same intrusive list prefix as the other BOD-backed
runtime pools; the remaining residual is still only the velocity-z/phase store
scheduling noted above.
