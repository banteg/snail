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

2026-06-18 field promotion:

- Promoted the raw owner slots to `CompletionGameView::options_menu`,
  `exit_prompt`, `subgame_resume_requested`, `subgame_resume_state`,
  `replay_launch_from_frontend`, and `ordinary_rebuild_selector`.
- The fielded source remains an exact 55/55 match, so these names are not just
  decompiler cosmetics.
