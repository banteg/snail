# initialize_cameraman @ 0x446160

Exact match: `100%`, `20/20` instructions, `6 ok` masked operands.

This initializes the shared `Cameraman` layout:

- `player` borrows `SubgameRuntime::player`
- `game` borrows the enclosing `GameRoot::subgame`
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

2026-07-14 root-owner closure: both backlinks now follow the canonical
`GameRoot -> SubgameRuntime -> Player` graph. The method remains exact at
20/20 with all six operands clean.

2026-07-14 camera handoff recovery: the byte at `Cameraman +0xcc` is
`force_camera_update`. `update_subgame_camera` copies it into the same
`camera_snap_requested` gate used by `CutScene::force_camera_update`; the
Cameraman initializer and AI both clear the request in the shipped Windows
path. The semantic rename is instruction-exact in this initializer.

2026-07-16 durable replay closure: the path-template BN replay now guards
`Cameraman +0xcc` explicitly as `force_camera_update`. This prevents the live
database from retaining the older `unresolved_cc` spelling even when the
complete imported type is structurally unchanged. The exact 20/20 initializer
and its six clean operands are unaffected.
