# spawn_sub_lazer_projectile

Current match: 100.00%, 63/63 instructions, with six clean masked operands.

Semantics covered:

- state becomes live (`+0x80 = 1`)
- live matrix is reset with `set_matrix_identity`
- origin is copied into the matrix position row at `+0x68`
- direction is copied into velocity at `+0x8c`
- sprite bob phase starts at zero and the bob step is
  `owner_game->subgame_rate * 0.0055555557`
- slot is added after the `owner_game+0x355bd4` sub-lazer list head with
  list flag `0x200`, or reports `"List ADDafter"` if already linked
- matrix forward axis is rebuilt from velocity through
  `set_matrix_z_direction`

Exact-match source-shape fix:

- Directly assigning `velocity = *direction` instead of copying through a local
  `Vector3* velocity_copy` lets VC6 schedule the `sprite_bob_phase = 0.0f`
  store between loading direction z and spilling velocity z, matching native.
  The source remains normal struct-copy code.

Rejected source-plausible variants:

- explicit component stores with a `float direction_z` temporary regressed to
  80.00% by forcing x87 load/store traffic
- direct component stores without the temporary regressed to 83.20% and lost
  the native pointer-copy register pattern
- moving `sprite_bob_phase = 0.0f` before the vector copy stayed at 98.41%
  but shifted the mismatch earlier
- `velocity_copy->x/y/z` field assignments regressed to 73.60% by changing
  register ownership

2026-06-16 vtable correction: `update_sub_lazer_projectile` is also a
`SubLazerSlot` view. The earlier separate `SubLazerRuntime` view was the
jetpack pickup parent updater at `0x43efb0`. A raw-word staging probe for the
velocity-z/phase store order regressed to 72.00% by changing register
ownership.

2026-06-16 BOD-list consolidation: `SubLazerSlot` now inherits the shared
`BodNode` prefix, and `SubLazerListAnchor` aliases `BodList`. Focused Wibo
verified 98.41%, 63/63 insns, with six masked operands OK before the later
direct-velocity-copy exact-match fix. This confirms the sub-lazer pool uses the
same intrusive list prefix as the other BOD-backed runtime pools.

2026-06-16 renderable-prefix consolidation: the shared `SubLazerSlot` header
now records the renderable transform rows at `+0x38..+0x77`, with
`position +0x68` as the matrix position row. The initializer calls
`initialize_renderable_bod()`, this spawner resets the matrix and copies the
origin into that row, and the updater/collision paths consume the same field.
The slot stays `BodNode`-based in the type because the zero-offset list overlay
is also real and used by the live/free-list helpers.

2026-06-21 subgame-owner consolidation: `SubLazerSlot::owner_game` is now a
`SubgameRuntime*`, with the node-shaped sub-lazer list head exposed at
`SubgameRuntime +0x355bd4`. Focused Wibo remains exact at `100.00%`, `63/63`
instructions, with `6` clean masked operands.

2026-07-11 sentinel-extent closure: the constructor pass proves that the
list head is not merely a 0x10-byte node-shaped window but a complete embedded
`BodBase` at `SubgameRuntime +0x355bd4`. `build_subgame_level` also links the
tutorial barrier through this same head, so the narrower `sub_lazer_list_head`
name is corrected to `barrier_sub_lazer_list_head`. The spawner borrows its
inherited `BodNode` prefix directly and remains exact at `100.00%`, `63/63`,
with `6` clean masked operands.
