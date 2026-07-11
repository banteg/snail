# update_high_score_screen

First structured scratch for `update_high_score_screen` @ `0x417260`.

Match status: 67.65%, 205 target instructions, 203 candidate instructions, 29
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

2026-07-10 owner closure:

- The former `HighScoreGameView` crossed two real owners. Root
  `+0x1a4/+0x1b8/+0x30c` are `GamePlayer[0]`'s 20-byte player name, front-end
  state, and redispatch byte. Root `+0x74658/+0x6ffae0/+0x1066be8...` are all
  fields of the embedded `SubgameRuntime` and its owned `HighScoreBank`.
- The footer fields are now named from their actual labels and shortcuts:
  `+0x24` is Cancel/Escape and `+0x28` is Submit/Enter. Submit finalizes the
  editable row; Cancel calls `cRSubHighScore::MiniDelete(int)` and exits.
- The ownership rewrite is codegen-neutral at the current 67.65% baseline.

Residual mismatch: the native name-submit branch reloads the selected row widget
between string copies and keeps only one stack local, while this scratch still
saves an extra callee register and materializes the active bank pointer earlier.
