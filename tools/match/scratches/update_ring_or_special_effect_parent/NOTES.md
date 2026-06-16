# update_ring_or_special_effect_parent @ 0x43e830

Live source map for the ring/special-effect parent virtual updater.

Current match:

- `86.35%`, `338/336` candidate/target instructions, with `35` masked
  operands ok and one known jump-table audit mismatch.
- A score-improving `>= tau` phase-wrap spelling was rejected because native
  uses the strict `> tau` x87 condition (`test ah, 0x41` after compare).
- The method is modeled as `void`: native exits do not establish a meaningful
  return value, and the earlier `void*` surface forced extra return-value
  cleanup in the candidate.

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
- The updater reads owner `+0x2964` as a target vector during state `3`; this
  is the same `cached_camera_target_world` field produced by the camera block in
  `update_subgoldy`.

Type consolidation:

- `RingOrSpecialEffectParent::state`, `transition_progress`,
  `transition_step`, `oscillate_x`, and `RingEffectRateSource::paused` are now
  in `tools/match/include/ring_special_effect_types.h`.
- 2026-06-16 naming correction: the old exported name
  `update_subgoldy_bullet` was stale. The function is the virtual updater for
  `RingOrSpecialEffectParent`, cross-confirmed by the ring/special-effect
  runtime initializer, spawner, child-particle initializer/updater, and
  collision consumer. The reference manifest keeps the old jump-table name as
  an alias only. Focused Wibo remains unchanged at `86.35%`, and the direct
  spawner caller remains unchanged at `51.23%`.
- `RingOrSpecialEffectParent` now inherits the shared `BodNode` prefix, and
  the remover uses `RingOrSpecialEffectListAnchor` (`BodList`) for the
  active/free anchor at `g_game_base + 0x5a8`. The old scratch-local `next`
  (`+0x08`) and `prev` (`+0x0c`) names were corrected to
  `list_prev`/`list_next` to match the shared prefix.
- 2026-06-16 renderable-prefix correction: the parent `position +0x68` updated
  by this virtual method is `RenderableBod::transform.position`. The shared
  parent now exposes the complete `+0x38..+0x77` transform row block instead of
  treating it as anonymous padding.
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
  `68.48%` to `69.77%`. The current state-3 collapse also stages an immutable
  local copy of `owner_player->cached_camera_target_world` before computing and
  scaling the delta. This recovers the native `sub esp, 0x18` frame. The later
  state-switch correction raised the scratch to `79.53%`; the state-1 branch
  shape pass below raises it further to `86.35%`, although native still uses a
  different x87/stack schedule for the target lanes.
- Remaining residuals are mostly switch and stack-shape differences: VC6 still
  uses a different stack and x87 schedule for the state-3 collapse and the
  duplicated removal tails. The dispatch itself now matches native's direct
  `0..5` jump table.
- 2026-06-16 state-1 branch-shape pass: spelling the z-threshold as
  `position.z < owner_player->interaction_max_z` with the removal path in the
  taken source block recovers the native physical order for the remove-vs-lives
  decision. Focused Wibo improves from `79.53%` to `86.35%` while preserving
  the native `0x18` stack frame. The only new audit debt is the candidate local
  switch-table symbol (`$L1005`) versus the curated target
  `update_ring_or_special_effect_parent_state_jump_table`; the dispatch
  instructions and table shape are otherwise unchanged.

Rejected/source-shape probes:

- Spelling the collapse as explicit unscaled `target_y`, `target_z`, and
  `delta_*` locals regressed to the previous `68.48%` shape, so keep the
  aggregate `Vector3 delta`.
- 2026-06-16 collapse staging probes: changing case `0`/default to explicit
  early returns alone compiled identically and did not fix the jump table;
  the winning shape required the explicit unsigned range guard. Staging
  `rate->paused` in a local byte also compiled identically. Mutating a local
  `Vector3 target.z` before computing delta improved only to `70.52%`, and a
  pointer plus scalar `target_y`/`target_z` spelling regressed to `70.55%` with
  a smaller frame. Keep the immutable local `Vector3 target` plus aggregate
  `Vector3 delta` form.
- 2026-06-16 rechecked after the state-1 branch-shape pass: the pointer plus
  scalar `target_y`/`target_z` collapse spelling reaches `87.72%`, but it drops
  the native `sub esp, 0x18` frame to `0x0c` and shrinks the candidate to
  `332/336` instructions. Reverted; the aggregate `Vector3 target`/`delta`
  spelling is still the better structural match.
