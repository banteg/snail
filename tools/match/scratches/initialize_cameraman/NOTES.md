# initialize_cameraman @ 0x446160

Exact match: `100%`, `20/20` instructions, `6 ok` masked operands.

This initializes the shared `Cameraman` layout:

- `player` points at `g_game_base + 0x42fd7c`
- `game` points at `g_game_base + 0x74618`
- `previous_desired_matrix`, `desired_matrix`, and `live_matrix` are reset to
  identity
- attachment lift smoothing starts at zero
- `fov_degrees` starts at `110.0f`

2026-06-16 consolidation: `Cameraman` now lives in
`include/cameraman.h` and is shared with `update_cameraman`. The focused
match remains exact.

2026-06-21 owner typing: `Cameraman::game` is now a `SubgameRuntime*`.
The initializer keeps the same exact `100%`, `20/20` match with an explicit
cast from `g_game_base + 0x74618`.

2026-07-11 authored-owner recovery: Android `cRCameraman::Init()` writes the
same three matrices at +0x00/+0x40/+0x80, Player/SubgameRuntime backlinks at
+0xc0/+0xc4, FOV at +0xc8, byte gate at +0xcc, and envelope pair at
+0xd0/+0xd4. This independently proves the exact 0xd8-byte Windows
`Cameraman` owner and the side-effect-only `void` contract. Focused Wibo
remains exact at 20/20 instructions with six clean masked operands.
