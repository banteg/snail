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

- Current matcher result: 35.76% (`tools/match/match.sh
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

Rejected source-shape trial: introducing a `Vec3* shot_position` local for the
terminal, kind-31, and side-exit shot-position writes regressed the scratch from
35.76% to 28.57% (408 candidate instructions), so keep the explicit field stores.
