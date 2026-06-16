# update_track_attachment_follow_state @ 0x420cb0

Best current source-shaped baseline for the native attachment-follow update helper.

Current matcher result:

- 46.44% match
- target: 726 instructions
- candidate: 678 instructions

Recovered shape:

- thiscall `FollowState::update_track_attachment_follow_state(float path_factor, Vec3* out_position, Vec3* motion)`, returns the mode code consumed by `update_subgoldy`
- advances `progress` by `path_factor * secondary_samples[sample_index].delta_length`
- consumes sample overflows until the active sample can hold the remaining delta
- terminates at `sample_index == template->segment_count`, clears `active`, returns `3`, and handles the Supertramp launch special case
- normal path interpolates the path center/lateral/special scalars, builds either kind-42 nonlinear transform or ordinary interpolated secondary-sample transform, stores output position and camera basis scratch vectors, then checks side exits
- special-runtime row updates use the typed row-slot table at `g_game_base + 0x641184 + 0xf4 * row_index`
- Supertramp launch path reloads the subgame rate from `g_game_base + 0x74650`

Known residuals after the current source shape:

- stack layout still differs (`sub esp, 0x180` target vs `sub esp, 0x160` candidate)
- the overflow loop still uses a different x87 subtract shape and keeps the template record in `ebx` instead of freeing `ebx` for the `0x80` row flag constant
- special-runtime row writes are semantically typed, but row lookup/store ordering and registers still differ in both milestone branches
- normal interpolation now follows the target's scalar and output temporary flow, but matrix-copy stack offsets and camera-basis stores remain different
- `orientation_b` is intentionally overwritten by the installed-heading lane, matching the native semantic result; exact dead/intermediate stores still need source-shape work

## Cross-findings (2026-06-12, second agent)

- the "camera basis" globals at 0x42fdb4/c4/d4 are the **player's
  live_matrix rows**: player block at game+0x42fd7c, TransformMatrix at
  +0x38, position row = the position vector at +0x68 — same shape as the
  hazard slots. Worth folding into the mirror's Player model even though
  the normalized addressing is identical either way.
- FollowState +0x18..+0x20 is output_position (the swept entry zeroes
  its x/y), orientation block spans +0x24..+0x34;
  tools/match/include/track_attachment.h updated.
- sample +0x8c renamed delta_length across the headers (the swept-entry
  "depth limit" gate is z < segment length); swept scratch updated, score
  holds at 79.80%.
- target preloads ebx=0x80 and edi=0x3f19999a (0.6f) in the prologue —
  loop-invariant constant hoisting; the candidate can only mirror it once
  those callee-saved registers are free across the overflow loop.

## Iteration findings (loop session, 2026-06-12)

- overflow subtract now matches via the one-expression shape
  (`delta -= len - progress` before the index bump): 42.77%, 644 insns.
- **template+0x58 confirmed as the primary_samples pointer** (the
  loop-exit advance clone reads `[edx+0x58]` then `[ecx+0x90]`);
  +0x5c is secondary_samples. Fold into the struct map.
- **the 47-insn deficit in hunk -107,129: the target DUPLICATES the
  advance-block head at the loop exit** (re-evaluates fits-check, stores
  progress via an int temp through [esp+0x14], clones the v85 lerp setup
  reading primary_samples) instead of jumping to the shared block. The
  candidate's `goto`-style shared advance block must be restructured so
  the loop-exit path carries its own copy of the advance prologue —
  likely literal duplicated source in the original (or a macro).
- milestone-store region: target re-runs the full row lookup (including
  the get_track_cell_row_index call) per store, and one store reads
  `[esi+0xa0]` where the register context suggests the template, not the
  attached record — re-verify the +0x24 source field during the
  restructure.
- advance-block duplication landed via cross-jump gotos (loop fits-exit
  carries its own prologue + last-segment v85 case, jumping into the
  shared else-lerp / after-v85 labels): 42.77% -> 47.39%, 654 insns.
  Remaining structural deficit is now concentrated in the kind-42 /
  general matrix-copy regions and the tail.
- clone now survives cross-jump merging (distinct `advanced` temp + fully
  duplicated v85 computation): 678/726 insns. Score 46.44% is alignment
  noise below the 47.39 peak; instruction count is the truer metric here.
- next: the 3*count/7 milestone-store region — target orders it
  [flags lookup+store] [attached fetch] [+0x24 lookup+store reading
  attached from esi] [+0x34 lookup+store of 0.6f]; candidate emits the
  +0x24 pair earlier and drops one lookup. Re-order the source statements
  to the IDA sequence and keep `attached` live across the +0x24 lookup.

## Pinned (2026-06-12): semantics complete, golf parked at 46.4%/678 insns

All lanes are source-shaped and cross-validated (IDA export, target.asm,
and the matched neighbors): progress/overflow stepping, dead voice-4
lane, both milestone writes, kind-42 + general interpolation, orientation
block with the dead-b lerp, side-exit gates, supertramp exhaust. The
remaining diff is clone PLACEMENT (compiler block ordering puts our
loop-exit clone at the function tail instead of between loop and
exhaust), register assignment (attached record in esi, template in esi
vs ebx), and x87 scheduling in the matrix regions — layout-only classes
per the established precedents. Per campaign rules this qualifies as
pinned: the FollowState contract is fully recovered and the mirror
transcription can proceed. Golf leads for a future polish pass are in
the iteration notes above.

## Tooling recheck (2026-06-13)

Native loads `ecx = template_record` immediately before the kind-42 transform
helper call, matching the member-call evidence seen in
`project_position_onto_track_attachment` and `calc_path_length_z`. Rewriting
this scratch's helper declaration as a `PathTemplate` member still regressed
the focused match from 46.44% to 44.87%, mostly by perturbing the already
fragile stack/layout alignment. Treat the convention evidence as a future
shared-type consolidation lead, not a bulk scratch rewrite.

2026-06-15 type consolidation: the sample view is now named
`AttachmentSampleMatrixView`, matching `calc_path_length_z`. The fields align
with the shared `AttachmentSample` layout; the local view remains only because
this scratch needs a `TransformMatrix`-typed transform for interpolation and
the shared attachment header still uses `AttachmentTransform`.

2026-06-16 header correction: `FollowState::update_track_attachment_follow_state`
now returns `int` in `track_attachment_types.h`. The previous `void`
declaration was invalid; both this scratch and `update_subgoldy` consume the
mode result.

2026-06-16 type consolidation: the former local state-only
`JetpackGaugeController` view now uses shared `jetpack_gauge.h`. This scratch
only reads `player->jetpack_gauge.state` at +0x0c, and the shared full-size
view keeps the pinned 46.44%/678-insn result.
