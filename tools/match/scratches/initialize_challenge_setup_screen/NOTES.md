# initialize_challenge_setup_screen @ 0x415f50

First structured scratch for the challenge mode setup initializer.

- Captures the mouse and reloads the selected front-end level path before
  building controls.
- Only mode `1` builds the challenge difficulty/speed sliders, play, replay,
  and back widgets. Other modes return `mode - 1`.
- Uses the widget slots proven by `destroy_challenge_setup_screen`.
- Corrected `game+0xa874` to inline `LevelDefinitionLoader` storage. The
  loader call is a member call with mode/index arguments, not a three-argument
  free helper with a path buffer.
- Full Wibo result: 2026-06-18, 100.00%, 167/167 instructions, 37 masked
  operands ok.
