# Port parity audit - 2026-06-10

Static cross-check of the Zig runtime against the tracked BN/IDA decompile exports,
looking specifically for behavior the repo believed correct that contradicts the
native code. Round 1 (findings 1-4) is fixed as of `ba7638e`; round 2
actionable findings are fixed as of `2f3b410`, `43e1cd0`, and `84a7550`.
Finding 6 is evidence-only and remains an IDA typing follow-up.

## Confirmed findings

### 1. `'}'` mirrors to `'['` instead of `'{'` in glyph normalization (high)

- port: `zig/src/track.zig:2715-2722` — `'}' => ... else if (mirror_state) '['`
- native: `normalize_segment_glyph_for_track_flags` @ 0x437270
  - IDA `analysis/decompile/ida/functions/00437270-...c:129-148`: case `'}'` with
    flags `0x200|0x20` and the mirror byte set shares `LABEL_23` with `']'` and
    resolves to `0x7B` (`'{'`), not `'['`.
  - BN `analysis/decompile/binja/functions/00437270-...c:95-106`: case `0xb`
    falls through `label_43732d` → `result.b = 0x7b`.
- native mirror table (flags `0x200|0x20`, mirror byte set):
  `'['`→`'['` (unchanged), `']'`→`'{'`, `'{'`→`'}'`, `'}'`→`'{'`. The table is
  intentionally asymmetric; the port assumed a symmetric bracket swap for `'}'`.
- consequence: on mirrored tracks, every `'}'` cell builds tile `0x05`
  (the `'['` transition) instead of tile `0x02`/`0x08` (the `'{'` transition) —
  wrong tile family in both gameplay and rendering. All other lanes of the
  normalize function match.

### 2. Damage warning overlay envelope is 0 where native uses 1.0 (high)

- port: `zig/src/gameplay/damage.zig:289-291` — `overlayAlpha` returns `0.0`
  when `fill_ratio` is in `[0.1, 0.9]`.
- native: `update_damage_gauge` @ 0x440fd0,
  `analysis/decompile/ida/functions/00440fd0-...c:105-139`: when
  `state != 0` and `display_fill <= 0.9`, the envelope is `display_fill * 10`
  below `0.1` and `1.0` in `[0.1, 0.9]`; only the `state == 0` early-out
  returns no overlay.
- consequence: during the warning/drain state the pulsing damage overlay is
  invisible for most of the gauge range in the port; in the original it pulses
  at full strength until the gauge falls below 0.1.

### 3. Widget vertical clamp subtracts height; native does not (medium)

- port: `zig/src/frontend/widget.zig:505-506` —
  `if (top + height + pad > 480) top = 480 - pad - height`.
- native: `layout_frontend_widget` @ 0x4024a0,
  `analysis/decompile/ida/functions/004024a0-...c:82-90` —
  `if (pad + top > 480) clamped_top = 480 - pad`. Horizontal is the asymmetric
  partner: it does include width (`640 - pad - width`, lines 73-81), which is
  probably what invited the symmetric port.
- consequence: both the trigger condition and the clamped position differ.
  Any wrapped-text widget near the bottom edge clamps `height` pixels higher
  than the original (and clamps in cases where the original would not).

### 4. Jetpack gauge never disarms on fuel-out or near route end (high)

- port: `zig/src/gameplay/jetpack.zig:78-86` —
  `if (self.progress > 1.0 or row_near_end) return;` with `active` left true.
  The accompanying comment (and the test note at `zig/src/gameplay.zig:10903`)
  claims `PORT(verified)`: "the state stays active — the gauge does not disarm
  here". Both decompilers contradict this.
- native: `update_jetpack_gauge` @ 0x43a390
  - IDA `analysis/decompile/ida/functions/0043a390-...c:23-32`: on
    `progress > 1.0 || (completion_row_start - 5) < player.z` it calls
    `end_jetpack_hover`, calls `set_snail_jetpack(0)` when `progress <= 0.94`,
    sets the state field (`this+12`) to 0, and zeroes the wobble fields — a
    full disarm.
  - BN `analysis/decompile/binja/functions/0043a390-...c` @ 0x43a543-0x43a579:
    same sequence, `gauge->state = 0`.
- consequence: in the port an exhausted jetpack stays armed forever —
  `zig/src/gameplay.zig:2456` keeps granting forward velocity while
  `self.jetpack.active`, and hover never ends through this lane. Two tests
  (`gameplay.zig:10891`, `jetpack.zig` "near empty edge...") encode the wrong
  behavior, so they will need updating together with the fix.

## Round 2 findings

### 5. Cameraman matrix blend uses per-tick velocity instead of the subgame rate (medium-high)

- port: `zig/src/gameplay/camera.zig:483-485` —
  `cameramanMatrixBlendFactor` returns `runner.track_step_rows * 0.3`
  (clamped), where `track_step_rows` is the per-tick forward row advance
  (`gameplay.zig:806`, ≈ rate × 0.17…0.5).
- native: `update_cameraman` @ 0x4461d0, BN @ 0x4466b4 —
  `linear_interpolate_matrix(..., game->track_center_x * 0.3)`. `Game+0x38`
  is the live subgame rate written by `calc_subgame_rate` @ 0x4404d0
  (`analysis/headers/path_template_types.h:672`), which the port already
  mirrors in `runner.track_center_x` (`updateNativeTrackCenterRate`).
- consequence: at base rate ≈ 0.49 the native camera lerps ~0.147/tick while
  the port lerps ~0.025-0.073/tick — the follow camera is roughly 2-6x
  laggier than the original, and the lag varies with instantaneous velocity
  instead of the rate. The test expectations at `gameplay.zig:10979/10982`
  encode the wrong source.

### 6. IDA Player typing is shifted in the cameraman region (low, evidence-only)

- the IDA export `analysis/decompile/ida/functions/004461d0-update_cameraman.c`
  labels the reads at `player+0x2964/0x2968/0x296c` as
  `jetpack_gauge.warning_intensity` / `cached_camera_target_world.x/.y`;
  the raw instruction at 0x4461f5 is `fld dword [eax + 0x2964]` and the
  BN-typed header places `cached_camera_target_world` at `player+0x2964`
  (after the 0x214-byte gauge at +0x2750). BN's export and the Zig port are
  correct; IDA's Player struct is off by one field here.
- consequence: none in the port; this is an audit hazard. Anyone comparing
  the port against the IDA export alone would "find" three false camera
  divergences (base x shake, lateral follow, lateral roll). Re-sync the IDA
  database's Player typing.

### 7. Mirror state does not flip the authored lane order in the port (high)

- port: `zig/src/track.zig:1996-2044` (`buildRuntimeTileGrid`) and the parallel
  walk in `buildAttachmentSourceRowMirrorStates` — under `mirror_state` the
  port only swaps directional glyphs via `normalizeSegmentGlyphForTrackFlags`;
  source cells are always read at their authored lane index.
- native: `populate_runtime_track_cells_from_segments` @ 0x435eb0 —
  IDA lines 499-515: `v50 = mirror_byte ? 7 - lane : lane` and the source cell
  read `v54 = segment + row + (v50 << 8) + 20`; BN @ 0x436655-0x436682 shows
  the same (`ebp_1 = 7 - edx_29` selects the source column, destination walks
  0..7 sequentially). The glyph normalize pass handles the directional swaps
  on top of the flip, not instead of it.
- consequence: every row whose mirror coin lands true is horizontally flipped
  in the original but keeps its authored orientation in the port — wrong lane
  layout for roughly half of all segments in any mode where the mirror
  selector runs. This compounds with the (now-fixed) `'}'` finding: glyph
  swap parity alone was never sufficient.

### 8. Mirror coin decision is off by one at exactly 0x4000 (low)

- port: `zig/src/track.zig:1971` — `decision = nextInt15() >= 0x4000`.
- native: `switch_track_mirror` @ 0x435e60 — `random_float_below(1.0) > 0.5`,
  i.e. `rand * 2^-15 > 0.5`, which is `rand > 16384`; a roll of exactly
  16384 (0x4000) is `false` natively but `true` in the port.
- consequence: 1-in-32768 rolls diverge, and once one coin differs the
  anti-streak counter and every subsequent mirror state in the level
  diverges with it. Trivial fix (`> 0x4000`), meaningful for deterministic
  replay parity.

### 9. Early void-edge carryover arm is missing from a PORT(verified) region (medium)

- port: `zig/src/gameplay.zig:4647-4660` — the only ground-path
  `begin_post_follow_carryover` arm fires at `position_y < 0.0` with
  non-positive velocity, citing `0043b120-update_subgoldy.c:581-583`. The
  enclosing comment block (`gameplay.zig:4515`) claims the mirror covers IDA
  lines 352-584.
- native: `update_subgoldy` @ 0x43b120, IDA lines 477-491 — inside that same
  claimed region there is a second, earlier arm: when the current cell's
  `tile_id` is 0 or 35 (void / open-neighbor), `position.y < 0.49`, and
  `velocity.y <= 0`, native begins carryover immediately, gated by a
  row-fraction window (`frac(z)` must be above `0.2` when `tile_flags_3d & 1`
  and below `0.8` when `tile_flags_3d & 2`, otherwise `(0.0, 1.0)`).
- consequence: walking off a floor edge arms `attachment.exit.pending` about
  half a ride-height later in the port. Exit-pending gates swept attachment
  entry (`try_enter_track_attachment_from_swept_motion` requires it) and the
  exit-damping/gravity lanes, so late arming can miss path entries the
  original catches. The fraction-window gating does not exist in the port at
  all.

Doc nit found on the way: the comment above `applyTileFamilyFloorReaction`
(`gameplay.zig:4695-4697`) says slope tiles drive `velocity.y = 1.2` and
down-ramps `0.8`; the code (correctly) uses `rate * 0.3` and `rate * 0.2`.
Native also gates the down-ramp lookback dispatch on
`!control_override_active` (IDA :564), which the port does not check.

## Checked and matching (for coverage)

- `normalize_segment_glyph_for_track_flags`: all non-`'}'` glyph lanes
  (`' '`, `'$'`, `'-'`, `'<'`/`'>'`, `'='`, `'['`, `']'`, `'_'`, `'o'`, `'{'`,
  `'|'`) match the port.
- `update_damage_gauge`: display-fill lerp (0.2), hit-flash step/reset, warning
  state machine gates (`0x430199`, `0x4301bc`, `0x42fde8 == 0.49`), drain deltas
  (`-0.0016666667` forced, `-0.0066666668` unforced), exit conditions
  (gates a/b/c), and the suspend-gate scope all match. Note: BN's flattened
  output makes the suspend gate look like it skips only the lerp; IDA shows it
  skips the whole state machine, which is what the port does — BN linear output
  alone would have produced a false finding here.
- `update_warning` / `start_warning`: solid alpha `0.999000013`, fade-cycle
  alpha ramp, state flip + sound-50 cadence, and the `progress=1.0, state=2`
  start seed all match `WarningActor`.
- `update_jetpack_gauge` warning math: 0.1 ramp-in, 0.94 near-empty band,
  `(1-p)*16.666668` phase, cell-flag `0x80` snap to 0.94, the one-shot
  `set_snail_jetpack(0)` + `uninit_jet_particles` on the 0.94 crossing, and the
  wobble formulas all match.

## Round 2 checked and matching

- `format_time_trial_string` @ 0x448960: the effective `%1i:%02i:%02i` format
  (the `%03i` sprintf is dead, overwritten by the second call) and the
  `-:--:--` zero sentinel (verified against the binary at VA 0x4AC5BC) match
  `formatTimeTrialString`.
- `update_cameraman` @ 0x4461d0: base matrix rows (0.946001/0.324162),
  vertical lift lerp (1.15 → 0.35 over the `z/first_rows*1.4-0.4` blend),
  intro pitch `(1-blend)*0.8725`, pitch clamp ±1.2215 from
  `(-2-(h-0.49)*5)*0.017450`, lift-envelope template-kind set
  {8,9,10,0x0e,0x10,0x24,0x2b,0x2d} (decoded from the named enum), launch
  envelope `cos(p*3π/2+π/2)` scale 0.24, smoothed-lift lerp 0.1, prev-z
  deadzone clamp 1.7/3.0, worm FOV 110+50 with lerp 0.3, and the outer
  0.9 shared-camera lerp (`app/subgame_camera.zig`) all match.
- track build seed path: replay seed reuse, seed 0 for tutorial/time-trial,
  `(i64)random_float_below(32768.0)` ≡ raw `rand()`, MSVC LCG constants in
  `math_random.zig`, pick order (pick → mirror roll per segment), mode-1 pick
  range `(scalar*0.9+0.1)*count`, course length `floor((scalar*0.65+0.35) *
  Length) - last_rows`, and the mirror anti-streak counter (≥4 flips) match.
- `update_subgoldy` physics constants: yz decay `1-rate*0.003` (z gated on
  the trampoline flag, y unconditional), x decay `1-rate*0.1`, gravity
  `-0.01*rate²`, forward clamp `[0.17, 0.5]*rate`, slide/jetpack boost
  `2*rate²*0.004`, negative-ring recovery `rate²*0.004*0.25`, exit damping
  `1-rate*0.2` gated on row flag 0x100/jetpack, slide-boost tile set
  {0x0f,0x10,0x12,0x13} plus drain+slide-family, slope lift `rate*0.3`,
  ramp-down `rate*0.2`, mouse steer `(320-x)*0.0125` clamp ±3.7, x clamp
  ±4.0, floor snap window `(-0.16333, 0.49)`, squidge threshold −0.03,
  trampoline catch (tile 22, ±0.49 around anchor, `rate*0.3` bounce,
  sound 41), completion deceleration `2*rate²*0.004` past
  `completion_row_start+2.5`, and death at `y < -7` all match.

## Caveats

- This audit pass was interrupted twice; the track-rendering, attachment,
  asset-format, frontend-transition, and parcels/outer-bridge lanes were only
  partially swept and got no completed verdict. The findings above are the
  fully verified subset, not an exhaustive sweep.
- Two of the first four findings sat under `PORT(verified)` comments or
  parity-labelled tests. When fixing, re-check neighbors of each finding —
  verified tags in these files are not currently trustworthy evidence.
