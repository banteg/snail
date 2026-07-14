# update_track_attachment_follow_state @ 0x420cb0

Best current source-shaped reconstruction for the native attachment-follow update helper.

Current matcher result:

- 72.89% match
- target: 726 instructions
- candidate: 698 instructions
- exact prefix: 122 instructions
- masked operands: 63 ok, 0 unresolved, 0 mismatch

Recovered shape:

- thiscall `FollowState::update_track_attachment_follow_state(float path_factor, Vec3* out_position, Vec3* motion)`, returns the mode code consumed by `update_subgoldy`
- advances `progress` by `path_factor * secondary_samples[sample_index].delta_length`
- consumes sample overflows until the active sample can hold the remaining delta
- terminates at `sample_index == template->segment_count`, clears `active`, returns `3`, and handles the Supertramp launch special case
- normal path interpolates the path center/lateral/special scalars, builds either kind-42 nonlinear transform or ordinary interpolated secondary-sample transform, stores output position and publishes the basis rows into `GameRoot::subgame.player.transform`, then checks side exits
- special-runtime row updates traverse `GameRoot::subgame.runtime_rows[row_index].primary_attachment_cell`
- Supertramp launch path reloads `GameRoot::subgame.subgame_rate`

Known residuals after the current source shape:

- the stack frame now matches exactly at `sub esp, 0x180`; the first mismatch is the destination of the branch at target instruction 122 (`je L240` versus candidate `je L23e`)
- the ordinary and kind-42 transform regions still differ in local stack-slot placement, x87 scheduling, and the amount of duplicated basis-copy code
- the candidate remains 28 instructions shorter, with most of the deficit concentrated after the scalar interpolation prefix
- the side-exit clamp tails use semantic C++ returns but do not reproduce the target's x87 constant-store schedule
- `orientation_b` is intentionally overwritten by the installed-heading lane, matching the native semantic result; some dead/intermediate stores remain layout-only mismatches

## Cross-findings (2026-06-12, second agent)

- the former "camera basis" globals at 0x42fdb4/c4/d4 are the **player's
  live_matrix rows**: player block at game+0x42fd7c, TransformMatrix at
  +0x38, position row = the position vector at +0x68 — same shape as the
  hazard slots. Worth folding into the mirror's Player model even though
  the normalized addressing is identical either way.
- FollowState `+0x18/+0x1c` holds the two scalar orientation lanes,
  `+0x20..+0x28` is the `orientation_up` vector, and `+0x2c..+0x34` is
  `output_position`; the swept entry zeroes the two scalar lanes.
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
this scratch's helper declaration as a `Path` member still regressed
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
The authored `SubHover` view now uses shared `sub_hover.h`. This scratch
only reads `player->sub_hover.state` at +0x0c, and the shared full-size
view keeps the pinned 46.44%/678-insn result.

2026-06-16 Player consolidation: the scratch now includes shared `player.h`
instead of carrying a local four-field `Player` slice. The header now carries
the cutscene pitch pair at `+0x2dc/+0x2e0`, `heading_roll +0x370`, and the
full `SubHover` at `+0x2750`; the focused match remains
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

2026-06-20 matrix-view naming cleanup: the source now names the local owner
`AttachmentFollowStateMatrixView` and the kind-42 member-call cast
`PathKind42CallView`. Including `track_attachment_types.h`
directly is rejected here because it defines the full shared `FollowState`,
while this scratch still needs a matrix-backed template/sample view for its
current 0x180-frame codegen. The rename is codegen neutral at `69.38%`,
`672/726`, `122/726` prefix, and `53/0/0` masks, and
`uv run snail match types Path --paths` /
`uv run snail match types FollowState --paths` now report no consolidation
candidates.

## 2026-07-10 entry-mesh transition ownership

The old local `AttachmentFollowRuntimeRow` / scalar overlay was misleading.
`g_game_base +0x641184 + row*0xf4` is a field-first view of
`TrackAttachmentRuntimeRow::primary_attachment_cell` at subgame row `+0xa4`.
The pointed object is a `TrackRowCell`, so its `+0x24` and `+0x34` writes are
`BodBase.object` and `tColour.a`, not anonymous runtime scalars.

For templates with `has_entry_mesh_transition` (`+0x9c`):

- sample `(3 * count) / 7` sets the entry cell's list flag `0x80`, installs
  `template->entry_transition_strip_mesh` (`+0xa0`), and sets alpha `0.6`;
- sample `count - 1` restores `template->entry_base_strip_mesh` (`+0xa4`) and
  alpha `1.0`.

World init supplies those pointers from an auxiliary pair and the public pair
respectively. Replacing the local fake overlay with the shared owner types is
codegen neutral: focused matching remains `69.38%`, `672/726`, prefix
`122/726`, masks `53/0/0`.

## 2026-07-13 aggregate ownership recovery

Windows and iOS now agree on two aggregate owners that the scratch previously
spelled as scalar copies:

- the three game-relative stores at `0x42fdb4`, `0x42fdc4`, and `0x42fdd4`
  publish the interpolated matrix's right, up, and forward `Vec3` rows into the
  embedded Player live matrix;
- `FollowState +0x20..+0x28` is one owned `orientation_up` vector copied from
  that interpolated matrix's up basis, not three unrelated orientation floats.

The iOS `cRPathFollowGoldy::Traverse(float, tVector&, tVector*)` body preserves
both aggregate copies with `ldm/stm`, independently confirming the source
shape. It also preserves the same `sample_index == segment_count * 2` voice-4
guard before terminating at `sample_index == segment_count`, proving that lane
is cross-platform dead code rather than an unresolved counter alias.

Using real `Vec3` assignments for the published Player matrix rows and the
side-exit output copy improves the focused Windows candidate from `69.38%`,
`672/726` to `70.28%`, `694/726`, with the exact `122/726` prefix retained and
`51/0/0` masked operands. The local `orientation_up` field remains component-
assigned because a single aggregate expression perturbs unrelated VC6 register
allocation and regresses to `67.19%`; the shared layout still records the real
vector owner, with no padding, volatile qualifier, or synthetic scheduling aid.

## 2026-07-14 canonical follow ownership

The updater now defines the shared `FollowState` method directly. Its borrowed
`Path*` and `SubLoc*`, plus the path-owned `AttachmentSample` banks, replace the
old `AttachmentFollowStateMatrixView`, `PathMatrixView`,
`TrackRowCellAnchorView`, `AttachmentSampleMatrixView`, and
`PathKind42CallView`. The kind-42 call now goes through canonical `Path`.

The three now-unused private view headers and the final field-first runtime-row
slot were removed. Entry-mesh milestone writes now traverse
`GameRoot::subgame.runtime_rows[row].primary_attachment_cell` directly.

This consolidation is codegen neutral: focused matching remains `70.28%`,
`694/726`, with the exact `122/726` prefix and `51/0/0` masked operands.

## 2026-07-14 canonical root publication

Both traversal branches now publish the interpolated right, up, and forward
rows through `GameRoot::subgame.player.transform`. The former three
field-first matrix-row globals described the same storage but obscured the
complete root, subgame, player, and transform ownership chain. The two
entry-mesh milestones use the same canonical root to reach the owned `SubRow`
array and its borrowed primary attachment cell.

The direct owner spelling improves the focused candidate from `70.28%`,
`694/726`, `51/0/0` masks to `72.89%`, `698/726`, with the exact `122/726`
prefix retained and `63/0/0` masked operands. No volatile or scheduling-only
source was introduced.

## 2026-07-14 source-cell base closure

The borrowed `SubLoc*` now exposes inherited `BodBase::position` and list flags
directly. Entry-mesh milestone writes therefore reach the primary attachment
cell's inherited `BodNode` without a synthetic embedded `bod` owner. Focused
output is byte-stable at 72.89%, 698/726 instructions, with the 122-instruction
prefix and all 63 operands clean.

## 2026-07-14 matrix-owner follow-up

The endpoint blend and ordinary terminal branch now invoke
`TransformMatrix::set_matrix_identity()` on their owned local matrices. This
removes the scratch-local free-function declaration and keeps the focused
candidate byte-identical at `72.89%`, `698/726`, prefix `122/726`, with
`63/0/0` masked operands.

The sibling Golb traversal's sample-bank reload does not transfer to this
larger Goldy traversal: removing the branch-local `secondary` owner shrinks the
native-sized `0x180` frame to `0x17c`, loses the full prefix, and regresses to
`68.87%`. A four-vector ordinary result chain grows the frame to `0x18c` and
regresses to `63.66%`; spelling either rotated contribution through the inline
vector multiply operator scores `72.61%`. Those shapes were rejected rather
than retained as scheduling aids.

## 2026-07-14 root declaration closure

The entry-mesh milestones, published player transform, and terminal subgame
rate now all begin from the canonical `GameRoot*` declaration rather than a
byte pointer repeatedly cast at each use. This closes the shared process-root
edge without changing code generation: focused matching remains 72.89%,
698/726 instructions, with the 122-instruction prefix and all 63 operands
clean.

## 2026-07-14 hover lifecycle ownership

Attachment-side lateral handling now tests the typed active hover state. Live
field xrefs prove this is a direct consumer of `SubHover +0x0c`, not an
attachment-owned flag. Focused output remains byte-identical at 72.89%,
698/726 instructions, prefix 122/726, with all 63 operands clean.
