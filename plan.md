# Re-audit Plan — Infrastructure First (2026-04-16, rev 2)

Infrastructure audit findings from the five parallel BN scans. The prior plan's "deferred" items all blocked on five infrastructure pieces. This revision orders the pieces by dependency and scopes the MVP slice that unlocks the most plan §1–§3 items.

See also: `docs/rewrite/port-status.md`, `docs/rewrite/subsystem-status.md`, `docs/rewrite/remaining-work-checklist.md`.

## Infrastructure audit summary

| # | Piece | Current Zig state | Work |
|---|---|---|---|
| A | `play_voice_manager` by-index dispatch | Already modelled as `NativeSet` + `NativeMode` in `gameplay/voice.zig`; just need a thin index→set wrapper with `interrupt_current` + optional explicit sample id | small |
| B | `change_snail_skin` (texture-slot swap) | Not ported. 6-field struct, 5 callers, 3 slot ids (0=default, 1=damage-red, 2=invincible) | small |
| C | `dispatch_cutscene_animation` (low-level clip selector) | Not ported. Separate from the existing high-level `cutscene_id`. IDs 1/3/4/5/6/7/8/9 = base/lookback-L/lookback-R/skidstop/damaged/intoshell/fall/talk | medium |
| D | Player motion state (`position`, `velocity`, ground snap, gravity-coupled y) | Not ported. Runner has no continuous `world_y` during `.active`, no `velocity.x/y/z`. Native owns everything in `update_subgoldy` @ 0x43b120. MVP slice = 5 floats + 1 bool | medium |
| E | Ambient hazard pools (Salt @ 0x3578c0 +0.15 dmg, SubLazer @ 0x356b00 +0.02 dmg) | Salt is conflated with runner-local live strip; SubLazer entirely absent. Docs misname SubLazer as "Wall2 ambient pool" — it's actually `cRSubLazerManager`, fired by Wall2 AI | medium-large |
| F | `set_snail_jetpack` one-shot + jet-particle pool | sfx + mesh swap **already covered** via `nativeJetpackSoundCues` + `GameplayJetpackVisualState`. The missing particle pool is optional presentation polish. 0.94 TODO closes as verified no-op. | trivial for TODO; jet particles are medium follow-up |

**Key renames/corrections from audit**:
- "Wall2 ambient pool at 0x356b00" in docs is really the **SubLazer projectile pool** (20 slots, stride 0xb0). It's *fired into* by Wall2 AI via `shoot_subgoldy`, but the slots themselves are projectiles.
- "Pool-A at 0x357940 +0.15 dmg" is the **Salt hazard pool** (40 slots, stride 0x98) — the same salt the Zig port already has as a runner-local hazard, but native owns a 40-slot pool the port conflates with a runner-local 8-row live strip.
- `voice-4` milestone from the prior audit was resolved as dead code — already closed.

## Phase 0 — Quick closures (small, independent)

### A. voice_manager by-index wrapper
- [x] All four blocked voice-cue sites are already wired via the diff-based `nativeGameplayVoiceCues` path in `gameplay/audio_cues.zig` — no new `playVoiceManagerIndex` wrapper required:
  - [x] `apply_damage_gauge_delta` hit-flash → `damage_entry` cue → `.damage` with `.ouch` fallback (`main.zig:2923-2927`)
  - [x] `update_damage_gauge` state 1→2 → `damage_escalation` cue → `.postal` (`main.zig:2929-2930`)
  - [x] Parcel collision → `package_pickup` cue → `.package` (`main.zig:2917-2918`)
  - [x] Ring 4/5 collision → `weapon_upgrade` cue → `.powerup` (`main.zig:2920-2921`)
  - Existing `tryPlayNativeGameplayVoiceSetPlayed` + `playVoiceByPath` already interrupt the current sound, so `.interrupt_current` mode semantics match native.

### F. Close jetpack 0.94 TODO as verified no-op
- [x] Converted the TODO at `gameplay.zig:4005-4019` into a `PORT(verified)` block. sfx activate/deactivate already fires via `nativeJetpackSoundCues.deactivate` on exactly the 0.94 edge; thrust-cone mesh is already hidden when `runner.jetpack.active and progress > 0.94` via `GameplayJetpackVisualState`; `uninit_jet_particles` targets a sprite column pool the port does not own. Nothing to tear down.

## Phase 1 — `change_snail_skin` (independent, small)

### B. Snail skin texture-slot swap
- [x] `SnailSkinTransition` struct added to `gameplay.zig` with 3 slots (default/damage/invincible), mirrors `change_snail_skin` @ 0x445fd0 + `update_snail_skin_transition` @ 0x445f80 timing (`progress_step = 1/(duration_s*60)` for timed swaps, 0 for instant).
- [x] Wired at the native call sites the Zig port currently represents:
  - [x] `applyDamageGaugeDelta` hit-flash branch: slot 1, 0.2s
  - [x] `updateDamageGaugeController` state-2 drain tick: slot 1, 0.2s
  - [x] `stepTemporaryStates` while `invincible_ticks > 0`: slot 2 every tick, instant
  - [x] Expiry tick when `invincible_ticks` reaches 0: slot 0, instant
- [ ] Future: hook render-state material index lookup once the snail-presentation render layer is ported (current port stores the transition state but has no renderer-side consumer yet).

## Phase 2 — Player motion MVP (D, medium)

MVP slice unlocks plan §1 lanes 1 & 2 (0x43bcb3 slide/floor-cache + 0x43bf6f swept-reentry grounded snap) without porting the full physics step.

### D.1 Minimum motion state
- [ ] Add to `Runner`:
  ```zig
  position_y: f32 = 0.49,       // mirror of Player+0x006c
  velocity_y: f32 = 0.0,        // mirror of Player+0x0414
  follow_active: bool = false,  // mirror of Player+0x0384 FollowState.active
  // attachment_exit_anchor_z already exists
  ```
- [ ] Track `follow_active` as a derived bool from the existing attachment-follow state machine (expose a getter).

### D.2 Minimum step functions (in the active-phase tick)
- [ ] `applyGravityCoupledY(self)` — mirror of `update_subgoldy` @ 0x43c316: `velocity_y += -0.01 * v_z²`. For the MVP, v_z = `movement_rate_scalar` (or a fixed proxy constant) until full `velocity.z` is modelled.
- [ ] `positionYIntegrate(self)` — mirror of 0x43bac4: `position_y += velocity_y`.
- [ ] `beginPostFollowCarryover(self)` — already partially modelled in `gameplay.zig`. Stashes `row_position` (proxy for Player+0x424 / attachment_exit_anchor_z), sets the pending+progress+gate_a/b fields. Audit whether existing implementation matches `begin_post_follow_carryover` @ 0x43af60.

### D.3 Two attachment-exit retirement lanes (depends on D.1, D.2)
- [ ] Lane 0x43bf6f (swept re-entry failed → grounded snap): after primary+secondary `flags_b & 0x40` / `& 0x80` swept probes in `tryPrimeCurrentRowAttachmentEntry`:
  - if `!follow_active && position_y<0.49 && position_y>=-0.163 && !open_neighbor(tile) && tile!=0x16 && velocity_y<-0.03 && velocity_y<0`:
    - snap position_y = 0.49
    - velocity_y = 0
    - clear attachment_exit_pending
    - apply squidge (need a squidge model; defer visual-only squidge to later)
- [ ] Lane 0x43bcb3 (slide/floor-cache non-follow fallback): **not gated on follow_active** — fires on runtime tiles `{0x0f,0x10,0x12,0x13}` OR (damage_warning_state==draining && is_slide_cache_tile_family(tile)). Does NOT depend on position_y — clears unconditionally within that branch. Can land with or without D.1 since it doesn't read y.
- [ ] Make the `attachment_exit_progress` step (0x43ce96) the explicit else-branch — only runs when neither 0x43bcb3 nor 0x43bf6f fired this tick.

### D.4 Follow-ups after MVP (record as TODOs, don't land yet)
- 0x43c06d tile-flags grounded re-snap (needs tile flags_3d + global flag 2 mirror)
- 0x43c3ea trampoline envelope (needs cell_y accessor; current proxy fires too eagerly)
- 0x43ce75 jetpack altitude gate (needs position_y plus jetpack_gauge.state==1 mirror)
- Full `position.x` / `velocity.x` model + ±4 clamp (lateral)
- Full `velocity.z` model + the autorun integrator
- Slug first-hit velocity triplet + slug repeat-hit knockback (need velocity.x/y/z)

## Phase 3 — Ambient hazard pools rename + port (E, medium-large)

### E.1 Rename + reassign
- [x] Docs: renamed "Wall2 ambient pool" references to "SubLazer projectile pool" across port-status, subsystem-status, and remaining-work-checklist. Clarified that Wall2 AI is the *emitter*, the slots are projectiles fired via `shoot_subgoldy`.
- [x] Docs: labeled the `+0.15` damage pool as the Salt hazard pool (`cRSalt` @ 0x3578c0, 40 slots, stride 0x98).

### E.2 Salt hazard pool port
- [ ] Replace the runner-local 8-row live strip's `.salt` branch with a dedicated `SaltHazardPool` struct (40 slots, each with `active`, `armed`, `position`, `velocity`, `transform`, `owner_attachment`).
- [ ] Port `initialize_salt_hazard_pool` @ 0x441540, `spawn_salt_hazard` @ 0x441560, `update_salt_hazard` @ 0x4417d0, `deactivate_salt_hazard` @ 0x441740.
- [ ] Collision consume at +0.15 damage using the `dist < 0.98` gate (inside existing `processRuntimeHazardCollisions`).
- [ ] Spawn from `update_subgame` tile dispatch on authored `0x22` tiles and `0x0f` with RNG gate `0.98 + 0.02*(1-scalar)`.
- [ ] Remove `.salt` from `RuntimeHazardKind` live strip seeding; keep only `.garbage`.

### E.3 SubLazer projectile pool port
- [ ] Add `SubLazerPool` (20 slots, each with `active`, `position`, `velocity`, `phase`, `lifetime`, `emitter`, `sprite_scale_y_base`).
- [ ] Port `initialize_wall2_ambient_hazard_pool` @ 0x441650, `spawn_wall2_ambient_hazard` @ 0x441670, `update_wall2_ambient_hazard` @ 0x43efb0, `destroy_wall2_ambient_hazard` @ 0x439bc0.
- [ ] Port `shoot_subgoldy` @ 0x441ad0 invocation path.
- [ ] Port `maybe_spawn_wall2_ambient_hazard` @ 0x439d50 with RNG gate + `game+0x74668 > game+0x42fdec` cadence.
- [ ] Collision consume at +0.02 damage using `dist < 0.49` gate.

## Phase 4 — `dispatch_cutscene_animation` layer (C, medium)

- [ ] Add `PlayerPresentationController.anim_manager: AnimDispatchState` with the native layout from `path_template_types.h:354`:
  ```
  active, progress, progress_step, active_keyframe, edge_latched,
  queued_animation_ids[10], queued_animation_count,
  self_ref, queue_sentinel
  ```
- [ ] Port `dispatchCutsceneAnimation(anim_id, immediate, initial_frame)` from `dispatch_cutscene_animation` @ 0x444600:
  - `immediate=false` → enqueue into `queued_animation_ids[queued_count++]`
  - `immediate=true` → index `animation_slot_table` (128-byte stride at presentation_controller + 0x14c+0x24), latch keyframe, clear queue, set flag 0x20
- [ ] Load the per-clip keyframe table from shipped `X/_ANIMATION.TXT` entries (base/move/bobalong/damaged/fall/lookback-L/lookback-R/talk/skidstop/intoshell).
- [ ] Define constants: `ANIM_BASE=1`, `ANIM_LOOKBACK_L=3`, `ANIM_LOOKBACK_R=4`, `ANIM_SKIDSTOP=5`, `ANIM_DAMAGED=6`, `ANIM_INTOSHELL=7`, `ANIM_FALL=8`, `ANIM_TALK=9`.
- [ ] Replace the existing "manual turbo-talk family switch" in Zig with real `dispatchCutsceneAnimation(.talk, true, 0)`.

## Phase 5 — Hit-flash wiring (depends on Phases 0.A, 1.B, 4.C)

- [ ] Mirror `apply_damage_gauge_delta` @ 0x4413f0 hit-flash side effects in Zig's `applyDamageGaugeDelta` (gameplay.zig:2322):
  - [ ] Gate: `(*(+0x4300b4) & 0x80) && !force` early exit — need to identify the invincible-flag source first (no writers visible in decompile; likely set by `update_invincible_shell`)
  - [ ] Thread a `force: bool = false` parameter through all call sites
  - [ ] When gated: `changeSnailSkin(1, 0.2)` then `playVoiceManagerIndex(.damage, .wait_for_frequency, null)` — if returns false, fallback `playVoiceManagerIndex(.ouch, .wait_for_idle, null)`; then `dispatchCutsceneAnimation(6, true, -1)` if `*(+0x430054)==0` else `dispatchCutsceneAnimation(1, false, -1)`
- [ ] Mirror state-2 drain side effects in `updateDamageGaugeController` (gameplay.zig:~2410):
  - [ ] `changeSnailSkin(1, 0.2)` each tick while draining
  - [ ] `playVoiceManagerIndex(.postal, .wait_for_idle, null)` on state 1→2 transition
- [ ] Call `stop_warning_sample_handle` analogue on state-2 exit.

## Phase 6 — Remaining attachment-exit lanes + slug velocity (depends on Phase 2 extensions)

Once the full `MotionState.velocity.x/y/z` + tile-flags mirror lands (not MVP):

- [ ] Lane 0x43c06d (tile-flags grounded re-snap).
- [ ] Lane 0x43c3ea trampoline envelope (tighten from the current broad heuristic to `|y - cell_y| < 0.49` + velocity flip + sfx 0x29).
- [ ] Lane 0x43ce75 jetpack altitude cap.
- [ ] Slug first-hit velocity triplet `(0, tc_x*0.2, -tc_x*0.2)` + `begin_post_follow_carryover` + cutscene state 0xa + firework_shoot + `play_slug_voice(0x22-rand)`.
- [ ] Slug repeat-hit z-velocity knockback `tc_x² × 0.004 × -8`.
- [ ] Garbage direction-of-hit field (slot +0x88 = 1 or 2 based on `vector.x > 0`).

## Phase 7 — Remaining polish (independent, small each)

- [ ] Global pause gate `data_4df904 + 0x74621` on `update_warning`, `update_damage_gauge`, pulse lane — low impact since no visible divergence has been observed.
- [ ] `update_damage_gauge` 6× accelerated drain — **blocked**: `*(+0x4301bc)` has no writers in the decompile set; needs a live Frida trace before the flag's meaning can be inferred.
- [ ] Jetpack state 2 (hover) controller + `end_jetpack_hover` @ 0x43a370 — large; belongs with a broader jetpack hover-mode port that isn't prioritized yet.
- [ ] Health/jetpack pickup per-slot `player.live_matrix.position.y >= 0.49` gate (depends on Phase 2 `position_y`).
- [ ] Outer-bridge safety net: mirror `destroy_subgame → +0x1bc = 0x12` (native 0x438b09). Current Zig paths compute the right owner via helpers; this is a defensive safety net. Defer until a repro surfaces.
- [ ] Jet-particle pool + `SPRITES/JETPACKTHRUST.TGA` + `SPRITES/SMOKE.TGA` loading (medium, presentation polish).

## Session summary (2026-04-16, rev 2)

Closed in rev 1:
- Voice-4 milestone as dead code.
- Jetpack disarm-on-overflow and route-end-auto-shutoff corrected.
- `armJetpackGauge` no longer writes `pulse_envelope`.
- Invincible-path slug defeat no longer awards kill score.
- All 7 collision sfx verified already wired.
- All doc corrections.

Closed in rev 2:
- Voice-manager (Phase 0.A): already-wired verification — `damage_entry` / `damage_escalation` / `package_pickup` / `weapon_upgrade` cues cover all 4 blocked sites via existing `tryPlayNativeGameplayVoiceSet` plumbing.
- Jetpack 0.94 TODO (Phase 0.F): closed as verified no-op.
- `change_snail_skin` (Phase 1.B): `SnailSkinTransition` struct + `tick()` + wiring at hit-flash, state-2 drain, invincible active, invincible expiry.
- Ambient hazard pool rename (Phase 3.E.1): SubLazer / Salt rename landed across all three status docs plus the remaining-work-checklist entry.
- `activeTrackAttachmentExitRetires` docstring: now cites all three native lanes (0x43bcb3 / 0x43bf6f / 0x43c3ea) and the predicates each requires; acknowledges the proxy stays until the motion model lands.

Deferred to next session:
- Phase 2 (player motion MVP): `position_y` / `velocity_y` fields + gravity/integration + grounded detection. Needed to tighten attachment-exit retirement from the broad proxy to the three native lanes. Scope grew beyond a quick landing because the runner's active-phase state has no continuous vertical coordinate today.
- Phase 3.E.2–E.3 (actual Salt/SubLazer pool ports): medium-large work, separate from the rename.
- Phase 4 (`dispatch_cutscene_animation`): medium work, needs the per-clip keyframe table loader.
- Phase 5 (hit-flash side effects beyond snail-skin): depends on `dispatch_cutscene_animation` for the entry animation (id 6 → damaged).
- Phase 6 (remaining attachment-exit lanes + slug velocity writes): depends on Phase 2.
- Phase 7 polish items.
