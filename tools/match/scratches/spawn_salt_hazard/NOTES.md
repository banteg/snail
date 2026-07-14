# Matched — 100.00%, 67/67 insns

The free-scan loop is the only divergence: the original lays it out as a
single top test with the bound compare as conditional back-edge; every
source shape tried (for-with-increment, while, for(;;)+break,
do-while+goto) rotates and duplicates the state test under our compiler
pass ordering. All semantics verified in the diff body:

- free scan over `slots[i].state` (+0x80, stride 0x98), bails with
  `return index` at 40
- seeding order: state=1, velocity.x +0x8c=0.0f, velocity.y +0x90 =
  `Game::subgame_rate * (1/30)`, position triple into the live-matrix
  position row (+0x68), `set_matrix_rotation_identity` on +0x38,
  random world-y rotation `(rand() - 16384) * 0.0001917476` (±π),
  then a one-byte write to velocity.z +0x94
- `+0x8c..+0x94` is still a spawn-time velocity-looking lane, and spawn only
  pokes the low byte of `+0x94` to `1`. The earlier claim that
  `update_salt_hazard` proves integration was based on the shifted
  `0x4417d0` name; the actual salt updater at `0x441c10` uses `+0x8c` as a
  fade fraction and does not read `+0x90/+0x94`.
- live-list add-after onto the node-shaped anchor at game+0x3ca224,
  flag 0x200, prev/next at +0x08/+0x0c, returns `list_flags |= 0x200`
- spawn's true extent ends at 0x44164c; an uncurated 20-slot pool
  initializer sits between it and deactivate (worth curating)

2026-06-13 pin audit: focused matcher still verifies 74.07%, 68/67 insns.
Keep pinned; the remaining diff is free-scan loop rotation plus scheduling,
while the velocity.z low-byte poke and list-link semantics are recovered.

2026-06-16 BOD/renderable consolidation: `SaltHazardSlot` now inherits the
shared `BodNode` prefix, aliases the free-list anchor to `BodList`, and exposes
the renderable/BodBase fields used by salt. This spawn path proves the
zero-offset live-list overlay and writes the matrix position row at `+0x68`;
`initialize_salt_hazard_runtime` calls `initialize_renderable_bod()`, and the
updater drives `color +0x28`. Focused Wibo remains `74.07%`, with `8` masked
operands OK. The `+0x94` low-byte poke remains spelled as an overlay on
`velocity.z` until more source evidence gives it a better semantic name.

2026-06-20 volatile audit: direct `g_game` no longer needs `volatile` in this
spawn path. Focused Wibo improves from 74.07% to 77.04%, still 67 target / 68
candidate instructions, with 9 masked operands OK and no unresolved or
mismatched operands. The remaining mismatch is still the free-scan rotation and
spawn scheduling/register choices; no fake loop labels or volatile locals were
used.

2026-06-20 sibling loop/angle correction: retesting the top-test
`while (1) { if (!*state) break; ... }` scan after the non-volatile `g_game`
cleanup recovers the native single state test and raises the prefix to 34.
Inlining the random world-y angle into `rotate_matrix_world_y(...)` lets VC6
push the argument slot first and fill it through x87 like native. Focused Wibo
is now 98.51%, 67/67 instructions, and 10 clean masked operands. Rewriting the
`+0x94` low-byte poke as a raw byte pointer was neutral; the only residual is
VC6 loading `list_flags` before that independent byte store.

2026-06-20 exact update: after the live-byte store, keeping a real
`int* list_flags = &slot->list_flags` owner for the intrusive-list flag check
and final OR prevents VC6 from hoisting the flag load above the independent
`+0x94` byte poke. Focused Wibo now reports a proof-grade `100.00%`, `67/67`
instructions, full prefix, and `10` clean masked operands.

2026-06-21 subgame-owner consolidation: `SaltHazardSlot::owner_game` now points
at `SubgameRuntime`; this spawner reads `subgame_rate` through
`g_game +0x74618` and keeps the root salt list head as a byte-addressed
`g_game +0x3ca224` anchor. Focused Wibo remains exact at `100.00%`, `67/67`
instructions, with `10` clean masked operands.

2026-07-10 collision-latch closure: the spawn-time low byte at slot `+0x94`
is now named `collision_armed`. `spawn_salt_hazard` sets it to `1`, and
`handle_subgoldy_collisions` is the confirming consumer: it gates contact on
that byte and clears it after damage. The accessor preserves the proven
`velocity.z` storage overlay and this scratch remains exact at `100.00%`,
`67/67`, with `10` clean masked operands.

2026-07-11 salt-list ownership closure: startup constructs a complete
`BodBase` at `SubgameRuntime +0x355c0c`, and this spawner uses its inherited
`BodNode` links as the salt live-list sentinel. The raw `char* g_game` address
arithmetic is therefore replaced by `GameRoot::subgame.salt_hazard_list_head`;
the rate read also resolves through the same owned subgame. Focused Wibo
remains exact at `100.00%`, `67/67`, with `10` clean masked operands.

2026-07-11 authored owner: this exact manager method now belongs to
`SaltManager`, matching Android `cRSaltManager::Add(tVector&)`; iOS v1.9 adds
the owning Goldy argument. The allocated slot is an inline `Salt`, not a
transferred hazard object. Matching remains 67/67 with ten clean operands.

2026-07-13 Binary Ninja ownership sync: the startup clone pass proves the
manager's 40 inline `0x98` slots and each slot's `owner_game +0x88` backlink.
The live prototype is now the manager thiscall plus one borrowed position,
retiring the stale path-template/multi-argument projection. Matching remains
exact at 67/67.

2026-07-14 renderable-owner closure: the spawn matrix reset and position copy
now use `Salt::transform` and `Salt::transform.position` directly. The exact
constructor and updater corroborate the same inherited `RenderableBod`; the
former field-by-field transform duplicate represented no separate owner.
Matching remains exact at 67/67 with ten clean operands.

2026-07-14 manager traversal ownership: the free-slot loop now advances a
typed `Salt*` through `SaltManager::slots` instead of treating each 0x98-byte
record as 38 integer lanes. This is byte-identical at 67/67 instructions with
all ten operands clean.
