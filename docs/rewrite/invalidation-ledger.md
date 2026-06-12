# Invalidation Ledger

Use this ledger only when new RE or runtime evidence overturns a previously trusted model.

Why this exists:
- prevent old workaround narratives from becoming sticky repo memory
- surface which assumptions are no longer safe to port against
- point the next dossier at the exact model that needs replacement

Add entries only when one of these happens:
- a previous owner or writer claim is disproved
- a field meaning changes materially
- a controller boundary moves
- a parity test is demoted from `parity` to `scaffold`

Keep entries short:
- date
- subsystem
- invalidated claim
- replacement evidence
- immediate port consequence

Template:

## YYYY-MM-DD - Subsystem

- invalidated claim:
- replacement evidence:
- port consequence:

## 2026-06-12 - Salt hazard slot layout

- invalidated claim: the salt slot is a self-contained 0x98-stride record
  and IDA's update render reads a velocity triple seeded by spawn
- replacement evidence: matched/pinned asm (tools/match scratches for the
  salt quartet) shows spawn seeds velocity.x = 0, velocity.y =
  game[+0x74650]/30, and pokes only the LOW BYTE of velocity.z (+0x94) —
  while update integrates all three lanes as floats; progress/step at
  +0x98/+0x9c sit past the 0x98 stride in the next slot's header and are
  never initialized by spawn
- port consequence: velocity.z is effectively zero (denormal) and the
  progress-based state-2 transition almost never fires; lifetime is
  governed by collision, y < 0, kill plane, and the tile-14 floor exit.
  Cataloged as OB-1/OB-2 in original-bugs.md (fixed by default,
  `--preserve-bugs` for differential runs; both happen to be
  observationally identical either way)

## 2026-06-12 - Attachment entry height model

- invalidated claim: attachment entry follow height is family-dependent
  (`nonlinear_42` keeps the raw local rider offset, other families clamp
  `max(0, local_y - 0.49)`)
- replacement evidence: matched native source (tools/match) shows no family
  branch on either entry lane — `begin_track_attachment_follow_state`
  (94.55%) seeds raw world `y - 0.49` unclamped, and
  `try_enter_track_attachment_from_swept_motion` (structure-aligned scratch)
  seeds `vertical_offset = 0` and snaps the player's world y to the rotated
  local-frame y before the validating follow update
- port consequence: `entryVerticalOffset` removed from
  `gameplay/attachment.zig`; the direct lane in
  `currentRowInstalledAttachmentEntry` now seeds world `y - 0.49` and the
  swept lane seeds zero; the swept sample gate now skips `<= 0` like the
  native `fcomp`/`test ah, 0x41` pair

## 2026-06-10 - Game runtime fields

- invalidated claim: `Game+0x38` is `track_center_x` (a lateral coordinate) and `Game+0x3c` is padding
- replacement evidence: `calc_subgame_rate` @ 0x4404d0 writes `+0x38` as the live per-tick gameplay rate consumed by the movement clamps (`rate*0.17/0.5`), gravity (`rate²`), and the cameraman matrix blend (`rate*0.3`); `build_subgame_level` writes `+0x3c = 2`, `update_subgame_camera` branches on `+0x3c == 1`, and `calc_subgame_rate` gates on `+0x3c != 2`
- port consequence: BN, both checked-in headers, and the binja sync tuples now name these `subgame_rate` / `subgame_state`; the Zig runner field `track_center_x` (which stores the rate) should be renamed to match and to stop inviting the rate/center-x conflation that produced the cameraman blend bug

## 2026-06-10 - Attachment follow voice-4 milestone

- invalidated claim: the `voice 4` lane in `update_track_attachment_follow_state` @ 0x420cb0 is an unresolved milestone that may need porting
- replacement evidence: the guard compares the incremented sample index against `2 * PathTemplate+0x44` while the loop terminates at `== +0x44`, and both entry paths seed the index below `+0x44` (`begin_track_attachment_follow_state` seeds 0; the swept scan stays below the count) — the call is unreachable; a BN comment at 0x420d1d now records this
- port consequence: do not port the voice-4 milestone; remove it from open-question lists

## 2026-06-10 - Jetpack gauge

- invalidated claim: `update_jetpack_gauge` keeps the gauge state live when `progress > 1.0` or within 5 rows of the route end, only skipping the warning math (`PORT(verified)` comments in `zig/src/gameplay/jetpack.zig` and `zig/src/gameplay.zig:10903`)
- replacement evidence: both decompilers show that branch fully disarms — `end_jetpack_hover`, conditional `set_snail_jetpack(0)` when `progress <= 0.94`, `state = 0`, wobble fields zeroed (`analysis/decompile/ida/functions/0043a390-update_jetpack_gauge.c:23-32`, BN @ 0x43a543-0x43a579)
- port consequence: `Gauge.update` must disarm on fuel exhaustion and the near-route-end window; `gameplay.zig:2456` otherwise grants jetpack forward velocity forever; the two tests encoding the stay-active behavior must flip (full audit: `analysis/runtime/port-parity-audit-2026-06-10.md`)

## 2026-03-25 - Outer bridge

- invalidated claim: ordinary respawn rebuild should stay modeled as a saved-owner bridge opcode lane
- replacement evidence: March 24 Windows capture shows ordinary respawn rebuilding through direct owner `0x1c`, not `0x1a/0x1b`
- port consequence: respawn bridge state in Zig must store the direct selector as authoritative and stop using the request dispatcher as the conceptual center

## 2026-03-25 - Runtime capture policy

- invalidated claim: broader Windows capture is still the default next step for bridge and attachment work
- replacement evidence: the stable March 24 subsystem notes closed the practical bridge handoff lanes, while broader probe sets caused host hangs
- port consequence: outer bridge is unblocked for replacement from the locked capture baseline; attachment exit stays static-RE only until a narrower stable proof exists

## 2026-03-26 - Ring runtime and Game fields

- invalidated claim: `game + 0x48` is `bonus_score`
- replacement evidence: `build_subgame_level` seeds `game + 0x48` from compact-record field `+0x48`, `calc_subgame_rate` uses it as the base gameplay rate, and `spawn_track_ring_or_special_effect` consumes it in the default ring `phase_step` formula
- port consequence: explicit ring timing should be modeled from authored `RingSpeed`, while default ramp-ring timing should be modeled from `base_subgame_rate`; future Zig ring-animation work must stop treating `game + 0x48` as a score lane

## 2026-03-26 - Player runtime slices

- invalidated claim: `player + 0x43c` is the persistent current track cell pointer
- replacement evidence: `initialize_subgoldy` seeds `+0x43c` from the per-player control-source globals, while `update_subgoldy` still gets the live current cell from the transient `get_track_grid_cell_at_world_position(...)` local
- port consequence: the shared `Player` typing and any Zig comments/docs must stop calling `+0x43c` `current_cell`; keep runtime-cell access transient and treat `+0x43c` as `control_source`

## 2026-03-26 - Squidge helper prototype

- invalidated claim: `start_squidge_z` returns `float`
- replacement evidence: the raw Windows helper only seeds `SquidgeState.z_phase` and `z_velocity`; on a fresh and current `.i64`, typing it as `void __thiscall start_squidge_z(SquidgeState*, float)` restores a clean high-level `update_subgoldy` decompile, while the float-return prototype alone forces Hex-Rays back into inline x87 asm
- port consequence: keep the checked-in BN/IDA type lane and any future helper signatures on `void`; do not infer helper return types from transient x87 stack residue when the call sites ignore the result

## 2026-03-26 - Player row-event tail

- invalidated claim: `player + 0x1ec..+0x1fc` is a standalone row-event `state/timer/data` block
- replacement evidence: `update_subgoldy` seeds that tail and passes `&player->row_event.tip_definition` to `enqueue_tip_message`; `initialize_tip` then reads it as flags, layout, dismiss timing, and text payload
- port consequence: keep only `row_event.id` as row-event-specific; model the tail as an inline tip-message definition and avoid hardening the old pure-row-event interpretation in Zig or docs

## 2026-03-26 - Player presentation root

- invalidated claim: `player + 0x29a8` is a standalone `snail_visual` sibling field and `player + 0x2984` is anonymous padding
- replacement evidence: `set_snail_weapon`, `dispatch_cutscene_animation`, and `initialize_cutscene` all operate on the inline root at `player + 0x2984`; `initialize_subgoldy` and `update_subgoldy` both reach the live visual object through that root as `presentation.visual_root`, and the embedded cutscene AI sits at `player + 0x42dc`
- port consequence: keep the recovered type lane and docs centered on one inline `PlayerPresentationController`; future Zig or RE naming should stop treating `+0x29a8` as a standalone sibling object

## 2026-03-26 - Player presentation animation lanes

- invalidated claim: the presentation root stores a flat `active_keyframe` at `+0x110`, a flat `queued_animation_count` at `+0x140`, and each weapon lane stores an anim-manager root at `+0x104`
- replacement evidence: `dispatch_cutscene_animation`, `set_weapon_animation`, `initialize_subgoldy`, `initialize_cutscene`, and `set_snail_jetpack` all agree on the same nested model: the root has an inline animation-dispatch block at `player + 0x2a88`, each repeated weapon/jetpack lane has `selected_state` at `+0x104` and an inline animation-dispatch block at `+0x108`, and the shared visual flags live at channel/root offset `+0x04`
- port consequence: keep the checked-in BN/IDA type lane centered on nested `AnimationDispatchState` and repeated `PresentationAnimationChannel` blocks; future Zig or RE naming should stop flattening those lanes into standalone root fields or treating `+0x104` as the anim-manager root inside the weapon channels

## 2026-03-26 - Camera matrix helper prototypes

- invalidated claim: `set_matrix_z_direction`, `look_at_point`, and `linear_interpolate_matrix` return meaningful values
- replacement evidence: the Windows helpers are used as in-place matrix mutators in `update_cameraman` and `update_cutscene`; typing them as returning values produces fake assignments and decompiler noise, while `void` restores clean call sites
- port consequence: keep the checked-in BN/IDA type lane on `void` returns for those helpers and avoid inferring return values from transient register/stack residue in x87-heavy camera callers

## 2026-03-26 - Attachment exit carryover helper

- invalidated claim: `0x43af60` is best described as `initialize_subgoldy_fall_state`
- replacement evidence: the Windows helper only arms the pending post-follow carryover window by copying follow carryover into `post_follow_value_a/b`, clearing `follow_state.active`, setting `attachment_exit_pending`, latching `attachment_exit_anchor_z`, and zeroing progress and gate bytes; it is neither a universal attachment-end helper nor a full airborne fall initializer
- port consequence: rename the tracked symbol and repo narrative around `begin_post_follow_carryover`, and keep actual fall/death state naming separate from attachment-exit carryover in Zig and RE notes

## 2026-03-26 - Selected replay record pointer

- invalidated claim: `game + 0xff25d4` can be treated like the compact on-disk high-score record layout
- replacement evidence: `serialize_compact_high_score_record` and `deserialize_compact_high_score_record` both prove `selected_level_record` points at the expanded in-memory high-score entry, and `update_subgoldy` consumes the expanded replay arrays at `record + 0x70 + i*6` directly
- port consequence: keep the native type lane and docs centered on an expanded `SelectedLevelRecord` with inline `replay_samples`; do not harden any compact-record interpretation into Zig or RE notes

## 2026-03-27 - Presentation tail boundary

- invalidated claim: `PlayerPresentationController` has a standalone `weapon_release_active` byte at `+0x1938`, with `snail_skin_transition` starting at `+0x193c` and `cutscene_ai` at `+0x195c`
- replacement evidence: raw Windows callsites show `initialize_cutscene` passes `presentation + 0x1938` directly to `update_snail_skin_transition` (`0x4428ef: lea ecx, [ebx+0x1938]`), and later passes `presentation + 0x1958` directly to `update_cutscene` (`0x442dec: lea ecx, [ebx+0x1958]`); the old extra byte was a mis-modeled boundary, not a real standalone field
- port consequence: keep `snail_skin_transition` starting at `+0x1938` and `cutscene_ai` at `+0x1958`, and do not reintroduce a fake `weapon_release_active` field ahead of the transition state in BN/IDA headers or docs
