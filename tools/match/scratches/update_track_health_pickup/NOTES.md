# update_track_health_pickup @ 0x43ecc0

Current match: **100.00%**, `128/128` candidate/target instructions, full
`128/128` prefix, with `21` clean masked operands.

Recovered behavior:

- skip when the reset-initialized owner-subgame `subgame_pause_gate` byte at
  `+0x09` is set;
- state `0` returns immediately;
- state `2` unlinks the pickup from the shared `g_game_base + 0x5a8` bod list,
  pushes it onto the free stack, clears `0x200`, and kills the sprite;
- state `1` performs the same teardown once `world_z` falls behind
  `owner->interaction_max_z`;
- all other nonzero states advance the health bob phase, wrap only when the
  phase is strictly greater than `1.0f`, and write
  `(sine(phase * tau) + 1.0f) * 0.30000001f + world_y` to
  `sprite->position.y`.

The emitted x87 wrap condition matches the native strict `> 1.0f` test
(`test ah, 0x41`). Earlier hand-expanded unlink spellings left a block-layout
residual; the shared-list recovery below closes it.

Rejected source-shaped probes:

- nesting the state-1 removal block under `if (world_z < interaction_max_z)`
  recovered the native branch direction but let VC6 merge the two unlink error
  tails, regressing to 58.47% and shrinking the candidate to 108 instructions;
- spelling the state dispatch as the IDA-style `state`, `state - 1`,
  `state - 2` ladder similarly merged duplicate unlink blocks and regressed to
  56.54%;
- an explicit `state_one_remove` label emitted the same merged 58.47% layout.

2026-06-19 branch-layout retry:

- spelling the state-one guard as `!(world_z < interaction_max_z)` is
  codegen-neutral at 71.88%; VC6 simplifies it back to the pinned
  bob-before-removal layout with `jne` into the state-one unlink block;
- retesting the structured `if (world_z < interaction_max_z) { remove; }`
  form still recovers the native `je` around the state-one unlink block but
  merges the duplicated unlink error tails, reproducing the 58.47%,
  108-instruction regression;
- adding explicit local labels around the state-two error exits does not
  prevent the merge and further regresses to 58.97%/106 instructions by
  changing the state-two branch polarity. Keep the speedup-shaped duplicated
  blocks until a structured spelling preserves both native branch polarity and
  the duplicated error exits.

2026-06-20 health-family retry:

- retesting the structured `if (world_z < interaction_max_z) { remove; }`
  state-one arm again recovered the local branch direction but merged too much
  of the duplicate unlink/error body, regressing to 58.47% with 108 candidate
  instructions and 12 clean masked operands;
- adding a natural `Sprite* bob_sprite` local for the final y-position store
  was score-neutral at 71.88%, but it loaded the sprite through `edi` and kept
  the broader bob-before-removal placement, so it was not retained.

Keep this pinned unless a source-plausible dispatch spelling preserves both the
duplicated unlink blocks and the native final bob-tail placement.

2026-06-16 type cleanup: this now uses the shared partial
`TrackHealthPickup` layout from `track_health_pickup.h`, including the shared
`BodNode` list prefix from `bod_list.h`. Match remains 71.88%.

2026-06-16 initializer consolidation: `initialize_track_health_pickup_runtime`
now uses this same promoted `TrackHealthPickup` type, while casting through
`BodBase` for the exact initializer and vtable write. The first `0x38` bytes are
therefore both the BOD base prefix at initialization time and the pickup
world/state payload used by spawn/update/collision paths.

Important naming correction: reset_subgame initializes health pickup `+0x44`
with the containing `SubgameRuntime*`, so this lane is now `owner_game`, not a visibility-cell
pointer. `spawn_track_health_pickup` stores the row/source cell at
`source_cell +0x68`. Do not collapse those into one `source_cell` field.
Do not merge health and jetpack into one full pickup struct either: both use
the containing subgame backlink at `+0x44`, while jetpack has embedded renderable
bodies below `+0x74`.

2026-06-18 owner-game rename: the earlier `TrackVisibilityCell` interpretation
was invalidated by reset_subgame, which writes the containing
`SubgameRuntime*` into
`+0x44` for every health pickup slot. The update check is the same pause-byte
view used by speedup and jetpack pickups.

2026-07-11 owner-view retirement: speedup, health, and jetpack now borrow the
full containing `SubgameRuntime` directly. The duplicate
`TrackPickupOwnerSubgameView`/`TrackPickupOwnerGameView` types were retired;
their only known field, `subgame_pause_gate +0x09`, is already part of the
canonical owner. This also makes the pickup ownership agree with slug, salt,
sub-lazer, garbage, and reset paths without changing generated code.

2026-06-20 updater CFG improvement: the Pro Extended pass moved the state-one
guard to the positive `world_position.z < owner->interaction_max_z` removal
arm, split the two state-two list-error exits into cold labels, and added one
state-one `Sprite*` snapshot shared by the two diagnostic exits. Local focused
Wibo reproduces 87.94%, 129/128 instructions, 6/128 prefix, and 21 clean masked
operands; `health_collect_particles` remains exact at 100.00%. The remaining
residual is the extra state-one sprite snapshot load before the diagnostic
tails; the native shape reloads `sprite` directly into `ecx`.

2026-06-20 larger health-family retry: moving the state-one `Sprite*` reload
inside each diagnostic branch after `report_errorf` removes the early snapshot
source-wise, but VC6 folds the duplicated unlink/error tails and regresses to
`58.47%`, `108/128` candidate/target instructions, with 12 clean masked
operands. Spelling the state-one diagnostics as explicit local labels regresses
further to `51.69%`, `108/128`, with 9 clean masked operands. Keep the shared
state-one sprite snapshot until a natural source form preserves both the
native tail placement and the separate teardown shape.

2026-06-20 pickup-family transfer: the same positive state-one removal arm,
split state-two cold exits, and shared state-one diagnostic sprite snapshot
lift `update_track_jetpack_pickup` from `72.44%` to `87.84%`. Retesting the
direct state-one `sprite->kill_sprite()` diagnostics in both health and jetpack
folds the duplicated teardown blocks (`58.47%` here, `58.12%` in jetpack), so
the remaining extra snapshot load is a shared pickup-family source-shape debt,
not a health-only semantic gap.

## 2026-07-11 cRSubHealth ownership

The receiver and intrusive-list neighbors now use the primary `SubHealth`
type. The exact Windows constructor table at `0x497320` points directly to this
helper; Android and iOS retain `cRSubHealth::AI()`. Focused Wibo remains the
honest 87.94%, 129/128 instructions, with all 21 masked operands clean.

## 2026-07-12 shared list removal recovery

Android spells both teardown paths as `cLinkedList<cRBod>::Remove`, followed by
`cRSprite::Kill`. Recovering that operation once on the owned `BodList` lets
VC6 inline the body independently at the state-1 and state-2 callsites, exactly
explaining the duplicated Windows error/unlink blocks without a synthetic
saved `Sprite*`. Focused Windows matching is now exact at `128/128`.

2026-07-14 root-list closure: both removal arms now borrow
`GameRoot::active_bod_list` directly. The updater remains exact at 128/128
with all 21 operands clean.
