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
- [ ] Add `AppState.playVoiceManagerIndex(set_id: NativeSet, mode: NativeMode, sample_override: ?usize) !bool` in `zig/src/main.zig`. Semantics from `play_voice_manager` @ 0x4492d0:
  - `mode = .interrupt_current` → first call `stopGameplayVoice()` (new helper wrapping `rl.stopSound` on the current voice channel)
  - `sample_override = null` → delegate to existing `tryPlayNativeGameplayVoiceSetPlayed(set_id, mode)`
  - `sample_override = some i` → new `tryPlayNativeGameplayVoicePayload(set_id, mode, i)` that bypasses playlist rotation and plays bank[i] directly
  - return whether a sample actually started (native uses this for the damage→ouch fallback chain)
- [ ] Wire the 4 blocked sites:
  - [ ] `apply_damage_gauge_delta` hit-flash voice (0x441489): `.damage, .wait_for_frequency` then fallback `.ouch, .wait_for_idle`
  - [ ] `update_damage_gauge` state 1→2 voice (0x44115e): `.postal, .wait_for_idle` (plays `IMGOINGPOSTAL{,2,3}.OGG`)
  - [ ] Parcel collision voice (0x4452ef): `.package, .wait_for_frequency`
  - [ ] Ring 4/5 collision voice (0x4457d4): `.powerup, .wait_for_frequency`
- Files: `zig/src/main.zig:5795-5826` (voice infra), `gameplay/voice.zig`

### F. Close jetpack 0.94 TODO as verified no-op
- [ ] Convert the TODO comment at `gameplay.zig:4005-4012` into a `PORT(verified)` block explaining:
  - sfx activate/deactivate is already fired by `nativeJetpackSoundCues` (audio_cues.zig:141-150) on exactly the 0.94 edge
  - thrust-cone mesh swap is already driven by `nativeJetpackVisualPresentationActive(runner) == runner.jetpack.active and progress <= 0.94`
  - `uninit_jet_particles` targets a 15×2 sprite column pool the Zig port does not own; there's nothing to tear down
  - The one-shot is functionally complete
- [ ] Add a regression test asserting the 0.94 crossing does NOT rearm any jetpack state.

## Phase 1 — `change_snail_skin` (independent, small)

### B. Snail skin texture-slot swap
- [ ] Add `PlayerPresentationController.snail_skin: SnailSkinTransitionState` to the Zig gameplay state (new module or inside `gameplay.zig`). Fields mirror native 0x1938 layout:
  ```zig
  SnailSkinTransitionState {
      selected_slot: u8,    // 0=default, 1=damage-red, 2=invincible
      slot_ids: [3]u32,
      active: bool,
      progress: f32,
      progress_step: f32,   // 1 / (duration_s * 60) when duration > 0, else 0 (instant)
  }
  ```
- [ ] Port `changeSnailSkin(slot, duration_s)` from `change_snail_skin` @ 0x445fd0: sets `active=1`, selected slot, and progress_step (or 0 for instant).
- [ ] Port `updateSnailSkinTransition` tick from `update_snail_skin_transition` @ 0x445f80: advances `progress` by `progress_step`, resolves `slot_ids[selected_slot]` into the render-state material slot.
- [ ] Wire at the 5 native call sites:
  - [ ] `initialize_invincible_shell`: reset (slot 0, 0.0 s)
  - [ ] `update_invincible_shell` case 3: fade-out done (slot 0, 0.0 s)
  - [ ] `update_invincible_shell` active tick: slot 2 every frame, 0.0 s
  - [ ] `apply_damage_gauge_delta` hit-flash: slot 1, 0.2 s
  - [ ] `update_damage_gauge` state 2 tick: slot 1, 0.2 s
- Note: only a texture swap — doesn't require the dispatch_cutscene_animation port below.

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
- [ ] Docs: in `port-status.md`, `subsystem-status.md`, `remaining-work-checklist.md`, rename "Wall2 ambient pool" references to "SubLazer projectile pool" and clarify that Wall2 AI is the *emitter*, the slots are projectiles.
- [ ] Docs: fix Pool-A label from "Wall2 pool" to "Salt hazard pool" (matches the 40-slot 0x98-stride `cRSalt` manager at `0x3578c0`).

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

Reshape in rev 2:
- Prior deferred items regrouped into 6 infrastructure phases with explicit dependency order.
- Several "infrastructure" items revealed to be already-present or trivial:
  - voice_manager already modeled; just needs a thin wrapper (small, Phase 0.A).
  - jetpack 0.94 boundary is already wired via sound/mesh cues; TODO closes as no-op (trivial, Phase 0.F).
  - snail-jetpack weapon visual already approximated via a parallel scaffold.
- Major rename: "Wall2 ambient hazard pool" in docs is actually the SubLazer projectile pool (cRSubLazerManager); Pool-A is the Salt hazard pool (cRSalt). Docs need corrections in Phase 3.E.1.
- Minimum viable attachment-exit retirement (lanes 1-2 only) requires just 5 floats + 1 bool on `Runner`, not the full physics port.
