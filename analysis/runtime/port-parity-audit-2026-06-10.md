# Port parity audit - 2026-06-10

Static cross-check of the Zig runtime against the tracked BN/IDA decompile exports,
looking specifically for behavior the repo believed correct that contradicts the
native code. All actionable findings are fixed as listed below. Finding 6 was
evidence-only; its IDA typing follow-up is also resolved.

## Resolution status

| Finding | Status | Fix commit |
| --- | --- | --- |
| 1. `'}'` mirrors to `'['` instead of `'{'` | Fixed | `bb287cd` |
| 2. Damage warning overlay envelope is 0 where native uses 1.0 | Fixed | `dc9438e` |
| 3. Widget vertical clamp subtracts height; native does not | Fixed | `6ca2fc5` |
| 4. Jetpack gauge never disarms on fuel-out or near route end | Fixed | `ba7638e` |
| 5. Cameraman matrix blend uses per-tick velocity instead of the subgame rate | Fixed | `2f3b410` |
| 6. IDA Player typing is shifted in the cameraman region | Evidence-only typing follow-up resolved | `f4114ce` |
| 7. Mirror state does not flip the authored lane order in the port | Fixed | `43e1cd0` |
| 8. Mirror coin decision is off by one at exactly 0x4000 | Fixed | `84a7550` |
| 9. Early void-edge carryover arm is missing from a PORT(verified) region | Fixed | `745777c` |
| 10. Parcel placement model spawns every annotation instead of a seeded subset | Fixed | `52598b0` |
| 11. Swept-entry half-span uses float division; native truncates | Fixed | `b274931` |
| 12. Slug contact is cell-crossing in the port; native is a radius test | Fixed | `f8bc253` |
| 13. Supertramp launch handoff uses scaffold constants | Fixed | `d01bc79` |

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
- RESOLVED 2026-06-10: root cause was `analysis/headers/path_template_types.h`
  carrying a stale Player tail (`slow_commentary_*` mid-struct, `_pad_44f`
  4 bytes short) and a mis-ordered Game tail (`pause_gate` placed before the
  `track_state_latch` cluster with a +0xa0000 pad typo that also unhooked the
  `selected_level_record` cluster). Both headers are fixed, the stale `Player`
  and `Game` types were force-replaced in the IDA database (IDA's
  `parse_decls` silently keeps conflicting definitions), and all 664 tracked
  exports were refreshed with health checks passing.

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
  row-fraction window (`frac(z)` must be above `0.2` when
  `open_edge_mask & SUBLOC_OPEN_PREVIOUS_ROW` and below `0.8` when
  `open_edge_mask & SUBLOC_OPEN_NEXT_ROW`, otherwise `(0.0, 1.0)`).
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

### 10. Parcel placement model: port spawns every annotation, native places a seeded random subset of sets (high)

- port: `zig/src/gameplay.zig:3332-3372` — `refreshLiveTrackParcels` spawns a
  live parcel for every row whose segment annotation is `.parcel`, in a
  scan-ahead window. `segment.ParcelAnnotation.id` (the authored set index)
  is stored but never used for selection. Digit cells `'0'..'9'` only map to
  floor tile 0x0f (`track.zig` glyph table).
- native: `place_parcels_on_track` @ 0x4438e0 (modes 0/7; mode 1 delegates to
  `place_challenge_parcels_on_track`):
  - candidates are grouped per segment-instance into sets 1..9 (from
    flagged `Parcel=` records *and* digit glyphs, which place at lane
    `i - 4 + 0.5`), with set-0 candidates pooled individually;
  - whole sets are chosen via `random_float_below(set_count)` (CRT rand,
    part of the seeded build stream) until `80% · required − max_set_size`
    parcels are placed, each chosen set then removed from the pool;
  - the remainder is filled one-by-one from random set-0 candidates until
    exactly the authored `Parcels=` count is on track (with
    `report_errorf` checks for under-allocation and duplicates);
  - placed cells get flags `|= 0x11`; parcel x is negated on mirrored rows
    (row flag 0x20); parcels on attachment rows (flags `1|0x40`) are
    projected onto the path node position (`get_path_position_at_node`, or
    the kind-42 transform).
- consequence: parcel count and distribution are wrong in the port — every
  authored candidate appears every run, instead of a per-seed random subset
  summing to the authored count. Set grouping, digit-glyph candidates, the
  mirrored-row x flip, and path projection are all absent. This also breaks
  replay determinism for postal runs once seeds are honored, and the
  RNG consumption (one rand per chosen set/single) is missing from the
  build-stream model, shifting every later consumer.

### 11. Swept-entry half-span uses float division; native truncates (entry gate only) (medium)

- port: `zig/src/gameplay/attachment.zig:152-158` — `templateHalfSpan`
  returns `span_cells * 0.5` as f32; shared by the swept-entry x gate
  (`installedAttachmentEntryForSweep`) and the side-exit threshold.
- native is *asymmetric* about the same `+0x54` field (`width_cells`,
  `analysis/headers/path_template_types.h:731`):
  - entry: `try_enter_track_attachment_from_swept_motion` @ 0x42c770 uses
    signed **integer** division (BN @ 0x42c84b/0x42c86f, `s>> 1` idiom)
    before the ±0.3 margin;
  - side-exit: `update_track_attachment_follow_state` @ 0x420cb0 uses
    `float(width_cells) * 0.5 + 0.3` (BN @ 0x421675) — no truncation.
- consequence: for odd-span templates (cage2, screw, twistera/b,
  twister2a/b, toads — span 3 per the port's spec table) the native entry
  window is ±1.3 cells while the port accepts ±1.8; the port's side-exit
  threshold already matches native. The port comment claiming entry and
  side-exit share the same semantics over `+0x54` is wrong about the
  arithmetic, not the field.
- the rest of the swept gate matches: tail-to-head sample walk, the
  `sample[5] > 0` (up-y) skip, start gates `y ≥ −0.2`, `0 < z < extent`,
  end gate `y ≤ 0.001`, and the caller's 1.05 velocity scale.

### 12. Slug contact is cell-crossing in the port; native is a radius test against the live actor (medium)

- port: `zig/src/gameplay.zig:1908-1944` — slug contact fires when the
  resolved row/lane's `gameplay_cell == .slug`. The reaction branches
  (invincible kill, repeat-hit `−8·rate²·0.004` + damage 1.0, first-hit
  velocity triplet + carryover + cutscene 10) are correctly cited and
  match native.
- native: `handle_subgoldy_collisions` @ 0x444cf0, IDA lines 160-200 —
  contact requires `Δ component < 2.0` then `|Δ| < 1.5675001` against the
  slug actor's *live* position, which `update_slug_hazard_ai` @ 0x43f930
  moves over time (including along attachments). The 1.5675 radius constant
  appears nowhere in the port.
- consequence: contact geometry differs — native slugs hit within a ~1.57
  sphere around wherever the slug currently is; the port hits exactly on the
  authored cell. A patrolling slug that has crawled off its spawn cell can
  be walked through in the port, and near-miss lanes that the original
  punishes are safe. Detection sits beside PORT(verified)-tagged reaction
  code, so the gap is easy to mistake for verified behavior.
- note: this collision pass is another consumer of the shifted IDA Player
  typing (finding 6): the position triple reads at lines 160-162 are
  labeled `jetpack_gauge.warning_intensity` / `cached_camera_target_world`.

### 13. Supertramp launch handoff uses scaffold constants instead of the native velocity transfer (low-medium)

- port: `zig/src/gameplay.zig:4995-5020` — launch vertical velocity is
  `max(0.15, clamp(rate·last_delta, 0, 1)) · 12.0`, launch height is floored
  at 0.6, and the camera pitch cycle steps at a fixed `1/72`.
- native: `update_track_attachment_follow_state` @ 0x420cb0 end-of-template
  SUPERTRAMP branch (IDA :401-429) — `motion.y = motion.z * 0.7` where
  `motion.z = clamp(path_factor · last_delta_length, ·, 1.0)` with **no
  floor**; launch position comes from the last sample's forward scaled by
  `(remainder + width_or_scale)`; the pitch cycle step is a game global
  (`game+0x74650`) times `0.013888888`; and voice 15 plays on launch.
- consequence: launch arc height and the minimum-speed launch behavior
  differ (native launches proportionally weaker at low approach speed; the
  port never launches below 1.8 units of vertical velocity). The enclosing
  launch lane is flagged PORT(partial) in a *different* function
  (`gameplay.zig:1885`), so this function reads as finished. Confidence:
  confirmed for the formula shape; the global multiplier needs a trace.
- related latent nit: the port adds `installed_heading_delta` to
  `heading_roll` every follow tick (`gameplay.zig:5188`) where native adds
  it once per exit (IDA :318, :438). The only shipped non-zero value is
  ±2π, so both are rotation-identity today, but the port accumulates
  unbounded float magnitude over long follows and the cadence is wrong if
  any template ever carries a non-full-turn delta.

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
- `mark_track_warning_zones` @ 0x4354f0: seed tile set
  {0x02..0x0e, 0x17, 0x19, 0x21}, the 6-rows-behind × 2-lanes footprint,
  and the row/lane bound guards all match `buildRuntimeWarningZoneGrid`.
  The fringe-variant promotion and slide harmonize passes are deliberately
  empty in the port (documented PORT(partial) BOD-table gaps, not errors).
- track build seed path: replay seed reuse, seed 0 for tutorial/time-trial,
  `(i64)random_float_below(32768.0)` ≡ raw `rand()`, MSVC LCG constants in
  `math_random.zig`, pick order (pick → mirror roll per segment), mode-1 pick
  range `(scalar*0.9+0.1)*count`, course length `floor((scalar*0.65+0.35) *
  Length) - last_rows`, and the mirror anti-streak counter (≥4 flips) match.
- `update_track_attachment_follow_state` @ 0x420cb0: the distance-step
  advancement (step = `path_factor · delta_length(initial sample)`, remainder
  carried across sample boundaries, progress zeroed per crossing), the
  0.999000013 overshoot clamp, the `vertical_offset += motion.y` accumulate
  with negative clamp-to-zero, the side-exit gates (jetpack suppress,
  `vertical_offset > 0` suppress, `float(width)·0.5 + 0.3` threshold, ±4.0
  world clamp), the wrapped ±π orientation interpolation, and the
  `(index+frac)·delta/count` camera phase lane all match the port. The
  `side_exit_mode` flag the port omits is 0 in every shipped template
  constructor (nothing writes nonzero), so the omission is behaviorally
  neutral. The `voice 4` milestone is unreachable: both Windows and iOS compare
  the incremented index with `2 * segment_count` even though the same loop
  terminates at `segment_count`. The `flag_9c` BOD-swap milestones at `(3·count)/7` and
  `count−1` belong to the known-partial installed-record/BOD lane.
- `handle_subgoldy_collisions` @ 0x444cf0 constants: salt 0.15 @ 0.98 gate,
  sublazer 0.02 @ 0.49, garbage 0.04 @ 0.98 with z-tolerance 1.0 and
  knockback factors 0.18 (x) / 0.10 (z), slug reaction branches
  (invincible kill, repeat `−8·rate²·0.004` + 1.0, first-hit
  `(0, rate·0.2, −rate·0.2)` + carryover + cutscene 10), health −0.5 @
  0.98 with 0.4 height gate, jetpack pickup @ 3.0, and ring gate 1.24 all
  match the port (detection-model caveat for slugs in finding 12).
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
