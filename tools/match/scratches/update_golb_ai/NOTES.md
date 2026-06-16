# WIP scratch — 49.63%, 646/700 insns (2026-06-14)

Structure complete and mostly ordered; the 54-insn gap is the original's
staging-local stores (IDA v69-v76: compute into named stack floats, then
store to the destination — same class the collisions golf documents) and
the duplicated early-return epilogues. The frame now matches native at `0x70`
after recovering the homing target/result temporaries, and the prefix reaches
9/700. Next golf pass: transcribe the remaining staging flow per block
(velocity-owner operands in the homing blend, path-output copies, and collision
probes) and let the early returns duplicate.

Latest matching change: the homing blend now stages the pull and keep
components as named source terms before storing the normalized velocity. This
improves the scratch from 21.39% to 21.84% without changing the 637-instruction
candidate count. Trail, smoke, and wall-impact stack temporaries are now typed
`Vec3` locals; that source cleanup emitted the same score on its own. The
unused `Vec3 scratch` local was removed after the full matcher stayed at 21.84%,
637/700 instructions. A
destination-pointer spelling for the `calc_path_length_z` output switch was
tested and rejected because it regressed to 21.04%.

2026-06-13 source-shaping follow-up: the live-state gate is now spelled as a
one-case `switch`, which matches native's `dec state; jne return` entry shape
and improves the scratch from 21.84% to 23.07%. The path-follow output switch
now uses whole-`Vec3` assignment for both the raw position and follow-state
output cases, matching the native copy-through-source/destination-pointer
shape and improving the scratch to 24.23%. The non-follow integration now uses
real `Vec3*` movement/current-position locals before the x/y/z position adds,
improving the scratch to 24.36%, 638/700 instructions.

Direction update follow-up: native stages `output_position - previous_output`
through named stack floats before copying into the live direction vector. The
scratch now spells that as explicit `direction_x/y/z` locals plus output and
direction pointers, improving the scratch from 24.36% to 24.53% and dropping
the candidate from 638 to 637 instructions.

Slug deflection follow-up: BN native zeros `probe.y` before normalizing the
slug deflection vector. The scratch now spells that as `probe.y = 0.0f` before
`normalize_vector(&probe)`, improving the scratch from 24.53% to 24.66%,
638/700 instructions, and confirming slug deflection is horizontal x/z.

Non-follow movement follow-up: the straight-flight gravity lane is now tested
as `kind == 0` before the kind-2 homing branch. This matches the native
`test kind; jne homing/nonzero` layout and improves the scratch from 24.66% to
26.74%, 639/700 instructions, without changing the recovered gravity or homing
semantics.

Matcher padding rebaseline: terminal object-padding normalization removes
untargeted bytes after final `ret` instructions, so the same source now reports
26.90%, 631/700 instructions. This is a measurement correction, not a source
shape change.

Slug dispatch follow-up: native handles slug-contact projectile kinds as
`kind == 1`, then `kind == 2`, then `kind == 0` (`cmp 1`, `cmp 2`, `test 0`).
The scratch now spells that as ordered `if` tests instead of a `switch`,
improving the scratch from 26.90% to 27.05%, 631/700 instructions, while
preserving the recovered slug-hit modes and bounce-arming behavior.

Homing vector follow-up: native carries the homing pull and retained-velocity
terms through real stack vector temporaries before adding them into velocity.
The scratch now spells those as `pull_delta` and `kept_velocity` `Vec3` locals,
improving the scratch from 27.05% to 27.84% and growing the candidate from
631 to 636 instructions without changing the recovered homing formula.

Reflected velocity follow-up: native stages slug deflection through a stack
reflected vector before copying it into velocity. The scratch now spells this
as `reflected_velocity`, improving from 27.84% to 28.10%, 638/700 instructions,
without changing horizontal slug deflection.

Transform dispatch follow-up: the live/source matrices are now typed as
`TransformMatrix`. Native's rocket trail block copies the source transform into
the live matrix with a 16-dword `rep movsd` and calls
`set_matrix_z_direction` / `rotate_matrix_world_z` as matrix member calls.
The typed aggregate copy and member calls improve the scratch from 28.10% to
42.62%, 642/700 instructions. With those owners recovered, re-testing the
trail dispatch as a `switch` ordered `case 2`, `case 1`, `case 0` now recovers
native's `sub`/`dec`/`dec` kind ladder and improves the scratch to 43.48%,
634/700 instructions.

Homing pointer follow-up: native keeps the integrated position pointer live
while computing `homing_target - position`, loading x/y/z through `[pos]`,
`[pos+4]`, and `[pos+8]`. The scratch now spells this through the existing
`current_position` pointer, improving from 43.48% to 43.63%, 634/700
instructions. The remaining homing residual is stack-copy scheduling around
the target delta vector before `normalize_vector`.

Homing stack-vector follow-up: native first computes the target delta into a
temporary stack vector, copies it into the vector passed to `normalize_vector`,
then stages the blended velocity through a result stack vector before assigning
it back to `velocity`. The scratch now spells those as `target_delta` and
`blended_velocity`, improving from 43.63% to 49.63%, 646/700 instructions, and
recovering the native `0x70` frame. Remaining homing residuals are the y/z
velocity owner operands (`[edi+4]`/`[edi+8]` versus direct member offsets) and
the downstream path/collision scheduling.

Tooling cleanup note: `uv run snail match types Game Player PathFollow
TrackRowCell GolbShot Vec3 ResultRecord RunRecord` reports `Player` and
`TrackRowCell` as header-covered candidates, but `Game`, `GolbShot`, and
`Vec3` are still divergent across scratches. After the typed transform pass,
`uv run snail match types TransformMatrix GolbShot Vec3` also reports
`TransformMatrix`, `GolbShot`, and `Vec3` as divergent. Do not consolidate the
gameplay owner/projectile/matrix types yet; keep using scratch-local fields
until more matching islands agree.

2026-06-15 type-header split probe: replacing the tiny local `TrackRowCell`
view with `track_attachment_types.h` kept the headline score at 49.85%, but
added a `Player` class/struct warning and an extra masked operand mismatch
around the late `kill_golb`/grid-cell call region. Keep the compact local
tile-id view until the surrounding owner/vector scheduling is less fragile.

Measured source-shape rejections:

- before the `TransformMatrix` recovery, replacing the `kind` trail dispatch
  with a `switch` regressed from 21.84% to 21.39%;
- direct trail/smoke offset expressions stayed score-neutral at 21.84%, so the
  named half/third/deep locals remain because they document native staging
  without claiming a match win;
- assigning `previous_output = output_position` regressed from 21.84% to
  21.71%.
- re-testing `previous_output = output_position` after the accepted whole-copy
  output switch still regressed slightly, from 24.36% to 24.35%, so keep the
  explicit x/y/z stores there;
- staging the non-follow x integration through a `next_x` local emitted the
  same 24.36% code and was reverted as neutral source churn.
- a label/goto trail dispatch that followed native's zero-then-decrement
  ladder regressed from 24.36% to 24.22% because the surrounding register and
  frame shape moved away from native;
- replacing the accepted direction `direction_x/y/z` locals with a `Vec3`
  delta local regressed from 24.53% to 24.31%;
- copying `previous_output` through the accepted output pointer regressed from
  24.53% to 24.49%, despite shrinking the candidate, so keep the explicit
  field copy from `output_position`.
- staging reflected x/z through `deflected_velocity`/`reflect_x`/`zero_y`
  after the accepted y-zero regressed from 24.66% to 24.40%; that scalar
  spelling was not the native stack-vector shape.
- re-testing trail/smoke offsets as x-direct plus y/z staged locals after the
  27.05% slug-dispatch change emitted identical code, so the symmetric
  `half/third/deep` locals stay as clearer source.
- before the `TransformMatrix` recovery, re-testing the trail/vapour/smoke
  dispatch as a `switch` ordered `case 2`, `case 1`, `case 0` recovered the
  tempting zero/one/two ladder locally but regressed the scratch from 27.05% to
  26.75%. This was superseded by the typed transform pass, where the same
  switch shape is now accepted.
- assigning `velocity = reflected_velocity` for the slug bounce regressed from
  28.10% to 27.72%, so keep explicit field copies.
- reordering reflected velocity to mirror IDA's y/x/z/source schedule regressed
  to 27.84%, so keep x/y/z local staging followed by explicit velocity stores.
- after the accepted homing stack-vector pass, spelling homing velocity through
  either the outer `movement` pointer, a branch-local `live_velocity` pointer,
  or a post-normalize `normalized_velocity` pointer hoisted the velocity owner
  into `ebx` and regressed to 47.61%-47.76%; keep direct `velocity` fields until
  a source-plausible spelling preserves native's `edi` owner.
- 2026-06-16 garbage struct typing retry: rewriting the projectile garbage sweep
  to use the shared `GarbageHazardSlot` fields is semantically consistent with
  the spawner, updater, destroyer, and player-collision scratches, and an
  explicit side-branch spelling raised the headline score slightly from
  `49.85%` to `49.96%`. Reverted anyway because it worsened the masked audit from
  `52 ok, 1 mismatch` to `51 ok, 2 mismatch` and shifted downstream call
  alignment (`kill_golb` vs `get_track_grid_cell_at_world_position`). Keep raw
  garbage offsets here until the surrounding low-score collision/path scheduling
  is less fragile.

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
- homing (kind 2): blend ramps by step to 1.0; target_dir is computed through
  the live current-position pointer, staged through a target-delta copy, and
  blended as `vel = normalize((1 - blend*1.5)*vel + blend*target_dir) *
  old_speed` through a stack result vector; impact when target distance < 0.4;
  dies when speed < 0.1
- path entry: latch z, tile 30 at the cell — AND a second probe one row
  EARLIER (cell - 672 = previous row record, 672 = 244-stride x ... no:
  -672 bytes = the row-cell grid stride math) when vz > 1.0, latching
  z + 1.0 — fast shots pre-enter the next path row
- trail offsets: kind 0 three sprites at out, out - dir*0.3, out -
  dir*0.6; kind 2 copies the 0x40 source transform into the live matrix with
  aggregate assignment/`rep movsd`, then emits two smokes at out and out -
  dir*0.5 + spin wrap 2pi
- bounds band: golb_band_min_z at player+0x2980 <= z <= player z + 46
- slug contact: |dz| < 2.5 && dist < 2.5; native zeroes probe.y, normalizes
  the x/z plane, then deflects velocity to (-speed*nx, 0, -speed*nz); kind 1
  -> hit_slug_hazard(slot, 2), kind 2 -> mode 4, kind 0 -> first contact arms
  the bounce byte, second kills
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
on calc_path_length_z. Spawn-side setup now has a structure-complete
create_golb scratch; use its NOTES for movement-flag spawn semantics.

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
