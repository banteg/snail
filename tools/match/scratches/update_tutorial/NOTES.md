# update_tutorial @ 0x448de0

Exact tutorial update thunk.

2026-06-20 type cleanup:

- Uses the shared `TutorialController` layout from `include/new_game_menu.h`.
  The recovered `game` pointer at controller `+0x0c` is the receiver for
  `get_track_grid_cell_at_world_position`.
- The position argument is the game-local vector at `game + 0x3bb7cc`, matching
  the Binary Ninja decompile.
- Focused matcher remains exact at 5/5 instructions with 1 clean masked
  operand.
