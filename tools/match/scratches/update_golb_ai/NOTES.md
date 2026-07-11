# WIP scratch — 73.34%, 645/694 insns (2026-06-21)

## 2026-07-10 slug-pool owner closure

The promoted `SubgameRuntime::slug_hazards` pool now supplies the exact
`0xec`-byte `SlugHazardRuntime` and its `hit_slug_hazard` method, so the old
method-only local class view is removed. This resolves the shared-header
redefinition without changing code shape: focused Wibo remains 73.34%,
645/694, prefix 9/694, with all 68 masked operands clean.

## 2026-06-21 GolbShot header consolidation

The local `GolbShot` and `PathFollow` field slices are now promoted into
`include/golb.h`. The shared projectile layout keeps the existing exact-helper
names (`primary_body`, `secondary_body`, `tertiary_body`, `render_body_owner`,
`object_ref`, `owner_player`) and adds the update-only overlays for the
vapour/live-matrix lane at `+0x80..+0x190`, homing state at `+0x198..+0x1bf`,
`owner_body`/`player` aliases, the source matrix at `+0x27c`, path-follow state
at `+0x2bc`, and the path-entry z latch at `+0x2e4`.

Focused Wibo for this scratch stays pinned at `73.34%`, target `694`,
candidate `645`, prefix `9/694`, with `68 ok, 0 unresolved, 0 mismatch`.
Exact Golb helper sentinels (`initialize_golb_shot`, `kill_golb`,
`spawn_golb_trail_sprite`, `initialize_path_follow_golb`) remain exact, and the
documented partial Golb consumers (`spawn_golb_smoke`,
`spawn_golb_impact_sprite`, `calc_path_length_z`) keep their dashboard
baselines. `uv run snail match types --paths` now reports only the remaining
`Player` header-compatible row.

## 2026-06-21 subgame owner cleanup

The retained cleanup removes this scratch's generic `Game` owner shell. Shared
`SubgameRuntime` now exposes the garbage hazard pool at `+0x359140`, so the
two garbage scans read `game->garbage_hazards.active_head` instead of the local
`garbage_list_head` placeholder. `GolbShot::game` is now the same
`SubgameRuntime*` owner used by the promoted header.

Focused Wibo stays pinned at `73.34%`, target `694`, candidate `645`, prefix
`9/694`, with `68 ok, 0 unresolved, 0 mismatch`. The exact Golb helper users
that include `golb.h` stayed exact, and the known partial consumers kept their
dashboard baselines. `uv run snail match types --paths` now reports
no `Game` row, with this scratch removed from the remaining
generic owner list.

## 2026-06-20 trail-offset vector follow-up

The retained follow-up improves from `72.67%`, target `694`, candidate `627`,
prefix `9/694`, with `67 ok, 0 unresolved, 0 mismatch`, to `73.34%`, target
`694`, candidate `645`, prefix `9/694`, with a clean masked audit of `68 ok,
0 unresolved, 0 mismatch`.

Accepted source-shape changes:

- the rocket smoke offset is now staged as a `Vec3 half_offset` before building
  `smoke_position`;
- the kind-0 trail offsets are now staged as separate `Vec3 third_offset` and
  `Vec3 deep_offset` locals before building the second and third trail sprites.

This keeps the recovered formulas unchanged, but gives VC6 real stack-vector
temporaries around the native `out - direction * scale` lanes.

Rejected splits: only vectorizing the first kind-0 trail offset reached
`72.95%`, `633/694`, with `67 ok`; only vectorizing the second kind-0 trail
offset reached `72.80%`, `633/694`, with `68 ok`; reusing a single offset
vector for both kind-0 trails regressed to `69.92%` by shifting earlier homing
stack locals. The small `spawn_golb_smoke` and `spawn_golb_impact_sprite`
helpers were also rechecked first and remain pinned at their documented
residuals.

## 2026-06-20 kind-0 vector-copy follow-up

The retained follow-up improves from `69.45%`, target `694`, candidate `625`,
prefix `9/694`, with `69 ok, 0 unresolved, 0 mismatch`, to `72.67%`, target
`694`, candidate `627`, prefix `9/694`, with a clean masked audit of `67 ok,
0 unresolved, 0 mismatch`.

Accepted source-shape changes:

- the kind-0 owner-body position write is now a `Vec3` aggregate copy into the
  row at `owner_body + 72`, matching native's pointer-shaped three-dword copy;
- the late `previous_output` refresh is now a `Vec3` aggregate assignment from
  `source_matrix.position`. Earlier aggregate-copy attempts regressed before the
  kind-0 body-position copy recovered the surrounding owner schedule.

Rejected follow-up: routing the whole kind-0 trail block through a named
`output_position` pointer was score-neutral at `72.67%`, `627/694`, with the
same masked audit, so it was reverted as churn.

## 2026-06-20 effects/member follow-up

The retained follow-up reports `69.45%`, target `694`, candidate `625`, prefix
`9/694`, with a clean masked audit of `69 ok, 0 unresolved, 0 mismatch`.

Accepted source-shape changes after the collision-lane baseline:

- `Game::get_track_grid_cell_at_world_position` is now modeled as a member
  call at both track-cell probes, matching the existing helper scratch and
  recovered callsites.
- The kind-1 vapour trail emission calls
  `VapourTrail::add_vapour_point(&source_matrix)`, matching the already
  promoted `VapourTrail` thiscall helper.
- The homing y/z retained-velocity and final rescale lanes stay on the live
  movement pointer, while the post-homing output copy remains one semantic
  `Vec3` assignment.
- The path-follow raw-position output case now uses named source/destination
  `Vec3*` pointers for the aggregate copy. This improves the follow-up from
  `69.29%` to `69.45%` without changing candidate size or the masked audit.
- The garbage-hit scheduler keeps the clean fallthrough ordering from the
  collision-lane pass.

Rejected follow-ups: scalar field stores for the raw-position output copy
regressed to `59.89%` and introduced two masked mismatches; swapping the
source/destination pointer declaration order for the accepted aggregate copy
was codegen-neutral.

## 2026-06-20 accepted collision-lane pass

The packaged baseline was `49.85%`, target `694`, candidate `646`, prefix
`9/694`, with masked operands `52 ok, 0 unresolved, 1 mismatch`. The accepted
source shape now reports `57.21%`, target `694`, candidate `631`, prefix
`9/694`, with a clean masked audit of `57 ok, 0 unresolved, 0 mismatch`.

Three coupled source-level corrections produced the clean gain:

- model `Player::add_subgoldy_score` and `SlugHazardRuntime::hit_slug_hazard`
  as member calls, recovering their `thiscall` ownership;
- keep the already-existing `new_output` pointer as the shot-position owner
  through garbage, slug, splash, and wall probes;
- spell the garbage scan as a sentinel loop, route its null exit through the
  slug scan, and keep the garbage-hit impact/splash path as the fall-through
  return before the labelled wall probe.

The strongest dirty trial reached `60.73%`, `630/694`, but retained two masked
call mismatches, so it was rejected. Declaring the track-grid lookup as a
member call also remained rejected: on the accepted control-flow shape it
reached `59.09%`, `626/694`, but introduced one masked mismatch. No shared
header was changed.

Next region: homing blend target `[158:211]` (native approximately
`0x414a45`–`0x414aa3`), especially the retained y/z velocity-owner operands and
rescale stores. Earlier branch-local or outer movement-pointer spellings
hoisted the owner into the wrong register and regressed to `47.61%`–`47.76%`,
so another attempt needs stronger source-shape evidence.

## Earlier source-shaping history

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

Historical tooling cleanup note: earlier `uv run snail match types Game Player
PathFollow TrackRowCell GolbShot Vec3 ResultRecord RunRecord` passes reported
`Game`, `GolbShot`, and `Vec3` as divergent across scratches. The
TransformMatrix piece is superseded by the 2026-06-18 consolidation below, and
the GolbShot method-surface conflict is superseded by the 2026-06-20
create-dispatch split below; keep the broader gameplay owner and vector views
scratch-local until more matching islands agree.

2026-06-18 TransformMatrix consolidation: the scratch now uses shared
`transform_matrix.h` instead of its local 0x40 matrix view. Focused Wibo stays
`49.85%`, `646/694`, with `52 ok, 1 mismatch`; the broader `GolbShot`,
`Game`, and `Vec3` owner views remain scratch-local.

2026-06-15 type-header split probe: replacing the tiny local `TrackRowCell`
view with `track_attachment_types.h` kept the headline score at 49.85%, but
added a `Player` class/struct warning and an extra masked operand mismatch
around the late `kill_golb`/grid-cell call region. Keep the compact local
tile-id view until the surrounding owner/vector scheduling is less fragile.

2026-06-20 tile-view naming cleanup: the compact local row-cell view is now
`GolbTrackRowCellTileView`, making it explicit that this scratch only needs the
`tile_id +0x3c` byte and should not be promoted to the full shared
`TrackRowCell` header yet. Focused evidence stayed unchanged at `49.85%`,
`646/694`, `9/694` prefix, and the existing `52 ok / 1` masked call mismatch;
`uv run snail match types TrackRowCell --paths` now reports no consolidation
candidates.

2026-06-20 GolbShot header compatibility: `create_golb` now consumes
`include/golb.h` and moves its slot-0 virtual callback spelling into a separate
local primary-body view. `uv run snail match types GolbShot --paths` now reports
the remaining `update_golb_ai` local slice as header-compatible with
`golb.h`. This scratch intentionally keeps its local `GolbShot` fields because
the current residuals are source scheduling and owner-register issues inside
the large update body.

2026-06-20 Player header consolidation: this scratch now consumes shared
`player.h` for `add_subgoldy_score`, `position.z`, and `interaction_max_z`.
Focused Wibo stays at `73.34%`, `645/694`, `68 ok / 0`; the large local
`GolbShot` and `Game` owners remain scratch-local for the scheduling reasons
above.

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

2026-06-18 vector alias cleanup: the scratch-local x/y/z `Vec3` view now aliases
the shared `Vector3` type. Focused Wibo remains `49.85%`, `646/694`, with
`52 ok` masked operands and the known target-call mismatch.

2026-06-20 trail helper ABI cleanup: the local `GolbShot` view now declares
`spawn_golb_trail_sprite` with its allocator-shaped `Sprite*` return, matching
`golb.h` and the helper decompiler. Focused Wibo remains `49.85%`, `646/694`;
all update callsites ignore the return. A broader attempt to clear the
`GolbShot` type row by making `create_dispatch` nonvirtual was rejected:
`create_golb`'s native tail is a real `(**vtable)(this)` dispatch through
`*this`.

## 2026-07-11 cRSlug target ownership

The two projectile-impact arms now call `Slug::hit_slug_hazard` through the
primary authored type, matching Android/iOS `cRSlug::Hit(int)` and the exact
Windows hit helper. The raw pool address arithmetic remains deliberate because
it preserves this large function's current register allocation. Focused Wibo
is byte-stable at 73.34%, 645/694 instructions, with 68 clean masked operands
and no unresolved or mismatched operands.
