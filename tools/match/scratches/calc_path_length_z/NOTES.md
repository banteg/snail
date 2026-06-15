# calc_path_length_z

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
- every normal path stores the basis rows into the Golb slot scratch vectors,
  copies `direction` to `velocity`, checks the lateral exit threshold, and
  returns `0` for normal continuation or `template->side_exit_mode == 0` for
  side exit.

Residuals:

- Current matcher result: 40.58% (`tools/match/match.sh
  tools/match/scratches/calc_path_length_z --full`).
- The shared `golb.h` path-follow names were corrected while keeping
  `initialize_path_follow_golb` exact: this state stores the attachment
  template at `+0x04` and source cell at `+0x08`, not an independent Golb path
  bank/count pair.
- Remaining diff is dominated by source-shape and stack layout, not missing
  lanes: native reserves `0xf4` bytes while the scratch reserves `0xe0`, and
  native keeps more float staging locals for the scalar lerps and matrix copies.
- The overflow loop and normal advance block are semantically equivalent but
  laid out differently; native falls through into a shared advance head while
  the scratch lets VC6 place part of that path later in the function.
- Terminal kind `31`, non-kind-31 terminal z, kind `42` transform, ordinary
  matrix interpolation, basis scratch stores, direction-to-velocity copy, and
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
helper declaration to a `PathTemplate` member regressed global alignment from
40.58% to 35.21%. The callsite convention evidence is real, but this large
scratch needs a more isolated consolidation than a direct local rewrite.

2026-06-15 type consolidation: the local `PathTemplateSample` name is now
`AttachmentSampleMatrixView`, shared with
`update_track_attachment_follow_state`. It is the same 0xa8 attachment sample
shape already represented by `AttachmentSample`; this scratch keeps the local
view only because its `transform` field needs the local `TransformMatrix`
methods for interpolation while the shared header still uses
`AttachmentTransform`.

2026-06-14 recheck: localized diff still shows one broad region dominated by
the `0xf4`/`0xe0` frame gap, overflow-loop placement, scalar lerp stack slots,
and matrix-copy layout. Hoisting the `center_x`/`lateral_scale`/`special_scalar`
declarations without changing evaluation order emitted identical 40.58% code.
Hoisting the ordinary-path `base_x`/`base_y`/`base_z` locals with explicit
assignments also emitted identical 40.58% code. Treat scalar/base local
declaration order as exhausted; the next useful move needs stronger evidence
around overflow placement or the matrix-copy block rather than more local
slot-shuffling.
