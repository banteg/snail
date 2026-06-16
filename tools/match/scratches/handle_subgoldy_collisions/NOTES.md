# WIP scratch — 45.15%, 647/673 insns (2026-06-16 audio/voice call-surface pass)

Structure complete: all eight pool sweeps in order with asm-verified
offsets. The low ratio is systematic small deltas, leads for next pass:

2026-06-16 audio/voice call-surface pass: replaced the scratch-local free
`play_sound_effect`/`play_voice_manager` declarations with compact manager
method views (`g_sound_effect_manager` and `g_voice_manager`). This matches the
native global-thiscall call shape without importing the broader shared audio
headers, improves the focused match from `43.33%` to `45.15%`, and raises the
masked audit from `65 ok` to `70 ok`. The remaining masked mismatch is still the
slug-block alignment debt (`kill_slug_hazard` vs `begin_post_follow_carryover`),
not an audio-symbol problem.

2026-06-16 slug method call-surface pass: replaced the scratch-local free
`kill_slug_hazard(int)` / `play_slug_voice(int, int)` declarations with the
shared `SlugHazardRuntime` method declarations. BN prototypes and the exact
`kill_slug_hazard` / `play_slug_voice` scratches agree these are methods, and
the collision scratch now emits real thiscall setup at the slug callsites.
Focused match improves from `45.15%` / 647 candidate insns to `45.36%` / 641.
The masked mismatch still reports `kill_slug_hazard` vs
`begin_post_follow_carryover`, so this did not solve the slug-block alignment
debt. Keep the slug pool byte-strided here: the helper methods are proven, but
the shared `SlugHazardRuntime` header does not yet prove a 0xec pool stride.

- Rejected probe: spelling a local `unsigned char movement_kill_mask = 0x80`
  did not produce native's `bl` mask register reuse. VC6 propagated it back to
  literal `test byte [esi+0x338], 0x80`, leaving the match at `43.33%`; keep the
  literal mask tests until the loop/register shape has a real owner.

2026-06-16 Player field promotion: `damage_retrigger_timer`/`step`
(`+0x1d4/+0x1d8`), `control_override_active` (`+0x2d8`), and
`completion_handoff_active` (`+0x440`) are now promoted in shared
`player.h`. These are cross-confirmed by this collision scratch and
`update_subgoldy`; `completion_handoff_active` is also aligned with the
post-follow carryover/camera exit gate notes. The collision scratch keeps its
local `Player` window for codegen, so this is a struct consolidation step, not
a score change.

2026-06-16 typed runtime-pool pass: the scratch now includes the shared
health, speedup, jetpack, garbage, salt, parcel, and ring/special-effect
headers in the local `Game` window. This is a relationship/field-certainty
pass rather than a source-shape win: the score drops from the prior
proof-shape `48.79%` to `43.33%` because the typed slot views change VC6's
loop base registers and stack slots. The useful cross-confirmations are:

- `TrackSpeedupRuntime` has a full `world_position` vector at `+0x68..+0x70`
  and `state` at `+0x80`; `update_track_speedup` only needed the z lane, but
  collision consumes x/y/z.
- `TrackHealthPickup`, `TrackJetpackPickup`, `TrackParcelRuntime`,
  `GarbageHazardSlot`, and `RingOrSpecialEffectParent` all line up with their
  shared headers at the collision callsites.
- `GarbageHazardSlot` now inherits the shared zero-offset
  `ContactTargetObject` prefix used by `append_subgame_contact_target`; this
  collision scratch consumes the same state/list node/body fields, while the
  per-frame registry append path consumes the prefix flags.
- `Player +0x404` is the lives counter used by the ring/special-effect reward
  ladder; this cross-confirms the shared `Player::lives` promotion.
- `Player::damage_gauge` at `+0x3c4`, `Player::jetpack_gauge` at `+0x2750`,
  and `Player::cached_camera_target_world` at `+0x2964` are now promoted in
  `player.h`. This collision scratch still keeps a broad local `Player` window
  because it touches several not-yet-promoted lanes, but these three fields are
  no longer scratch-only evidence.
- The salt collision live byte remains deliberately spelled as
  `*(unsigned char*)&slot->velocity.z`: the byte is cross-confirmed by the
  salt spawner, but the surrounding semantic field is still not named.

2026-06-16 pickup/runtime offset correction pass: corrected the scratch-local
`Game` and `Player` windows to agree with the already matched/update-spawner
evidence:

- Game core fields now use `level_mode +0x40`, `level_mode_arg +0x44`,
  `base_subgame_rate +0x48`, and `runtime_flags +0x4c`, matching
  `set_subgame_features`, `populate_runtime_track_cells_from_segments`, and
  `update_subgoldy`.
- The five collision-adjacent runtime regions are now aligned to the target:
  health pool `+0x356000`, speedup singleton `position +0x355e18/state
  +0x355e30`, jetpack singleton `position +0x355e74/state +0x355e9c`,
  ring/special-effect parents `+0x35b78c`, and the parcel HUD/total lanes
  `+0x35bb94/+0x1b01e0`.
- Corrected adjacent pool anchors that had drifted by one region:
  slug `+0x3563a0`, sub-lazer `+0x356b00`, salt `+0x3578c0`, garbage list
  head `+0x359140`, and track parcel/ring slots `+0x125e480`.
- Switched proven helpers back to method-call shape:
  `Player::add_subgoldy_score`, `Player::health_collect_particles`,
  `DamageGaugeController::apply_damage_gauge_delta`, and
  `JetpackGaugeController::arm_jetpack_gauge`.

Matcher impact: score improved from `45.71%` to `48.79%`, and the
speedup/jetpack/garbage/parcel offsets now agree with the target asm. The
matcher reports one masked call mismatch in the still-low-score slug block
(`kill_slug_hazard` vs the nearby carryover call); treat that as alignment
debt, not proof of the slug branch.

2026-06-13 matcher padding rebaseline: terminal object-padding normalization
removes untargeted bytes after final `ret` instructions, so the same source now
reports 45.15%, 656/673 instructions. This is a measurement correction, not a
source-shape change.

- frame 0x74 vs 0x5c: native stages MORE locals — the slug first-hit
  writes an unused staging triple (IDA v70=0/v71/v72 before the velocity
  stores) and the per-loop delta/probe pairs each own slots; add the
  staging Vec3 and check slot reuse
- the movement-flags 0x80 test rides a REGISTER (mov bl, 0x80; test bl,
  al) reused by the garbage-loop test — try a local mask variable
- delta.z wants fst+fcomp straight off the FPU (store z, compare in one
  flow) — the struct copy `probe = delta` currently intervenes; try
  per-component copies ordered after the z compare like the health loop
- velocity.z = -0.1f at ring kinds 3/7 compiles to `mov ebp, 0xbdcccccd`
  hoisted before the loop + reg store — NOT a byte-poke bug (IDA's -0.1
  confirmed); should fall out once loop shape aligns

2026-06-15 slug-hit shape pass: focused matcher now verifies 45.71%,
657/673 instructions, masked operands 64 ok / 0 mismatch. BN confirms the
repeat-hit native code multiplies by subgame_rate, then 0.0040000002f, then
-8.0f; staging the scaled rate prevents VC6 from folding the constants into
-0.032. Rewriting the slug-hit branch as normal-control paths first and the
movement-flag kill path last matches the native physical block order and
clears the previous `kill_slug_hazard`/`begin_post_follow_carryover` audit
misalignment.

Asm-verified field finds (cross-findings for the campaign):

- player+0x408 = Game* (the back-pointer)
- player+0x440 = completion_handoff_active — cross-confirms the
  unification's "damage-warning drain blocker at 0x4301bc"
- nuke_effect_progress/step at player+0x374/+0x378 (NOT 0x4180);
  initialize_nuke receives player+0x150 as this (overlaps the
  player_slot read — settle when the nuke port lands)
- pools (game-relative): salt state 0x357940/live byte 0x357954/pos
  0x357928; sub-lazer state 0x356b80/pos 0x356b68; garbage list head
  0x359140 (node: pos +0x68, next +0x80, state +0x84, direction +0x88);
  slug state 0x356420/pos 0x356408/object 0x3563a0/hit byte 0x356479;
  track rings state 0x125e4b8/pos 0x125e490; health state 0x356038/pos
  0x356010/particles 0x356000; speedup single 0x355e30/0x355e18;
  jetpack single 0x355e9c/0x355e74; ring effects state 0x35b80c/pos
  0x35b7f4/kind 0x35b814; parcel hud owner dword 0x35bb94, total
  0x1b01e0

# Dossier — scratch not yet written (673 insns, 2887 bytes)

cRSubGoldy::Collision() per cross-port symbols. target.asm committed.
The contact table, from the IDA export (line refs in 00444cf0-*.c):

| pool | walk | gate | effect |
|---|---|---|---|
| salt | 6080 bytes / stride 152 (40 x 0x98) | pre-gate < 1.0 then normalized dist < 0.98 | damage 0.15, damage_retrigger_timer seeded from retrigger_step when zero |
| sub-lazer | 3520 / 176 (20 x 0xb0) | < 1.0 then < 0.49 | damage 0.02 |
| garbage | (stride from loop) | < 1.0 then < 0.98 | velocity.x -= dir.x * vz * 0.18, velocity.z -= dir.z * vz * 0.1, direction byte from dir.x >= 0, score event 0, damage 0.04, random voice via next_math_random_value * -0.000061035156 |
| slugs | 1888 / 236 (8 x 0xec) | < 2.0 then < 1.5675001 | repeat hit: velocity.z = subgame_rate^2 * 0.004 * -8, damage 1.0; first hit: velocity = (0, tc*0.2, tc*-0.2), wobble lift_phase_step = 0, carryover/cutscene lanes |
| rings/pickups | 7000 / 140 (50 x 0x8c) | < 1.0 then < 1.24 | score event 3, ring ladder dispatch |

Validates the harvested checklist formulas (slug triplet, repeat-hit
knockback) and adds the garbage knockback pair and the ring 1.24 gate.
All damage flows through apply_damage_gauge_delta(state, amount, 0) —
the force parameter from the hit-flash harvest is visibly 0 here.

Verify-pass targets for the Zig port: salt/sub-lazer gates ported per
checklist; slug velocity lanes and garbage knockback are motion-slice
consumers (not yet portable); ring gate and score-event ids worth
diffing against the runner's pickup collision slots.

Match plan: five sequential pool loops with the shared
pre-gate-then-normalize idiom — start the scratch from the salt loop and
extend pool by pool; reuse the salt slot layout from the quartet.

## Verify pass (2026-06-12): Zig gates all confirmed

Diffed against the runner: salt 0.98, sub-lazer 0.49, garbage 0.98,
ring 1.24, slug 1.5675001 with the 2.0 z-gate, health 0.98, and the
damage_retrigger_timer seeded from retrigger_step when zero — all
present and correct (gameplay.zig constants + processRuntimeHazard /
pickup lanes). The June-10 audit fixes hold against the matched-grade
table. Remaining gaps are exactly the motion-slice consumers already on
the checklist: slug first-hit/repeat velocity lanes and the garbage
0.18/0.1 knockback pair. The eventual full match is proof-polish over a
now-verified model, so cluster 3's priority drops below the cameraman
and golb matches.
