# Recovered — 100.00%, 67/67 insns

Independent Android and iOS exit residues prove the authored method is
`void`. The exact Windows source now preserves that ABI: a bounded allocator
scan with its exhaustion return inside the loop makes VC6 retain the native
full-pool and success/error exit shapes. The historical score progression
below is retained as evidence. All semantics remain verified in the diff body:

- free scan over `slots[i].state` (+0x80, stride 0x98), bails when all 40 slots
  are occupied
- seeding order: state=active, fade alpha +0x8c=0.0f, spawn-y +0x90 =
  `Game::subgame_rate * (1/30)`, position triple into the live-matrix
  position row (+0x68), `set_matrix_rotation_identity` on +0x38,
  random world-y rotation `(rand() - 16384) * 0.0001917476` (±π),
  then arms the one-byte collision latch at +0x94
- `+0x8c`, `+0x90`, and `+0x94` are independent fields: fade alpha,
  spawn-time y velocity, and collision latch. The earlier claim that
  `update_salt_hazard` proves integration was based on the shifted
  `0x4417d0` name; the actual salt updater at `0x441c10` uses `+0x8c` as a
  fade fraction and does not read `+0x90/+0x94`.
- live-list add-after onto the node-shaped anchor at game+0x3ca224,
  flag 0x200, prev/next at +0x08/+0x0c; the final flags value remains in EAX
- spawn's true extent ends at 0x44164c; an uncurated 20-slot pool
  initializer sits between it and deactivate (worth curating)

2026-06-13 pin audit: focused matcher still verifies 74.07%, 68/67 insns.
Keep pinned; the remaining diff is free-scan loop rotation plus scheduling,
while the collision-latch store and list-link semantics are recovered.

2026-06-16 BOD/renderable consolidation: `SaltHazardSlot` now inherits the
shared `BodNode` prefix, aliases the free-list anchor to `BodList`, and exposes
the renderable/BodBase fields used by salt. This spawn path proves the
zero-offset live-list overlay and writes the matrix position row at `+0x68`;
`initialize_salt_hazard_runtime` calls `initialize_renderable_bod()`, and the
updater drives `color +0x28`. Focused Wibo remains `74.07%`, with `8` masked
operands OK. Later collision evidence names the `+0x94` byte
`collision_armed`.

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
at `cRSubGame`; this spawner reads `subgame_rate` through
`g_game +0x74618` and keeps the root salt list head as a byte-addressed
`g_game +0x3ca224` anchor. Focused Wibo remains exact at `100.00%`, `67/67`
instructions, with `10` clean masked operands.

2026-07-10 collision-latch closure: the spawn-time low byte at slot `+0x94`
is now named `collision_armed`. `spawn_salt_hazard` sets it to `1`, and
`handle_subgoldy_collisions` is the confirming consumer: it gates contact on
that byte and clears it after damage. This scratch remains exact at `100.00%`,
`67/67`, with `10` clean masked operands.

2026-07-11 salt-list ownership closure: startup constructs a complete
`BodBase` at `cRSubGame +0x355c0c`, and this spawner uses its inherited
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

2026-07-19 state and field closure: the exact manager method now consumes the
authored `SaltState` values and writes independent `fade_alpha`,
`spawn_velocity_y`, and `collision_armed` fields. This retires the false
`Vec3 velocity` overlay without changing the 67/67 listing. The sole Windows
caller discards EAX, and the function's full-pool and successful exits leave
different residual values. A `void` source experiment changed the exact
Windows epilogue to 88.55%, so the analysis ABI remains conservatively
`int32_t` pending stronger independent evidence; no slot-index return is
claimed.

2026-07-24 authored void ABI: independent mobile bodies supply the evidence
that the earlier conservative analysis lacked. Android
`cRSaltManager::Add(tVector&)` at `0x69038` returns from the full-pool path
with the last nonzero `SaltState` load in `R0`, but tail-calls the intrusive
list insertion on success. iOS at `0x1dcf8` independently reaches its common
epilogue with `this`, a matrix-call residue, or an error-call residue in `R0`.
Those incompatible values cannot be one authored result, so the manager
method and analysis prototype are now `void`; no slot-index or flag result is
claimed. The resulting Windows mismatch is retained honestly rather than
fakematched.

The same pass closes the manager's free-slot traversal ownership. Its physical
pointer starts at `Salt::state` and advances by the complete `0x98` actor
stride, so both decompilers now use the borrowed analysis-only
`SaltStateStrideCursor` instead of rendering the loop as a `SaltState*` stepped
by 38 integers. The selected slot remains the real manager-owned `Salt*`.
Binary Ninja replay declares this cursor separately from the canonical hazard
owners; adding one analysis view therefore no longer attempts to replace the
existing `Salt` and `SubLazer` definitions.

## 2026-07-28 mobile random-angle provenance

iOS `cRSaltManager::Add(tVector&)` at `0x1dcf8` explicitly retains the
spawn rotation as `(rand - 16384) * (1 / 16384) * pi`. Android at `0x72600`
corroborates it at instruction level: the two consecutive VFP multiplies load
`0x38800000` (`1 / 16384`) and `0x40490fdb` (pi) after subtracting
`0x46800000` (`16384`). The decompiler's missing Android angle operand is
therefore an analysis loss, not a platform difference.

Restoring that hierarchy compiles byte-identically. The honest mobile-proven
void Windows source remains at 88.55%, 64/67 instructions, prefix 4, with all
10 masks clean; the residual is still solely the authored-void versus native
residue-sensitive exit shape, not the angle expression.

## 2026-07-29 exact bounded allocator scan

The sibling slug and pickup allocators expose the missing source-level control
flow. The salt manager scans its 40 inline slots with an explicit upper bound,
advances the typed `Salt*` cursor in the body, and performs the exhaustion
return immediately after that advance:

```cpp
while (index < 40 && scan->state != SALT_STATE_INACTIVE) {
    ++index;
    ++scan;
    if (index >= 40)
        return;
}
```

This ordinary bounded loop retains the independently proven `void` ABI while
making VC6 reproduce all three previously missing native instructions.
Focused matching improves from `88.55%` (`64/67`, prefix `4/67`) to
**100.00%** (`67/67`, full prefix), with all ten audited references clean.

The complete six-variant sweep covered condition-only, equality-exit,
post-loop bound, bounded `for`, and guarded `do/while` forms. Only the bounded
inner exit was exact; the two post-loop bounded forms reached `92.54%`, and
the other forms were neutral or worse. No scalar result, dummy operation,
volatile access, or artificial return value is needed to preserve the native
exit layout.
