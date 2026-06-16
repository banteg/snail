# update_subgoldy_bullet @ 0x43e830

Live source map for the ring/special-effect parent virtual updater.

Current match:

- `71.41%`, `339/336` candidate/target instructions, with `33` masked
  operands ok.
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
  `owner_player->lives` against it after the effect passes the player's
  interaction z limit; losing lives while the effect is behind the player
  drives the `4 -> 5` expansion/removal transition instead of immediate
  teardown.
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
  field instead of raw `player + 0x404` loads. Focused score remains
  `69.77%`.
- `Player::cached_camera_target_world` is promoted at `+0x2964` after
  cross-confirmation from the `update_subgoldy` producer and this ring
  transition consumer. Focused score and masked audit remain `69.77%`, `32 ok`.

Residual:

- Native duplicates the list-removal/child-kill tail for the three removal
  exits. The scratch now spells those exits explicitly, which raised the match
  from `28.32%` to `68.48%`.
- A `Vector3 delta` local for the state-3 collapse moved the scratch from
  `68.48%` to `69.77%`. The current state-3 collapse also stages an immutable
  local copy of `owner_player->cached_camera_target_world` before computing and
  scaling the delta. This recovers the native `sub esp, 0x18` frame and improves
  the scratch to `71.41%`, although native still uses a different x87/stack
  schedule for the target lanes.
- Remaining residuals are mostly switch and stack-shape differences: VC6 still
  collapses case `0`/default into a `state - 1` jump table, while native uses a
  direct `0..5` jump table.

Rejected/source-shape probes:

- Spelling the collapse as explicit unscaled `target_y`, `target_z`, and
  `delta_*` locals regressed to the previous `68.48%` shape, so keep the
  aggregate `Vector3 delta`.
- 2026-06-16 collapse staging probes: changing case `0`/default to explicit
  early returns compiled identically and did not fix the `state - 1` jump table.
  Staging `rate->paused` in a local byte also compiled identically. Mutating a
  local `Vector3 target.z` before computing delta improved only to `70.52%`,
  and a pointer plus scalar `target_y`/`target_z` spelling regressed to
  `70.55%` with a smaller frame. Keep the immutable local `Vector3 target`
  plus aggregate `Vector3 delta` form.
