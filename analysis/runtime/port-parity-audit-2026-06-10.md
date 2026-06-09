# Port parity audit - 2026-06-10

Static cross-check of the Zig runtime against the tracked BN/IDA decompile exports,
looking specifically for behavior the repo believed correct that contradicts the
native code. Four divergences confirmed, each verified against both decompilers.

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

## Caveats

- This audit pass was interrupted twice; the track-rendering, attachment,
  asset-format, frontend-transition, and parcels/outer-bridge lanes were only
  partially swept and got no completed verdict. The four findings above are the
  fully verified subset, not an exhaustive sweep.
- Two of the four findings sat under `PORT(verified)` comments or
  parity-labelled tests. When fixing, re-check neighbors of each finding —
  verified tags in these files are not currently trustworthy evidence.
