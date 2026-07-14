# Exact match

`set_subgame_features` seeds `game->runtime_flags` for the current mode before
runtime track population. If a selected-level record override is active, it
copies the record's flag word at `+0x38`; otherwise the native presets are:

- modes `0` and `1`: `0xf5cfff`
- mode `4`: `0x75cfff`
- mode `7`: `0xe4cfff`
- all other modes: `0x600484`

The exact source shape keeps the native pre-switch seed `0x484`, then shares
the `0x600484` default assignment across the bounded switch. The scratch uses
`END=0x435e3c` because bytes after the final `ret` are the native jump table
data for this switch, not executable function body.

## 2026-07-14 game-wide feature owner

The native whole-word writes now use `SubgameRuntimeFlagPreset` names instead
of anonymous mode masks. `SubgameRuntimeFlag` separately names only bits with
proved Windows consumers; preset-only bits `0x040000`, `0x100000`, and
`0x200000` remain intentionally opaque. Focused output remains exact at
100.00%, 19/19 instructions, full prefix, and three clean operands.
