# calc_path_length_z

## 2026-07-14 Traverse vector-expression recovery

The independent Android `cRPathFollowGolb::Traverse(float, tVector*,
tVector*)` body and Windows native stack schedule close the ordinary-path
source shape. The secondary sample bank is reloaded through its owning `Path`
when the next matrix is copied instead of being hoisted across the whole
branch. The lateral contribution is the shared `Vector3` expression
`basis_right * local_x`, added to the anchored path base and copied as one
result vector. Output pointers now begin inside the kind-specific branches,
and the terminal side-exit mirror is the same aggregate `Vector3` transfer as
the overflow exit.

Together these changes restore the native 0xf4-byte frame and 32-instruction
prefix, raise focused matching from 55.52% (400/425) to 71.82% (416/425), and
keep all seven masked operands clean. The recovered `Path` and
`TransformMatrix` calls also use their shared member surfaces directly.

Measured rejected neighbors are kept out: retaining the hoisted secondary
bank left a 0xf8 frame and reached only 55.62%; scalar ordinary output stores
with the direct bank reload reached 61.56% but lost the native aggregate-copy
shape; and rebuilding the terminal supertramp calculation from extra named
vectors overgrew the candidate to 442 instructions and regressed to 57.21%.

## 2026-07-13 flight-transform ownership closure

The three formerly separate basis scratch vectors and raw shot position are
the four vector rows of one `TransformMatrix` at `GolbShot +0x1c4`: basis rows
land at `+0x1c4/+0x1d4/+0x1e4`, and the position row lands at `+0x1f4`.
`create_golb` independently passes that exact base to
`Vapour::add_vapour_point`, while this function populates the basis and
position rows during path traversal. The adjacent matrix-shaped owner at
`+0x204` retains the prior rendered position at its `+0x30` row. Focused
matching is byte-for-byte unchanged at 55.52% (400/425 instructions, 7 clean
masked operands).

calc_path_length_z @ 0x4217b0 advances the Golb projectile path-follow state
used by `update_golb_ai`.

Recovered semantics covered by this scratch:

- state layout follows the exact initializer at 0x421770: `+0x04` is the
  attachment template, `+0x08` is the source cell, `+0x0c` is sample index,
  `+0x10` is progress, `+0x14` is vertical offset, `+0x18..+0x20` is the
  output position, and `+0x24` is the Golb shot slot;
- `path_factor * secondary[sample_index].delta_length` advances progress and
  consumes one or more sample boundaries;
- terminal overflow clears `active`, writes launch velocity, mirrors the last
  state output to `shot+0x1f4`, handles kind `31` supertramp launch, and
  returns mode `3`;
- nonterminal advance interpolates center x, lateral scale, and special scalar
  from the primary sample bank, then uses either kind `42`
  `compute_kind42_attachment_transform` or ordinary matrix interpolation with
  zeroed matrix position rows;
- every normal path stores the basis rows into the Golb flight transform,
  copies `direction` to `velocity`, checks the lateral exit threshold, and
  returns `0` for normal continuation or `template->side_exit_mode == 0` for
  side exit.

Residuals:

- Current matcher result: 71.82% (`uv run snail match scratch
  tools/match/scratches/calc_path_length_z`).
- The shared `golb.h` path-follow names were corrected while keeping
  `initialize_path_follow_golb` exact: this state stores the attachment
  template at `+0x04` and source cell at `+0x08`, not an independent Golb path
  bank/count pair.
- Remaining diff is dominated by the terminal supertramp expression and
  matrix/result register scheduling, not missing semantic lanes. The native
  and candidate frames are now both `0xf4` bytes.
- The overflow loop and normal advance block are semantically equivalent but
  laid out differently; native falls through into a shared advance head while
  the scratch lets VC6 place part of that path later in the function.
- Terminal kind `31`, non-kind-31 terminal z, kind `42` transform, ordinary
  matrix interpolation, flight-transform basis stores, direction-to-velocity copy, and
  side-exit return are all covered. Avoid dummy locals solely to chase the
  native frame size without stronger original-source evidence.

2026-06-13 source-shaping follow-up: terminal and side-exit `shot->position`
copies now use explicit x/y/z stores, matching the native field-write spelling
instead of relying on whole-struct assignment. The `shot->direction` to
`shot->velocity` transfer is also explicit x/y/z, and the side-exit lateral
absolute-value test now uses `float`/`0.0f` instead of widening through
`double`. These source-shaped changes improve the scratch from 32.17% to
35.76%, 414/425 instructions. The remaining frame gap (`0xf4` native versus
`0xe0` candidate), overflow-loop placement, scalar lerp stack slots, and matrix
copy layout are still broad source-shape residuals rather than new semantic
unknowns.

2026-06-13 source-shaping follow-up 2: the ordinary interpolation path now
zeros the copied matrix position rows in native z/y/x store order for both
`from` and `to` before calling `linear_interpolate_matrix`. This is BN-visible
source shape around the matrix-copy block, not a frame-size pad; the focused
matcher stayed at 35.76%, 414/425 instructions, but the local store order now
matches that residual more closely.

2026-06-13 source-shaping follow-up 3: the side-exit threshold test is now
spelled as `abs_lateral > exit_threshold`, so the native side-exit block is the
fallthrough and the normal continuation is the jump target. This is semantically
equivalent to the previous `<=` spelling, but it matches the BN-visible tail
layout better and improves the scratch from 35.76% to 36.95%, still 414/425
instructions.

2026-06-13 source-shaping follow-up 4: the final basis scratch copies now use
real destination `Vec3*` locals for the right/up/forward basis rows before
copying direction to velocity. This matches the native BN shape where each
basis row is copied through a destination pointer instead of direct
`shot->field` stores, and improves the scratch from 36.95% to 40.58%,
408/425 instructions.

Rejected source-shape trial: introducing a `Vec3* shot_position` local for the
terminal, kind-31, and side-exit shot-position writes regressed the scratch from
35.76% to 28.57% (408 candidate instructions), so keep the explicit field stores.

Rejected source-shape trial: introducing a real `Vec3 terminal_position` local
in the terminal kind-31 launch path increased the frame from `0xe0` to `0xec`
and candidate count from 414 to 424, but regressed the matcher from 35.76% to
33.22% by perturbing the terminal block and later matrix-local layout. Do not
use that local as frame padding without stronger source evidence.

Rejected source-shape trial: changing the final velocity transfer to whole
`Vec3` assignment regressed the accepted basis-copy shape from 40.58% to
39.28%, and adding an owner-shot alias around the final copy batch regressed to
37.20%. An explicit scalar-local spelling for the ordinary output vector
emitted the same 40.58% code and was reverted as neutral source churn.

Rejected source-shape trial: narrowing the `shot_position` pointer alias to
only the side-exit copy still regressed the accepted basis-copy shape from
40.58% to 39.38%, so keep the explicit side-exit x/y/z stores.

Rejected source-shape trial: native loads `ecx = template_record` immediately
before the kind-42 transform helper call, matching the member-call evidence
seen in `project_position_onto_track_attachment`, but changing this scratch's
helper declaration to a `Path` member regressed global alignment from
40.58% to 35.21%. The callsite convention evidence is real, but this large
scratch needs a more isolated consolidation than a direct local rewrite.

2026-06-15 type consolidation: the local `PathTemplateSample` name is now
`AttachmentSampleMatrixView`, shared with
`update_track_attachment_follow_state`. It is the same 0xa8 attachment sample
shape already represented by `AttachmentSample`; this scratch keeps the local
view only because its `transform` field needs the local `TransformMatrix`
methods for interpolation while the shared header still uses
`AttachmentTransform`.

2026-06-17 GolbShot consolidation: the local shot window moved into the shared
`golb.h` view. The later ownership closure above supersedes the provisional
scratch-vector names: those offsets are the basis and position rows of
`flight_transform +0x1c4`, followed by the previous-flight owner at `+0x204`.
Velocity `+0x24c` and direction `+0x258` remain independently pinned against
the exact small Golb helpers and this path-follow updater.

2026-06-14 recheck: localized diff still shows one broad region dominated by
the `0xf4`/`0xe0` frame gap, overflow-loop placement, scalar lerp stack slots,
and matrix-copy layout. Hoisting the `center_x`/`lateral_scale`/`special_scalar`
declarations without changing evaluation order emitted identical 40.58% code.
Hoisting the ordinary-path `base_x`/`base_y`/`base_z` locals with explicit
assignments also emitted identical 40.58% code. Treat scalar/base local
declaration order as exhausted; the next useful move needs stronger evidence
around overflow placement or the matrix-copy block rather than more local
slot-shuffling.

2026-06-18 GPT Pro overflow-loop pass: rewriting the overflow consumer from
`for (;;)` plus a named `remaining` local into a `do/while` with
`delta -= samples[current_index].delta_length - progress` improves focused
Wibo from `40.58%`, `408/425` to `40.97%`, `400/425`; masked operands remain
`7 ok`. The useful part is local to the overflow region: candidate region 2
shrinks from `target[14:148] candidate[14:130]` at `36.00%` to
`target[14:148] candidate[14:122]` at `37.19%`, and the first subtraction now
emits native-shaped `fsubp st(1)`. This still does not resolve the broad
`0xf4`/`0xe0` frame gap, scalar-lerp stack slots, matrix-copy layout, or
terminal/side-exit position-copy scheduling.

## 2026-06-19 measured source-shape pass

The Linux i686 runtime now executes the pinned VC6.5 compiler under QEMU. The
previous local scratch reproduced **40.97%** (400 candidate instructions). The
accepted source-shape patch measures **55.41%** (398 candidate instructions),
with 7 masked operands resolved and no unresolved or mismatched masks, using:

```sh
tools/match/match.sh tools/match/scratches/calc_path_length_z --regions --max-regions 12 --region-context 5
```

Accepted changes preserve all previously mapped behavior:

- spell the segment-consumption path as one top-tested `while`, with
  `delta -= current_length - progress` and a real `next_index` local;
- keep `terminal_index` after the overflow path rather than precomputing it;
- use a whole `Vec3` copy only for the initial terminal mirror to
  `shot->position`;
- use `sample_index` directly in the normal path and repeat the natural
  `primary_samples[sample_index]` expressions instead of hoisting a primary
  sample pointer;
- call kind 42 through the recovered `Path` member shape;
- materialize the ordinary-path rotated offset as a real `Vec3` before adding
  the three base components.

The loop now emits the native `fsubp st(1)` form and backward continuation
edge. The direct primary-bank expressions recover the native index/byte-offset
register pattern; the focused scalar interpolation region is 79.17%.

Rejected measured trials:

- precomputing `terminal_index` before the loop scored 56.00%, but inserted
  `mov edi,[segment_count]` / `dec edi` before the initial overflow test and
  changed the terminal compare to `jg`; those instructions are absent from the
  target, so this is rejected as a metric-only alignment gain;
- adding both a named rotated-offset vector and named result vector scored
  54.48% and overgrew the frame to `0xf8` versus native `0xf4`;
- a named result vector without the rotated-offset vector scored 54.50%; whole
  direction-to-velocity assignment scored 54.06%; both regress the accepted
  layout;
- hoisting output/basis/velocity pointers moved the frame but perturbed the
  initial register schedule and regressed to 52-53%.

The remaining precise lead is the ordinary result staging: native reserves
`0xf4`, while this candidate reserves `0xec`. Native has result slots at
`esp+0x2c..0x34` and rotated-product slots at `esp+0x38..0x40` immediately
before the transform at `esp+0x44`. Straight named-`Vec3` spellings allocate
four bytes too much and regress, so the next experiment should target the
original vector-expression/temporary shape rather than add padding.

2026-06-21 ordinary result staging retry: replacing the intermediate
`right_offset` vector with a direct final `Vec3 result` improves focused Wibo
from 55.41% to 55.52% (`400/425` candidate/target instructions) while keeping
the `0xec` frame and the 7 clean masked operands. Direct output-field writes
without a result vector regress to 54.46%, and aggregate assignment
`*output = result` regresses to 54.50% by expanding the copy. Product-scalar
variants compile identically to the retained result constructor, so the scratch
keeps the smaller source spelling until a stronger lead explains native's
separate rotated-product stack slots.

## 2026-07-14 authored path and source-cell ownership

`GolbPathFollowState` now borrows the same shared `Path*` and `SubLoc*` owners
used by the player attachment lane. The private `GolbPathTemplate` and
`GolbPathSourceCell` prefix views are gone; sample traversal uses the canonical
`AttachmentSample` banks, and kind 42 calls the shared `Path` method without a
cast. Focused matching stays honestly unchanged at 55.52%, `400/425`, with all
seven masked operands clean. The exact 16-instruction initializer also remains
proof-grade after loading `SubLoc::attachment_template_record` and
`SubLoc::position` directly.

## 2026-07-17 durable Golb-follow owner export

The live Binary Ninja prototype now reads back as
`int32_t __thiscall(GolbPathFollowState*, float, Vec3*, Vec3*)`, and all four
native exits use `retn 0xc`. That agrees with iOS
`cRPathFollowGolb::Traverse(float, tVector&, tVector*)` and the typed call from
`update_golb_ai`.

Refreshing the tracked decompile replaces the last remaining BN
`struct PathTemplate*` owner with the complete `GolbPathFollowState` graph:
borrowed `Path*` and `SubLoc*`, progress and output state, and the owning
`GolbShot` flight transform. The shared header and IDA replay now carry both
the initializer and traverse ABIs, while health checks pin the owner and its
consumer. No matching source was changed; focused matching remains honestly
at 71.82%, 416/425 instructions, with all seven operands clean.
