# add_subgoldy_score

Current match: 80.62%, source-shaped.

- `score_kind` selects fixed point awards for regular hazards/parcels and uses
  `bonus_score` only for score kind `5`.
- The six buckets at `Player+0x310` accumulate per-kind points; `Player+0x2e4`
  is the total subgame score.
- Crossing a 50,000-point boundary increments `Player+0x4340` up to a visible
  life stock cap of `9`.
- The score sound `0x2c` is gated off while `game+0x74658` or `game+0x24` is
  nonzero.
- The function is a `void` mutator in source terms; Binary Ninja reports a
  return because the trailing `eax` value is still live at the native epilogue.
- `END=0x44037e` excludes the native switch jump-table data that follows the
  final `ret`.
- The arithmetic prefix matches exactly through the 50,000-point threshold
  compare. The remaining live-code residual is the final sound-gate epilogue:
  native keeps `pop edi; pop esi; ret 8` after the optional manager-thiscall,
  while the obvious VC6 source forms hoist the saved-register pops before the
  gate block.
- `snail match idioms gated-tail-member-*` now records the tested tail forms:
  the void/call-result forms preserve the native gate loads but hoist the pops,
  and the preserve-game return form keeps the epilogue low but adds a non-native
  returned-game restore.
- 2026-06-16 shared-`Player` probe: `total_score`, `score_buckets`, and
  `visible_life_stock` are present in `player.h`, but including it here preserved
  the instruction stream while changing the switch-table relocation audit from
  `6 ok` to `5 ok, 1 mismatch` (`$L460` instead of
  `add_subgoldy_score_jump_table`). Keep the compact local shell until that
  symbol-shape issue has a targeted fix.
