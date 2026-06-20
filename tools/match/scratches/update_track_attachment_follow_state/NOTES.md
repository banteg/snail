# update_track_attachment_follow_state @ 0x420cb0

Best current source-shaped reconstruction for the native attachment-follow update helper.

Current matcher result:

- 69.38% match
- target: 726 instructions
- candidate: 672 instructions
- exact prefix: 122 instructions
- masked operands: 53 ok, 0 unresolved, 0 mismatch

Recovered shape:

- thiscall `FollowState::update_track_attachment_follow_state(float path_factor, Vec3* out_position, Vec3* motion)`, returns the mode code consumed by `update_subgoldy`
- advances `progress` by `path_factor * secondary_samples[sample_index].delta_length`
- consumes sample overflows until the active sample can hold the remaining delta
- terminates at `sample_index == template->segment_count`, clears `active`, returns `3`, and handles the Supertramp launch special case
- normal path interpolates the path center/lateral/special scalars, builds either kind-42 nonlinear transform or ordinary interpolated secondary-sample transform, stores output position and camera basis scratch vectors, then checks side exits
- special-runtime row updates use the typed row-slot table at `g_game_base + 0x641184 + 0xf4 * row_index`
- Supertramp launch path reloads the subgame rate from `g_game_base + 0x74650`

Known residuals after the current source shape:

- the stack frame now matches exactly at `sub esp, 0x180`; the first mismatch is the destination of the branch at target instruction 122 (`je L240` versus candidate `je L23e`)
- the ordinary and kind-42 transform regions still differ in local stack-slot placement, x87 scheduling, and the amount of duplicated basis-copy code
- the candidate remains 54 instructions shorter, with most of the deficit concentrated after the scalar interpolation prefix
- the side-exit clamp tails use semantic C++ returns but do not reproduce the target's x87 constant-store schedule
- `orientation_b` is intentionally overwritten by the installed-heading lane, matching the native semantic result; some dead/intermediate stores remain layout-only mismatches

## Cross-findings (2026-06-12, second agent)

- the former "camera basis" globals at 0x42fdb4/c4/d4 are the **player's
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

2026-06-16 Player consolidation: the scratch now includes shared `player.h`
instead of carrying a local four-field `Player` slice. The header now carries
the cutscene pitch pair at `+0x2dc/+0x2e0`, `heading_roll +0x370`, and the
full `JetpackGaugeController` at `+0x2750`; the focused match remains
`46.44%`, `678/726`, with `45 ok` masked operands.

2026-06-16 attachment-template slot correction: template `+0x98` is now a
dual view in the shared headers. Follow-state math reads it as
`installed_heading_delta` (`float`), while `begin_post_follow_carryover` copies
the same 32 bits into player+0x430 via `installed_heading_bits`. This corrects
the earlier one-type assumption and keeps this scratch at `46.44%`, `678/726`,
with `45 ok` masked operands.

2026-06-17 cleanup pass: the last-sample orientation branch now names the
`AttachmentSampleMatrixView::rotation_scalar_94/98` fields instead of loading
raw `+0x94/+0x98` floats. Hoisting the sample pointer outside the branch
regressed the pinned shape to `44.99%`, so the source keeps the branch-local
address formation and remains at `46.44%`, `678/726`, with `45 ok` masked
operands.

2026-06-18 vector alias cleanup: the scratch-local x/y/z `Vec3` view now aliases
the shared `Vector3` type. Focused Wibo remains `46.44%`, `678/726`, with
`45 ok` masked operands.

2026-06-18 naming cleanup: the scratch now writes
`g_player_live_matrix_basis_right/up/forward` instead of the stale
`g_camera_basis_*` names. These are still the same game-relative addresses
(`0x42fdb4/0x42fdc4/0x42fdd4`) and should not affect codegen.


## Focused source-shape pass (2026-06-18)

Starting point and final measured result:

- before: `46.44%`, target `726`, candidate `678`, prefix `0`, masks `45/0/0`, frame `0x160`
- after: `69.38%`, target `726`, candidate `672`, prefix `122`, masks `53/0/0`, frame `0x180`
- net improvement: `+22.94` percentage points with no unresolved or mismatched masked operands

Accepted source-shape changes, in measured order:

- introduced real `Vec3` result-stage temporaries for the ordinary rotated offsets and the terminal Supertramp launch position; these recover meaningful stack storage rather than padding
- split template-pointer lifetimes (`initial_template`, runtime/loop reloads, current/orientation/final views), which recovered the exact frame and progressively lengthened the exact prefix
- replaced the cloned/shared overflow construction with one top-tested segment-consumption `while`, retaining a lexical normal-path block and a terminal label so the source remains valid C++ across initialized locals
- kept a real `float* p_delta_length` and updated it after every consumed segment; this made the first 122 target instructions exact
- spelled the special-runtime row lookup for each native store instead of reusing one row pointer, matching the repeated call/store order in both milestone branches
- used direct `primary_samples[index]` expressions for scalar and orientation interpolation instead of hoisting a sample pointer
- recovered the kind-42 helper as a member-shaped call through the attachment template, producing the native `thiscall` setup
- matched the native blend branch polarity and the `z, y, x` zeroing order for the two interpolation matrices
- retained semantic, separate side-exit clamp returns; the simpler source shape matched better than the exact decompiler nesting
- materialized terminal `forward_offset`, `base_position`, and `launch_position` vectors with field assignments, preserving the otherwise-dead aggregate x write naturally
- materialized ordinary-path `path_x`, `path_y`, and `path_z` intermediates, improving x87 scheduling without changing the exact frame

Representative rejected or neutral trials:

- a four-vector ordinary-path rewrite fell to `43.99%` and overgrew the frame to `0x184`
- the first sibling-style top-tested-loop transplant fell to `42.13%`; it was only useful after reconstructing pointer lifetimes and terminal control flow
- exact scalar terminal/Supertramp rewrites collapsed the frame to `0x174` and regressed global alignment
- an aggregate ordinary result vector reached `68.67%` but also collapsed the frame to `0x174`, so the exact-frame `69.38%` shape was retained
- explicit basis-pointer locals intended to prevent branch tail merging increased code size but scored lower (`67.05%` for the strongest variant)
- an active primary-sample pointer in the kind-42 path scored `65.52%`; direct member expressions were better
- the literal IDA-style nested clamp tail scored `67.80%`; three straightforward semantic return paths scored higher
- additional row locals, voice-expression spellings, terminal boolean locals, and several expression reorderings were codegen-neutral

Final verification command:

```sh
tools/match/match.sh \
  tools/match/scratches/update_track_attachment_follow_state \
  --regions --max-regions 14 --region-context 6
```

2026-06-20 follow layout cleanup: the local matrix-backed `FollowState` view now
includes the recovered `+0x3c` flag byte and tail padding, matching the shared
0x40 layout used by `track_attachment_types.h` and `update_subgoldy`. This is
codegen neutral: focused match remains `69.38%`, target `726`, candidate `672`,
prefix `122/726`, masks `53/0/0`.
