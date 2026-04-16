# Re-audit Plan — Concrete Divergences (2026-04-16)

Working checklist from the five-agent BN audit. Each item cites BN addresses and Zig file:line. Work top-down; re-audit when the ranked list is clean.

See also: `docs/rewrite/port-status.md`, `docs/rewrite/subsystem-status.md`, `docs/rewrite/remaining-work-checklist.md` — several of these need doc corrections at the end of this pass.

## 1. Attachment-exit retirement (biggest architectural bug)

The whole retirement lane is in the wrong runner phase — `stepAttachmentExitState` only runs in `.phase == .fall`, but every native clear runs on the active track path.

- [ ] Move retirement out of `.fall` into the active-track step in `zig/src/gameplay.zig` (around :4236–4268 and :1257–1274)
- [ ] Implement 0x43bcb3 lane: `!follow_state.active && runtime_tile ∈ {0x0f,0x10,0x12,0x13}` OR `(damage_gauge.state==2 && is_slide_cache_tile_family(tile))` → clear unconditionally after velocity-damping triad
- [ ] Implement 0x43bf6f lane (swept re-entry failed → grounded snap): after primary+secondary swept probes, if `!follow_state.active && y<0.49 && y≥−0.163 && !open_neighbor && tile!=0x16 && velocity.y<−0.03 && velocity.y<0` → snap y=0.49, zero velocity, clear
- [ ] Implement 0x43c06d lane (tile-flags grounded re-snap): `velocity.y ≥ threshold(tile_flags_3d)` + `(runtime_flag & 4) != 0` + `(global & 2) == 0` + `y<0.49` → squidge, clear, snap y=0.49
- [ ] Tighten 0x43c3ea (trampoline): gate on `|y − cell_y| < 0.49` bounce envelope + squidge + velocity flip + sfx 0x29; currently fires every tick on tile 0x16
- [ ] Tighten 0x43ce75 (jetpack cap): add the missing `position.y<1.0` altitude gate
- [ ] Make `attachment_exit_progress` step (0x43ce96) the else-branch — run only when none of the five clears fire this tick
- [ ] Delete/revise test at `gameplay.zig:7812–7835` — the legacy "progress ≥ 1.0 timeout" clear doesn't exist in native (only store is 0x43ce96)

## 2. Damage / warning / jetpack gauges

- [ ] Add 6× accelerated drain in `update_damage_gauge` state 2 when `*(+0x4301bc)!=0` — extra `apply_damage_gauge_delta(-0.00666666683, 0)` per tick (native 0x441074). Constant currently absent in Zig.
- [x] Replace `disarmJetpackGauge` on `progress > 1.0` (gameplay.zig:3957) with "skip warning math this tick" — native does NOT disarm at overflow
- [ ] Add the `(progress − cycle_phase) ≥ 0.94` boundary crossing: call `set_snail_jetpack(0)` + `uninit_jet_particles` side effects at 0x43a441 (current port: stub marker only; needs snail-jetpack weapon visual + jet-particles actor ports first)
- [ ] Model native jetpack state 2 (hover). Add `end_jetpack_hover` (0x43a370) analogue. Currently Zig collapses to a bool.
- [ ] Add `apply_damage_gauge_delta` early-out: `(*(+0x4300b4) & 0x80) && !force` bypass gate
- [ ] Thread the `force` parameter through `applyDamageGaugeDelta` call sites
- [ ] Add hit-flash side-effects in `apply_damage_gauge_delta`: `change_snail_skin`, `play_voice_manager(0x751498, 0, 1, -1)`, fallback `play_voice_manager(0x751498, 9, 0, -1)`, `dispatch_cutscene_animation` (1 or 6 depending on `*(+0x430054)==0`)
- [ ] Add state 1→2 voice cue in `update_damage_gauge`: `play_voice_manager(0x751498, 0xe, 0, -1)` at 0x44115e, gated on `*(+0x42fde8)==0.49`
- [ ] Add `change_snail_skin(..+0x434038, 1, 0.2)` call in state-2 drainer (0x441054)
- [ ] Call `stop_warning_sample` on state-2 exit (0x441105 → `stop_warning_sample_handle(play_warning_sample_backend(0x32))`)
- [ ] Model global pause gate `data_4df904 + 0x74621` — suppresses `update_warning`, `update_damage_gauge`, and the pulse lane (native 0x446f88, 0x440fdc, 0x4411fa)
- [x] Stop writing `pulse_envelope=1.0` in `armJetpackGauge` — native leaves it unwritten
- [ ] Wire `set_snail_jetpack` sfx: `play_sound_effect(0x1a)` on arm/activate, `play_sound_effect(0x10)` on deactivate + weapon-animation hooks

## 3. `handle_subgoldy_collisions` (0x444cf0)

- [ ] Add pool-A writer: `@0x357940` stride 0x98, 25 slots, +0.15 damage on contact (native 0x444e00). Currently missing in `gameplay.zig`.
- [ ] Add pool-B writer: `@0x356b80` stride 0xb0, 20 slots, +0.02 damage (native 0x444ebd). This is the "Wall2" pool the docs keep referring to; Zig conflates it with salt.
- [ ] Flesh out slug first-hit (currently just `beginFallState(.hazard)` at `gameplay.zig:1932`):
  - [ ] Write `velocity = (0, tc_x*0.2, -tc_x*0.2)` (0x4450cd)
  - [ ] Call `begin_post_follow_carryover`
  - [ ] Set cutscene state 0xa
  - [ ] Fire `firework_shoot` + `play_slug_voice`
- [ ] Add slug repeat-hit z-velocity knockback: `velocity.z += tc_x² × 0.004 × -8` (0x44521e)
- [ ] Drop the +100 score on invincible-path slug defeat — native's `kill_slug_hazard` does not call `add_subgoldy_score` (0x44523a). Currently `gameplay.zig:1917–1920` awards `slug_projectile_kill_score`.
- [ ] Replace `attachment_entry_rider_height` pre-loop check for health/jetpack pickups with per-slot `player.live_matrix.position.y >= 0.49` gate (BN 0x4453c4, 0x4455b1)
- [x] Wire the 7 collision sfx — already wired via counter/cue diffs in `main.zig:playGameplayRunnerAudio` (not via direct calls inside `processRuntimePickupCollisions`). Verified:
  - [x] 0x44500a: sfx `0x27 - rand` (garbage hit) — `garbage_hits` counter → `asteroid_impact` pick
  - [x] 0x4452fb: sfx `0x1b` (parcel pickup) — `NativeGameplaySoundCues.parcel_pickup` → `place_package`
  - [x] 0x44542f: sfx `0xe` (health collect) — `health_pickups` counter → `heart`
  - [x] 0x4456f2: sfx `0x2b` (native ring 3/7 slow) — `nativeSlowRingSoundTriggered` → `slow_ring`
  - [x] 0x445763: sfx `1` (ring kind 1) — `nativeRingPickupSoundIndex` → `powerup_pickup[0]`
  - [x] 0x44578d: sfx `0x2a` (ring kinds 2/6 nuke) — `nativeExplodeRingSoundTriggered` → `explode_ring`
  - [x] 0x44580d: sfx `eax_50 + 1` (ring kinds 4/5/8) — `nativeRingPickupSoundIndex` via `movement_flag_selector`
- [ ] Wire the 3 voice cues:
  - [ ] `play_voice_manager(0x751498, 0xa, ...)` at 0x4452ef (parcel voice)
  - [ ] `play_voice_manager(0x751498, 5, ...)` at 0x4457d4 (ring-4/5 voice)
  - [ ] `play_slug_voice(0x22 - rand)` at 0x44516c
- [ ] Add garbage direction-of-hit field: slot `+0x88 = 1 or 2` depending on `vector.x > 0` (0x444fb8–0x444fc2)

## 4. Outer-bridge saved-owner writers

- [ ] Mirror `destroy_subgame → +0x1bc = 0x12` (native 0x438b09) in Zig's teardown path. Consequence of missing it: a persistent selected-record run torn down via a path that bypasses `outerOwnerForPendingRunResult` / `outerOwnerForAbandonActiveRun` returns to the wrong outer owner instead of the high-score list.
- [ ] Audit whether both `update_subgame` post-run preserve ops (0x439994 / 0x4399b2) are modeled via `outerOwnerForPendingRunResult`. Docs currently credit them to "state 2 at boot" which is wrong.
- [ ] Decide on menu-local `+0x4f2dc+0x14` step field and `+0x8/+0xc` suppressor — zero direct writers exist in the decompile set; the fields are likely init-only via the owning struct constructor. Confirm with a runtime Frida capture before porting a guessed cadence.

## 5. Voice-4 milestone — close as dead code

- [x] Do not port voice-4 at 0x420d30. Field `[esi+0x44]` is `PathTemplate.segment_count` (not `sample_count`). Gate `sample_index+1 == segment_count*2` is unreachable — termination at `sample_index == segment_count` fires first. Just close the item.

## 6. Doc corrections (after fixes land)

- [ ] `docs/rewrite/port-status.md:205` — stop claiming the attachment-exit proxy is "closer to recovered 0x43bf6f/0x43c06d/0x43c3ea lanes". Rewrite to reflect the actual lanes once ported.
- [ ] `docs/rewrite/subsystem-status.md:210–215` — mark voice-4 as dead code (not "contradictory"); fully identify 0x43c06d as tile-flags grounded re-snap and 0x43c3ea as trampoline bounce.
- [ ] `docs/rewrite/subsystem-status.md:365` — correct "update_subgame state 2 at boot copies `+0x1b8` into `+0x1bc`" — that preserve op is in the post-run completion branches at 0x439994 / 0x4399b2, not boot.
- [ ] `docs/rewrite/remaining-work-checklist.md:120, 172` — saved-owner writer set is wrong; attachment retirement winner after swept re-entry is 0x43bf6f (not 0x43bcb3, which is the parallel non-follow lane).
- [ ] Fix menu-local offset in docs: hide latch is `+0x4f2dc+0x4` (i.e. `data_4df904 + 0x4f2e0`), not `+0x14`. The `+0x14` is the unwritten step field.
