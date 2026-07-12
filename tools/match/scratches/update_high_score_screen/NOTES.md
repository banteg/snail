# update_high_score_screen

First structured scratch for `update_high_score_screen` @ `0x417260`.

Match status: 67.65%, 205 target instructions, 203 candidate instructions, 29
masked operands all resolved. No fakematching.

Recovered relationships:

- `HighScore` has separate row-widget arrays: editable name rows at
  `+0x7c` and replay-launch rows at `+0xcc`;
- `SubSolution` is the 0x1fac0-stride persistent replay/high-score record
  used by completion, high-score browsing, and replay launch;
- high-score replay launch sets `game+0x1066be8/+0x1066be9/+0x1066bec/+0x1066bf0`
  to active, frontend-origin, selected record, and return state `18`;
- the selected record's `+0x2c` value feeds `game+0x74658`, matching the
  subgame launch mode handoff seen in menu and completion paths.

2026-07-10 owner closure:

- The former `HighScoreGameView` crossed two real owners. Root
  `+0x1a4/+0x1b8/+0x30c` are `GamePlayer[0]`'s 20-byte player name, front-end
  state, and redispatch byte. Root `+0x74658/+0x6ffae0/+0x1066be8...` are all
  fields of the embedded `SubgameRuntime` and its owned `SubHighScore`.
- The footer fields are now named from their actual labels and shortcuts:
  `+0x24` is Cancel/Escape and `+0x28` is Submit/Enter. Submit finalizes the
  editable row; Cancel calls `cRSubHighScore::MiniDelete(int)` and exits.
- The ownership rewrite is codegen-neutral at the current 67.65% baseline.

2026-07-11 cRHighScore ownership: Android and iOS name this lifecycle method
`cRHighScore::AI()`; the shared `HighScore` owner replaces the provisional
screen shell without changing the honest 67.65% baseline.

2026-07-12 exact source and row-bank closure:

- Re-reading the selected name widget for each destination matches native's
  actual borrowed-handle lifetime; no widget, root, or persistent record is
  retained across the three string copies.
- The replay loop similarly reloads `g_game_base` after callbacks instead of
  keeping a root pointer live across teardown. The Back and replay-launch paths
  use separate root loads for the front-end state and redispatch byte, matching
  their independently owned fields.
- The bank toggle is the native two-case switch. Together these source changes
  raise the function from 67.65% (`203/205`, prefix 0, 29 clean operands) to
  proof-grade 100.00% (`205/205`, prefix 205, 40 clean operands).
- Initializer indexing proves five ten-handle banks at `+0x2c`, `+0x54`,
  `+0x7c`, `+0xa4`, and `+0xcc`. The former `name_row_widgets[20]` plus
  `replay_row_widgets[1]` view hid three banks and incorrectly truncated the
  known controller storage at `+0xd0`; replay slot nine proves it through
  `+0xf4`. The final `0x14` bytes before TipManager remain explicitly unknown.
