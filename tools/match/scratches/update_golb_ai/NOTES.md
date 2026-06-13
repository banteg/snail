# WIP scratch — 20.79%, 637/700 insns (2026-06-13)

Structure complete and ordered; the 63-insn gap is the original's
staging-local stores (IDA v69-v76: compute into named stack floats, then
store to the destination — same class the collisions golf documents) and
the duplicated early-return epilogues. Next golf pass: transcribe the
staging flow per block (trail/smoke offsets, direction update, slug
deflection) and let the early returns duplicate.

Recovered this pass (full field map in scratch.cpp):

- GolbShot layout: live matrix +0x150; homing target/blend +0x198-0x1b0;
  spin pair +0x1b4; skip byte +0x1bc; bounce byte +0x1bd; kind +0x1c0
  (0 golb, 1 lazer/vapour, 2 rocket); position +0x1f4; previous output
  +0x234; state +0x244; owner body +0x248 (position row written at +72);
  velocity +0x24c; direction +0x258; path factor +0x264; lifetime pair
  +0x268; game +0x270; player +0x278; source transform +0x27c whose
  POSITION ROW is the output position at +0x2ac (one matrix, two views —
  the 0x40 qmemcpy to the live matrix spans both); path-follow object
  +0x2bc with output at +0x18; path-entry z latch +0x2e4
- golb (kind 0) gravity: vy -= subgame_rate * 0.017 while y outside
  [0, 0.49]; vy = 0 inside the band
- homing (kind 2): blend ramps by step to 1.0; vel = normalize((1 -
  blend*1.5)*vel + blend*target_dir) * old_speed; impact when target
  distance < 0.4; dies when speed < 0.1
- path entry: latch z, tile 30 at the cell — AND a second probe one row
  EARLIER (cell - 672 = previous row record, 672 = 244-stride x ... no:
  -672 bytes = the row-cell grid stride math) when vz > 1.0, latching
  z + 1.0 — fast shots pre-enter the next path row
- trail offsets: kind 0 three sprites at out, out - dir*0.3, out -
  dir*0.6; kind 2 two smokes at out and out - dir*0.5 + spin wrap 2pi
- bounds band: golb_band_min_z at player+0x2980 <= z <= player z + 46
- slug contact: |dz| < 2.5 && dist < 2.5; velocity deflects to
  (-speed*nx, 0, -speed*nz); kind 1 -> hit_slug_hazard(slot, 2), kind 2
  -> mode 4, kind 0 -> first contact arms the bounce byte, second kills
- garbage gate: |dz| < 3 && dist < radius(+156) + 0.49; kind 2 splash
  re-sweeps the list at radius 3.0
- wall tile 14: impact sprite at z - 1.0 then retire

# Dossier — scratch not yet written (700 insns, 2656 bytes)

update_golb_ai @ 0x414820. target.asm committed. Focus: the path-follow
lane the Zig port lacks (checklist Phase 4 item).

## Path-follow entry (IDA export lines ~180-198)

When the shot's local y (+504) is in (0,1) and it advances past its
stored z: grid-cell lookup at the shot position (+684 vec); if the
cell tile == 30 (0x1e), stash position.z into the anchor slot (+740)
and call the matched initialize_path_follow_golb(state at +700, cell,
position vec at +500, this). A second entry lane checks +596 > 1.0 with
the adjacent row's cell (cell - 612 bytes) and seeds anchor z+1 via
cell - 672. **Naming correction for the matched init scratch: the third
int arg is the owner golb pointer (returned through eax), not a search
slot id.**

## Trail dispatch by state (+448)

- 0: trail sprites at position, position - 0.3*velocity, - 0.6*velocity
- 1: add_vapour_point from the live matrix
- 2 (rocket?): live-matrix copy, spin accumulate +0x1b4 with the 2pi
  wrap, golb smoke at position and position - 0.5*velocity

Velocity triple at +600/604/608, position at +684/688/692, live matrix
at +636 (0x40 copy), path-follow state at +700 (the matched
GolbPathFollowState layout), owner game ptr at +624.

## Zig gap

The port has the level band + gravity + despawn (checklist) but not the
tile-30 path-follow entry, the per-state trail dispatch offsets, or the
adjacent-row second entry. The matched search_path_for_golb (100%) and
initialize_path_follow_golb (100%) make the mirror transcription of the
entry lane mechanical once the in-follow stepping region of this
function is read (next session).

## In-follow stepping + rocket homing (lines 94-175)

- following (state byte +700 == 1): `calc_path_length_z(state, step
  scalar +612, position +500, velocity +588)` rides the path and returns
  a mode: 0/2 -> position adopts the state's output vector (+724/728/732
  — the GolbPathFollowState shares the FollowState output_position
  layout, sibling types confirmed); 1/3 -> keep the raw integrated
  position. calc_path_length_z now has a structure-complete scratch; use
  its NOTES for path-follow residuals.
- not following: position += velocity, then per state:
  - 0 (laser): outside the y band [0, 0.49], vy -= subgame_rate * 0.017
    (the lane the port already has)
  - 2 (rocket) with a live target (+408): homing — blend (+428)
    accumulates by step (+432) capped 1.0; impact sprite + despawn when
    distance to target < 0.4; velocity = renormalize(blend*to_target +
    (1 - 1.5*blend)*velocity) rescaled to the old speed; despawn when
    speed < 0.1. This is the checklist's "rocket homing lane".
- exit: the follow byte clears at line ~368 (read the surrounding block
  for the exit conditions next).

Mirror plan: entry + homing + trails are transcribable now; riding waits
on calc_path_length_z.

## calc_path_length_z @ 0x4217b0 (read 2026-06-12)

It is a sibling of update_track_attachment_follow_state: identical
advance structure (step = factor * delta_length, segment-fit check,
center/scale/angle lerps with the terminal-sample special case, kind-42
compute vs general matrix lerp with zeroed position rows through
linear_interpolate_matrix), operating on the golb path state whose
relative layout equals FollowState (template +0x4, sample_index +0xc,
progress +0x10, vertical +0x14, output +0x18). The mode codes 0-3 it
returns are what update_golb_ai switches on. The original clearly
stamped one template-follow routine into both call sites — a future
scratch should be derived from the boss scratch's source, and any boss
golf wins transfer here. For the Zig mirror, the existing
updateTrackAttachmentFollowState transcription covers this function's
semantics modulo the state struct binding.
