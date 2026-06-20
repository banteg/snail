# initialize_tutorial @ 0x448da0

Exact tutorial controller initializer.

2026-06-20 type cleanup:

- Promoted the small `TutorialController` layout to `include/new_game_menu.h`.
  Binary Ninja and the scratch agree on `state` at `+0x00` and the owning
  `Game*` at `+0x0c`.
- The initializer stores `game = g_game_base + 0x74618`, sets render flags
  `0x600000`, then clears bit `0x2` through the game view at `+0x4c`.
- Focused matcher remains exact at 12/12 instructions with 2 clean masked
  operands.
