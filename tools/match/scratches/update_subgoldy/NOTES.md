# Dossier — scratch not yet written (2091 insns, 8456 bytes — the boss of bosses)

update_subgoldy @ 0x43b120. target.asm committed. Existing analysis:
analysis/runtime/update-subgoldy-attachment-exit-2026-03-15.md, the
five-clear-site narrowing in the checklist, and the harvested motion
plan (gravity @ 0x43c316, integrate @ 0x43bac4, lane predicates).

## Structural index (IDA export line refs)

- ~299: the follow-update mode switch — **case 0 following, cases 1/3
  shared (exit handling), case 2 separate. The boss mirror currently
  returns side_exit_mode == 0 as a bool; the native side exit likely
  returns 1 or 2 keyed on side_exit_mode (calc_path_length_z's sibling
  modes group 0/2 and 1/3). Verify the boss return lane and fix
  FollowUpdateMode before routing.**
- ~414/438: the two swept-entry call sites (primary 0x40 then secondary
  0x80 live-owner bits per the checklist narrowing)
- ~483/576/606 (+1 more): the four begin_post_follow_carryover arms
- the five attachment_exit_pending clear sites (0x43bcb3 slide/floor,
  0x43bf6f grounded snap, 0x43c06d flags re-snap, 0x43c3ea trampoline,
  0x43ce75 jetpack) with the harvested predicates
- gravity velocity_y += -0.01*v_z^2 @ 0x43c316, integrate @ 0x43bac4

## Plan

Too large for a single scratch pass; match it in regions the way the
follow-update went (the mode-switch consumer block first — it validates
the boss return codes — then the exit-lane cluster, then the motion
step). Each region transcribes into the cluster-2 mirror as it pins.
The FollowState/Player/carryover layouts recovered this campaign cover
most of the struct surface already.

## Mode-code question RESOLVED (2026-06-12, boss asm verification)

All three side-exit return paths in update_track_attachment_follow_state
end with `mov ecx, [template+0x40]; test ecx, ecx; sete al` — the
function returns only 0, 1, or 3. update_subgoldy's case 2 for this
switch is dead code (the voice-4 class). A BLOCKED side exit (mode != 0)
returns 0: its side effects happen but the caller treats it as
following. The mirror's FollowUpdateMode is corrected accordingly, and
template+0x40 is confirmed as side_exit_mode.

## Motion core (consumer block read, lines 296-400)

The boss is called as update(velocity.z, &position, &velocity) — follow
advance speed IS the z velocity, and vertical_offset accumulates
velocity.y per tick (closing the loop on the earlier verify finding).

- mode 0 (following): non-DETOUR templates add the acceleration quantum
  `2 * rate^2 * 0.004` to velocity.z, then fall into the shared
  integration; modes 1/3 with still-active follow jump to the re-enter
  lane; mode 2 is dead (verified)
- shared integration (both follow and free): position += velocity;
  drags vz *= (1 - rate*0.003), vy *= (1 - rate*0.003),
  vx *= (1 - rate*0.1); **gravity vy += rate^2 * -0.01 — the harvested
  motion-plan formula's "v_z" is actually the subgame rate**; +/-4
  lateral clamp zeroing vx at the walls
- free flight extras: slide tiles 15/16/18/19 (or damage state 2 +
  slide family) add the acceleration quantum and bump the +0x2738
  threshold float past first_block_row_count; jetpack state 1 adds the
  quantum; the vz drag is GATED on byte +0x1e4 being clear
- byte +0x41c (adjacent to exit_pending +0x41d): one-tick boost lane —
  adds the quantum and clears attachment_exit_pending. DEAD: no producer
  exists in the binary (see the resolved residual below)
- the pending-exit gate checks row-record flag 0x100, jetpack state 0,
  and no control override before the swept probes

This block is the cluster-2 mirror's core; with FollowState, Player,
and the carryover/swept layouts already recovered, the motion-slice
fields (velocity triple, position, the two gate bytes) are now fully
specified for transcription.

## Exit-lane cluster (lines 440-530) — checklist predicates validated + corrected

- grounded snap (0x43bf6f): !follow.active, y in (-0.16333334, 0.49),
  !open-neighbor, tile != 22 -> rotation identity, clear byte +0x1e4,
  squidge when vy < -0.03 (amount vy - 0.03), and only when vy <= 0:
  snap y = 0.49 + zero vy; **pending clears unconditionally in the
  block** (the static predicate over-constrained the clear)
- tile-0/35 carryover arm: fractional z inside (0.2 if flags_3d&1 else
  0, 0.8 if flags_3d&2 else 1.0) and !pending -> begin_post_follow_carryover
- flags re-snap (0x43c06d): (runtime_flags & 0x400) == 0 or global
  byte_4B2F40 & 2, plus y < 0.49 -> squidge(vy), clear +0x1e4, vy = 0,
  clear pending, snap 0.49
- death plane: y < -7.0 and !resurrect_active -> initialize_subgoldy_death
- trampoline (0x43c3ea): while pending, gravity applies; tile 22 with
  |y - (anchor.y + 0.49)| < 0.49 -> squidge(vy), **vy = rate * 0.3 (a
  set, not a velocity flip — corrects the checklist)**, y = anchor.y +
  0.49, clear pending, **byte +0x1e4 = 1** (the trampoline-bounce state
  that skips the vz drag in the motion core), play_sound_effect(41)
- surface_reaction_timer: step-accumulated, resets past 1.0

byte +0x1e4 is now fully decoded: set by trampoline bounce, cleared by
both grounding lanes, gates the vz drag. With this the five-lane spec is
complete and the cluster-2 mirror can be written.

## Zig verify pass (final, 2026-06-12)

stepActivePhaseVerticalMotion verifies CLEAN against the corrected spec:
integration, damping, the grounded-snap band with the unconditional
pending clear (the correction is already applied at block level), the
squidge threshold nesting (observationally equivalent), the void-edge
carryover arm, the death trigger, and the pending-exit trampoline with
rate*0.3. Three named residuals:

1. ~~the +0x41c one-tick boost lane is absent~~ **RESOLVED (2026-06-12):
   the lane is DEAD CODE in the shipped binary.** Exhaustive scan for the
   0x41c displacement across the whole image finds exactly one register
   write (`mov [esi+0x41c], bl` at 0x43aef5 inside initialize_subgoldy's
   reg-zero mass-clear, bl = 0), the imm-0 clear in update_subgoldy, and
   three reads (two boost-lane reads here, one in
   handle_subgoldy_collisions). No absolute references to 0x430198 exist.
   The byte is never set nonzero — vestigial/cut feature; the port
   correctly omits it.
2. native resets the live-matrix rotation to identity in the grounded
   snap; the port only clears the airborne flag (presentation-level)
3. the trampoline envelope uses a shipped-tile floor-height proxy for
   the cell anchor y (the checklist correction stands)
