# update_ring_or_special_effect_parent @ 0x43e830

Live source map for the ring/special-effect parent virtual updater.

Current match:

- `98.21%`, `336/336` candidate/target instructions, with `37` masked
  operands clean and no unresolved or mismatched operands.
- A score-improving `>= tau` phase-wrap spelling was rejected because native
  uses the strict `> tau` x87 condition (`test ah, 0x41` after compare).
- The method is modeled as `void`: native exits do not establish a meaningful
  return value, and the earlier `void*` surface forced extra return-value
  cleanup in the candidate.

Cross-port owner: iOS preserves this callback as `cRSubRing::AI()`, and the
Windows constructor table at `0x49732c` points directly here. The shared source
now defines it on `SubRing` and its children as `SubRingStar`; focused matching
remains 98.21%, 336/336 instructions, with 37 clean operands.

Evidence:

- Parent `+0x80` is a state word, not a boolean. Observed states are `0`
  inactive, `1` normal orbit/update, `2 -> 3` target-collapse transition, and
  `4 -> 5` expansion/removal transition.
- Parent `+0x1d4/+0x1d8` are transition progress and transition step.
- Parent `+0x8c` is the owner's lives snapshot. State `1` compares
  `owner_player->lives` against it only when parent `position.z` is at or beyond
  the player's interaction Z limit. If the parent falls below that limit, native
  immediately removes the parent and kills the ten child sprites. This corrects
  the earlier inverted `position.z < interaction_max_z` interpretation.
- Parent `+0x1dc` gates the sine-driven `position.x` oscillation using
  `active_phase +0x1e0` and `active_phase_step +0x1e4`.
- The state-3 collapse uses a real `Vector3 delta` toward
  `owner_player->cached_camera_target_world` (`+0x2964`), with target Z biased
  by `+0.2` before the `0.939999998` scale.
- The parent child-array evidence remains consistent with the other ring
  scratches: ten particles at `+0x90`, stride `0x20`.
- Both radius-update paths compile as indexed walks over those ten embedded
  records. The loop cursor is derived from parent `this + 0xac` (the first
  child's `radius`), rather than following or transferring an external child
  pointer.
- Each embedded particle holds a separate `SpriteManager::allocate_sprite`
  result. All three parent-removal exits call `kill_sprite()` for every child;
  the parent owns the fixed particle records, while sprite storage stays under
  the sprite manager's allocate/kill lifecycle.
- The updater reads owner `+0x2964` as a target vector during state `3`; this
  is the same `cached_camera_target_world` field produced by the camera block in
  `update_subgoldy`.

Type consolidation:

- `SubRing::state`, `transition_progress`, `transition_step`, and
  `oscillate_x` are now
  in `tools/match/include/ring_special_effect_types.h`.
- 2026-06-16 naming correction: the old exported name
  `update_subgoldy_bullet` was stale. The function is the virtual updater for
  `RingOrSpecialEffectParent`, cross-confirmed by the ring/special-effect
  runtime initializer, spawner, child-particle initializer/updater, and
  collision consumer. The reference manifest keeps the old jump-table name as
  an alias only. Focused Wibo remains unchanged at `86.35%`, and the direct
  spawner caller remains unchanged at `51.23%`.
- `RingOrSpecialEffectParent` now inherits shared `RenderableBod`, and the
  remover uses `RingOrSpecialEffectListAnchor` (`BodList`) for the active/free
  anchor at `g_game_base + 0x5a8`. The old scratch-local `next` (`+0x08`) and
  `prev` (`+0x0c`) names were corrected to `list_prev`/`list_next` through the
  inherited `BodNode` prefix.
- 2026-06-17 renderable inheritance correction: the parent center updated by
  this virtual method is inherited `transform.position` at `+0x68`. Focused
  Wibo remains unchanged at 86.35%, confirming this is a type consolidation
  rather than a source-shape change.
- `RingOrSpecialEffectParticle` is now promoted in the shared header, and parent
  `+0x90..+0x1cf` is modeled as `particles[10]`. The particle updater is
  side-effect-only from all known callsites, so it is declared `void`.
- `Player::lives` is promoted in `tools/match/include/player.h` at `+0x404`;
  this updater and `spawn_track_ring_or_special_effect` now use the shared
  field instead of raw `player + 0x404` loads.
- `Player::cached_camera_target_world` is promoted at `+0x2964` after
  cross-confirmation from the `update_subgoldy` producer and this ring
  transition consumer.
- 2026-06-16 state-switch correction: spelling an explicit unsigned
  `current_state > 5` guard and `case 0: return` recovers native's direct
  `0..5` state jump table instead of VC6's optimized `state - 1` table. The
  corresponding compiler-emitted table at `0x43ec9c` is named
  `update_ring_or_special_effect_parent_state_jump_table` in the gameplay
  reference manifest.

Residual:

- Native duplicates the list-removal/child-kill tail for the three removal
  exits. The scratch now spells those exits explicitly, which raised the match
  from `28.32%` to `68.48%`.
- A `Vector3 delta` local for the state-3 collapse moved the scratch from
  `68.48%` to `69.77%`. Staging an immutable local copy of
  `owner_player->cached_camera_target_world` before computing and scaling the
  delta recovered the native `sub esp, 0x18` frame. The later state-switch
  correction raised the scratch to `79.53%`; the state-1 branch-shape pass
  raised it further to `86.35%`; the current target/current position pointer
  plus `scaled_delta` source shape raises it to `88.92%` while preserving the
  native `0x18` frame.
- 2026-07-10 ownership/source-shape pass: constructing the biased camera target
  as a real `Vector3` value and expressing both radius loops as indexed walks
  raises the focused match from `88.92%` (`332/336`) to `98.21%` (`336/336`).
  This also recovers the native `this + 0xac` embedded-child cursor and aligns
  the dispatch instruction/table shape. The reference manifest now pairs that
  compiler table cleanly.
- The remaining residual is two local schedules: native keeps target X live on
  the FPU stack while staging biased Z and target Y before deriving the child
  cursor, and one duplicated removal tail materializes the shared list anchor
  through a different general-purpose register. The source keeps the ordinary
  `Vector3`/indexed-array model rather than encoding register or byte-layout
  tricks for those six instruction-order differences.
- 2026-06-16 state-1 branch-shape pass: spelling the z-threshold as
  `position.z < owner_player->interaction_max_z` with the removal path in the
  taken source block recovers the native physical order for the remove-vs-lives
  decision. Focused Wibo improves from `79.53%` to `86.35%` while preserving
  the native `0x18` stack frame. The only new audit debt is the candidate local
  switch-table symbol (`$L1005`) versus the curated target
  `update_ring_or_special_effect_parent_state_jump_table`; the dispatch
  instructions and table shape are otherwise unchanged.
- 2026-06-20 collapse restaging: revisiting the pointer-plus-scalar target
  shape with a real `Vector3 scaled_delta` local preserves the native `0x18`
  frame and improves the focused match from `86.35%` to `88.92%`. The accepted
  source keeps typed pointers to `owner_player->cached_camera_target_world` and
  `transform.position`, computes `delta`, then applies a separate scaled-delta
  vector before copying the updated parent position into each child particle's
  base position. Reordering the named target y/z lanes compiled identically at
  `88.92%`, so the clearer delta-first source order is kept.

Rejected/source-shape probes:

- Spelling the collapse as explicit unscaled `target_y`, `target_z`, and
  `delta_*` locals regressed to the previous `68.48%` shape, so keep the
  aggregate `Vector3 delta`.
- 2026-06-16 collapse staging probes: changing case `0`/default to explicit
  early returns alone compiled identically and did not fix the jump table;
  the winning shape required the explicit unsigned range guard. Staging
  `rate->subgame_pause_gate` in a local byte also compiled identically. Mutating a local
  `Vector3 target.z` before computing delta improved only to `70.52%`, and a
  pointer plus scalar `target_y`/`target_z` spelling regressed to `70.55%` with
  a smaller frame. Keep the immutable local `Vector3 target` plus aggregate
  `Vector3 delta` form.
- 2026-06-16 rechecked after the state-1 branch-shape pass: the pointer plus
  scalar `target_y`/`target_z` collapse spelling reaches `87.72%`, but it drops
  the native `sub esp, 0x18` frame to `0x0c` and shrinks the candidate to
  `332/336` instructions. Reverted; the aggregate `Vector3 target`/`delta`
  spelling is still the better structural match.
- 2026-06-20 larger-family retry: spelling the state-3 collapse in native
  scalar order with explicit `target_z`, `target_y`, `delta_x/y/z`, and
  `scaled_y/z` locals regressed the focused match from `88.92%` to `78.55%`,
  collapsed the frame to a single pushed scratch slot, and shortened the
  candidate to `326/336` instructions. Keep the pointer-plus-`Vector3 delta`
  and `scaled_delta` form unless a stronger local-lifetime lead appears.
- 2026-07-10 a chained `Vector3` operator expression grew the frame to `0x24`
  and regressed to `85.17%`; copying the target value into `delta` before
  subtracting grew the candidate to `342/336` and regressed to `89.97%`.
  Neither reflects the native temporary lifetime, so both were rejected.

2026-07-11 root-list ownership cleanup: all three duplicated removal tails now
take their intrusive-list anchor from `GameRoot::active_bod_list` instead of
recasting `g_game_base +0x5a8`. This matches the exact salt-removal owner and
preserves 98.21%, 336/336 instructions, and 37 clean operands. The remaining
list-tail register choice is therefore compiler scheduling, not evidence for a
ring-local list owner.

2026-07-12 shared remover recovery: the three duplicated teardown bodies now
call the proved inline `GameRoot::active_bod_list.remove_bod` method. This is
codegen-neutral at `98.21%`, `336/336` instructions, with all `37` masked
operands clean, while making the common list ownership explicit. The only
removal residual is one root-anchor register choice; the larger residual is
still the state-3 camera-target `Vector3` staging at target instruction 193.

2026-07-13 rate-owner closure: reset assigns each embedded ring's `+0x1d0`
backlink directly to its enclosing `SubgameRuntime`; the updater consumes that
same owner's `subgame_pause_gate +0x09` and `subgame_rate +0x38`. The former
`RingEffectRateSource` shell represented no allocation or lifetime boundary and
is retired. Focused matching remains 98.21%, 336/336, with 37 clean operands.
The scratch now names `subgame_runtime.h` as a direct dependency rather than
depending on `game_root.h` to expose the complete owner transitively.

## 2026-07-14 particle extent derivation

All six update/kill loops and both indexed radius loops now share the
`SUB_RING_PARTICLE_COUNT` bound owned by `SubRing::particles`. The normalized
listing remains byte-identical
(`0940726eee8e7a0a108d1a2d58301241c610d08414c729dc7685b0f5f9950488`)
at the honest 98.21% result (`336/336`, prefix `193/336`, 37 clean operands).

## 2026-07-14 ring lifecycle ownership

The parent state word is now `SubRingState`: inactive/active, collision-pending
and collecting, then expansion-pending and expanding. Those names follow the
proved writers and transition behavior rather than guessing an original enum.
Focused output remains 98.21%, 336/336 instructions, prefix 193/336, with 37
clean operands.
