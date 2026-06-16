# calc_subgame_rate

Initial scratch for the per-frame subgame rate calculator.

Recovered relationships:

- `base_rate +0x30` feeds `subgame_rate +0x38` when `subgame_state +0x3c`
  is not active state `2`.
- active-state rate ramps from `completion_progress_z +0x3bb7d4` divided by
  `completion_row_start +0x58`, clamped to `[0, 1]`.
- `level_mode +0x40` selects the completion ramp constants: `0.55` for modes
  1/3, `0.4 + 0.2` for mode 4, and `0.2` otherwise.
- `bonus_rate_state +0x3bbb28` and `bonus_rate_phase +0x3bbb48` add the
  sinusoidal bonus-rate envelope, with a smaller base bonus in modes 1/4.
- `nuke_rate_state +0x3bdec0` and `nuke_rate_progress +0x3be0c0` add the
  final half-rate lane.
- Focused Wibo result after active-state fallthrough shaping: 84.52%, 84/84
  instructions, with 14 masked operands OK. Remaining residual is localized to
  bonus-envelope x87 scheduling and branch label distance, not unresolved data.
