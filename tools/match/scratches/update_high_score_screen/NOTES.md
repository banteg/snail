# update_high_score_screen

First structured scratch for `update_high_score_screen` @ `0x417260`.

Match status: 64.88%, 205 target instructions, 205 candidate instructions, 28
masked operands all resolved. No fakematching.

Recovered relationships:

- `HighScoreScreen` has separate row-widget arrays: editable name rows at
  `+0x7c` and replay-launch rows at `+0xcc`;
- `HighScoreRecord` is the 0x1fac0-stride persistent replay/high-score record
  used by completion, high-score browsing, and replay launch;
- high-score replay launch sets `game+0x1066be8/+0x1066be9/+0x1066bec/+0x1066bf0`
  to active, frontend-origin, selected record, and return state `18`;
- the selected record's `+0x2c` value feeds `game+0x74658`, matching the
  subgame launch mode handoff seen in menu and completion paths.

Naming caveat: this keeps the game view and high-score record local for now.
The replay-launch scratch names are shared conceptually with click-start and
new-game menu, but should only move to a common `Game` view once another caller
confirms the same field semantics.

Residual mismatch: the native name-submit branch reloads the selected row widget
between string copies and keeps only one stack local, while this scratch still
saves an extra callee register and materializes the active bank pointer earlier.
