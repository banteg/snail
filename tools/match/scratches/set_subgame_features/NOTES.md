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
