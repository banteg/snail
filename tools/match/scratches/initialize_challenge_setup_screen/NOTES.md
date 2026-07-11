# initialize_challenge_setup_screen @ 0x415f50

First structured scratch for the challenge mode setup initializer.

- Captures the mouse and reloads the selected front-end level path before
  building controls.
- Only mode `1` builds the challenge difficulty/speed sliders, play, replay,
  and back widgets. Other modes return `mode - 1`.
- Uses the widget slots proven by `destroy_challenge_setup_screen`.
- Corrected `game+0xa874` to inline `SubTracks` storage. The
  loader call is a member call with mode/index arguments, not a three-argument
  free helper with a path buffer.
- Full Wibo result: 2026-06-18, 100.00%, 167/167 instructions, 37 masked
  operands ok.

2026-07-11 ownership closure: `GUI::game` is a borrowed
`SubgameRuntime*`, not a scratch-local setup view. The selected mode/index and
inline `SubTracks` owner belongs to that runtime, while replay availability
comes from its owned `SubHighScore::survival_pending_record`. Focused Wibo
remains exact at 167/167 instructions with 37 clean masked operands.

2026-07-11 cRGUI ownership: Android and iOS name this exact owner method
`cRGUI::Init()`. Android independently preserves the borrowed game pointer at
+0x00 and the same widget fields through +0x24. The Windows 0x28-byte layout
also closes exactly between the salt-frequency dword and the `Help` owner.
