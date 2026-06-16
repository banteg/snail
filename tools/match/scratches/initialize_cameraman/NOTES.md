# initialize_cameraman @ 0x446160

Exact match: `100%`, `20/20` instructions, `6 ok` masked operands.

This initializes the shared `CameramanState` layout:

- `player` points at `g_game_base + 0x42fd7c`
- `game` points at `g_game_base + 0x74618`
- `previous_desired_matrix`, `desired_matrix`, and `live_matrix` are reset to
  identity
- attachment lift smoothing starts at zero
- `fov_degrees` starts at `110.0f`

2026-06-16 consolidation: `CameramanState` now lives in
`include/cameraman_state.h` and is shared with `update_cameraman`. The focused
match remains exact.
