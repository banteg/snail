# calc_subgame_rate

Initial scratch for the per-frame subgame rate calculator.

Recovered relationships:

- `base_rate +0x30` feeds `subgame_rate +0x38` when `subgame_state +0x3c`
  is not active state `2`.
- active-state rate ramps from the embedded `player.live_matrix.position.z`
  (`Player +0x70`, runtime `+0x3bb7d4`) divided by
  `completion_row_start +0x58`, clamped to `[0, 1]`.
- `level_mode +0x40` selects the completion ramp constants: `0.55` for modes
  1/3, `0.4 + 0.2` for mode 4, and `0.2` otherwise.
- `player.damage_gauge.state` and `player.damage_gauge.display_fill` add the
  sinusoidal bonus-rate envelope, with a smaller base bonus in modes 1/4.
- `player.sub_hover.state` and
  `player.sub_hover.warning_intensity_latch` add the final half-rate lane.
- Focused Wibo result after active-state fallthrough shaping was 84.52%,
  84/84 instructions, with 14 masked operands OK.
- 2026-06-18 bonus-envelope correction: the native source shape does not cache
  `damage_gauge.display_fill` in a `phase` local for the gate. Reading the member
  directly in the two comparisons recovers the native `fcomp`/reload sequence.
  The selected bonus is also source-shaped as a mode-1 fast path, default
  `0.6`, then mode-4 override; and the sine envelope is staged before
  multiplying by the selected bonus. This raises the focused Wibo result to
  100.00%, 84/84 instructions, with 16 masked operands OK.

2026-07-11 owner closure: Binary Ninja's complete `Player` field at
`SubgameRuntime +0x3bb764` proves that all five former contextual rate aliases
belong to the embedded actor. Replacing the sparse runtime overlay with direct
`player` fields preserves the proof-grade 100.00% match and all 16 operands.
