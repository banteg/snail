# update_tutorial @ 0x448de0

Exact tutorial update thunk.

2026-06-20 type cleanup:

- Uses the primary shared `Tutorial` layout from `include/tutorial.h`.
  The recovered `game` pointer at controller `+0x0c` is the receiver for
  `get_track_grid_cell_at_world_position`.
- The position argument is the embedded player's transform position:
  `SubgameRuntime::player` at `+0x3bb764`, `RenderableBod::transform` at `+0x38`,
  and `TransformMatrix::position` at `+0x30` resolve the former raw
  `game + 0x3bb7cc` expression.
- Focused matcher remains exact at 5/5 instructions with 1 clean masked
  operand.

2026-06-21 subgame-header consolidation: the controller's `game` field is now a
`SubgameRuntime*`, so this thunk can call `get_track_grid_cell_at_world_position`
through the shared subgame header instead of a scratch-local method-only `Game`
view.

2026-07-11 authored owner: Android/iOS retain this exact 5/5 member as
`cRTutorial::AI()`. The complete 0x1c owner replaces the old 0x10 prefix plus
anonymous SubgameRuntime padding; its sole operand remains clean.

2026-07-14 embedded-player ownership: the world-position argument now uses
`player.transform.position` through the shared runtime, body, and matrix
layouts instead of preserving the resolved field as a raw byte offset.
