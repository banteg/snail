# spawn_track_jetpack_pickup @ 0x43d890

Live source map for `cRSubGame::AddJetPack(cRSubLoc*, cRSubGoldy*)`.

Current match:

- `86.60%`, `147/144` candidate/target instructions, with `9` masked
  operands ok.
- The scratch now uses the promoted `TrackJetpackPickup` field names and the
  shared `BodList`/`BodNode` active-list shape. Prefix improves to `44/144`;
  the first remaining mismatch is the lane-wall tile compare spelling
  (`mov cl, 0xe` in native versus the current byte-load/constant compare).
- The sprite output copy is now the same typed `Vector3` assignment accepted in
  the health spawner, reducing the tail residual to the bob-phase store versus
  `world_z` conversion scheduling.

Evidence:

- Allocates the single jetpack pickup runtime at `subgame +0x355e64`; the
  shared parent layout now lives in `track_jetpack_pickup.h`.
- The collision-visible lanes are `position +0x10`, `state +0x38`,
  `owner +0x3c`, `sprite +0x64`, `source_cell +0x68`, `bob_phase +0x6c`,
  and `bob_phase_step +0x70`, matching the corrected
  `handle_subgoldy_collisions` offsets `position 0x355e74` and
  `state 0x355e9c`.
- The runtime footprint is `0x19c`; `initialize_track_jetpack_pickup_runtime`
  proves the parent has two embedded renderable bodies beyond the
  collision/spawn prefix.
- The lateral `x` correction is lane/tile dependent: lane `3` shifts `+0.5`
  when the neighboring row bytes are `14`; lane `4` shifts `-0.5` for the
  mirrored neighbors.
- Sprite texture `124` is allocated at size `1.5`, and the bob phase uses the
  same numeric float-to-int parity test seen in the health pickup spawner.
- The active-list add path matches the same insertion semantics as health:
  insert the pickup before the old first node, clear the new head's prev link,
  and set the `0x200` linked bit.

2026-06-16 vtable correction: the earlier "different local view" was a shifted
symbol assumption. `0x43efb0` is the jetpack pickup updater installed by the
parent vtable, while the exact `0x43ee50` updater belongs to the speedup
singleton.

2026-06-16 pool-overlay/list-splice pass: the spawner now mirrors the health
pickup scratch's shifted slot-base shape, keeping `esi` based at
`subgame + slot_index * 0x19c` while using the shared
`SubgameRuntime::jetpack_pickup` member and promoted `TrackJetpackPickup`
fields. The active-list splice was
also reordered to put the empty-list case first, matching native fallthrough
and the health pickup shape. Focused Wibo improves from `52.86%` (`136/144`,
prefix `25/144`) to `73.76%` (`138/144`, prefix `31/144`), with all `9`
masked operands still OK.
Rejected follow-ups: pointer-to-local staging for the initial `PositionBits`
copy compiled identically, a local wall-tile byte compiled identically, and an
explicit odd-z bob-phase `else` regressed to `72.22%` by reversing the tail
block order.

2026-06-16 Vector3 staging correction: same correction as health. The native
function materializes float-sized `x/y/z` locals before storing the pickup
`world_position`, so the scratch now uses `Vector3 staged_position` instead of
the raw `PositionBits` view. Focused Wibo improves from `73.76%` to `79.30%`,
candidate size from `138/144` to `141/144`, and prefix from `31/144` to
`44/144`, with all `9` masked operands still OK. Retesting signed/named
wall-tile constants remained codegen-neutral and did not recover the native
`mov cl, 0xe` ordering, so the source keeps direct tile-id comparisons.

2026-06-19 pickup bob-tail pass: spelling the odd-z case as an explicit
early-return tail improves focused Wibo from `79.30%` to `81.79%`. Native
sets `bob_phase` to zero before the `__ftol` parity test, stores zero again on
the odd path, and has separate odd/even return tails; the early return is the
source shape that recovers that duplication. A destination `Sprite*` local for
the position copy stayed neutral at `79.30%`, direct typed `position.x/y/z`
stores regressed to `77.62%`, splitting the lane-wall test into nested or
independent `if` blocks stayed neutral at `79.30%`, and a `switch(lane)`
regressed to `76.49%`.

2026-06-20 pickup-family retry: focused Wibo still reports `81.79%`,
`147/144` candidate/target instructions, `44/144` prefix, and nine clean
masked operands. Naming the wall-tile constant as either `unsigned char` or
`int` is codegen-neutral and still leaves VC6 lowering the compares as
load-byte-then-`al = 0xe`, not native's early `cl = 0xe`. A destination
`Sprite* out_sprite` local for the final position copy is also neutral and
does not recover native's `edx` ownership. Before the typed copy below, the
first residual was still lane-wall compare scheduling, followed by list-splice
and position-copy register ownership.

2026-06-20 typed sprite-position copy: replacing the raw `DWORD*`
`out_position[0..2]` stores with `sprite->position = *live_position` improves
focused Wibo from `81.79%` to `86.60%`, with candidate size still `147/144`,
prefix `44/144`, and nine clean masked operands. The retained residual is now
the lane-wall constant/register schedule plus the independent bob-phase zero
store moving after the `world_z` `fld`; the typed copy matches the health
spawner's accepted source idiom.
