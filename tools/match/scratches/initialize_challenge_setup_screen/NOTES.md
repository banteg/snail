# initialize_challenge_setup_screen @ 0x415f50

First structured scratch for the challenge mode setup initializer.

- Captures the mouse and reloads the selected front-end level path before
  building controls.
- Only mode `1` builds the challenge difficulty/speed sliders, play, replay,
  and back widgets. Other modes return immediately.
- Uses the widget slots proven by `destroy_challenge_setup_screen`.
- Corrected `game+0xa874` to inline `SubTracks` storage. The
  loader call is a member call with mode/index arguments, not a three-argument
  free helper with a path buffer.
- The former scalar transcription matched 167/167 instructions; the authored
  void contract below supersedes that proof-grade classification.

2026-07-11 ownership closure: `GUI::game` is a borrowed
`SubgameRuntime*`, not a scratch-local setup view. The selected mode/index and
inline `SubTracks` owner belongs to that runtime, while replay availability
comes from its owned `SubHighScore::survival_pending_record`. Focused Wibo
retained the former scalar exact baseline before the return-contract audit.

2026-07-11 cRGUI ownership: Android and iOS name this exact owner method
`cRGUI::Init()`. Android independently preserves the borrowed game pointer at
+0x00 and the same widget fields through +0x24. The Windows 0x28-byte layout
also closes exactly between the salt-frequency dword and the `Help` owner.

2026-07-13 root-owner cleanup: player-zero mouse capture and all five widget
allocations now use the canonical `GameRoot` graph. The borrowed
`SubgameRuntime* game` remains screen-local state.

## 2026-07-14 authored void contract

Android `cRGUI::Init()` reaches one side-effect-only epilogue, and the sole
Windows caller in `initialize_subgame` discards EAX. The shared initializer is
therefore `void`; Binary Ninja applied and read back that prototype directly.
The honest focused result is 96.41%, 167/167 instructions, prefix 14, with all
36 operands clean. The lost sequence score is register allocation formerly
anchored by a synthetic return. `cRGUI::AI()` remains `int`: `update_subgame`
consumes its semantic 0/1/3 state result.
