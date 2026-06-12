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
  adds the quantum and clears attachment_exit_pending
- the pending-exit gate checks row-record flag 0x100, jetpack state 0,
  and no control override before the swept probes

This block is the cluster-2 mirror's core; with FollowState, Player,
and the carryover/swept layouts already recovered, the motion-slice
fields (velocity triple, position, the two gate bytes) are now fully
specified for transcription.
