# update_pause_menu @ 0x4407a0

First scratch for the pause-menu button dispatcher.

- Options clears its click bit, captures the current frontend state into the
  options-menu owner at `game+0x4f388`, clears byte `+0x4f38c`, and switches
  the frontend state to `6`.
- Resume clears its click bit, tears down the pause menu, writes the subgame
  resume lanes at `game+0x74654` and `game+0x74620`.
- End Game clears its click bit, seeds the exit prompt at `game+0x4f3ac`,
  preserves the previous frontend state at `+0x4f3b4`, sets
  `ordinary_rebuild_selector` at `+0x12e55e0`, and switches the frontend state
  to `8`.
- Focused Wibo result: 2026-06-18, 100.00%, 55/55 instructions, masked
  operands 10 ok.

2026-06-18 field promotion, superseded by the root closure below:

- Promoted the raw owner slots for options, exit-prompt, resume, replay, and
  rebuild state.
- The fielded source remains an exact 55/55 match, so these names are not just
  decompiler cosmetics.

2026-07-11 owner closure: those lanes now use their actual owners:
`GameRoot::options`, `GameRoot::exit_controller`, and
`GameRoot::subgame.{resume_requested,subgame_state,replay_launch_from_frontend,
subgame_rebuild_selector}`. The duplicate `CompletionGameView` is gone and the
function remains exact 55/55.

2026-07-14 authored-owner and return closure: leaked iOS symbols identify the
method as `cRSubPause::AI()` in `SubGame.o`; Android consumes the same three
widget slots on a 0x0c-byte owner and exits without constructing a stable
result. The Windows source now uses the embedded `SubPause` at
`SubgameRuntime +0x14` and an honest `void` contract instead of returning
path-dependent incidental pointers. It remains exact at 55/55 instructions
with all ten operands clean.

The transactional Binary Ninja replay imports `SubPause` at size 0x0c,
embeds it at `SubgameRuntime +0x14`, and reads all three Windows functions back
as `void __thiscall(SubPause*)`. A second filtered replay reports no
non-idempotent mutation; only the six already-known pinned `Game*` owner
prototypes remain deferred.
