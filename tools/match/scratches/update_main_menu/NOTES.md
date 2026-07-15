# update_main_menu @ 0x419e00

First scratch for main-menu dispatch. Focused Wibo result:
100.00%, 68/68 instructions, 16 masked operands ok.

- New Game tears down the main menu, sets `frontend_next_state = 2`, and raises
  the shared front-end dirty byte at `+0x30c`.
- Credits does the same with state `14`.
- Exit opens the completion/exit prompt path by saving the previous front-end
  state, copying the exit widget layout y into `Exit::prompt_y`,
  setting prompt state `10`, and switching front-end state to `8`.
- Options raises `Options::active`, records the previous state, and switches
  to state `6`.
- High Scores switches to state `18` and seeds `HighScore::mode = 0`.
- Root `+0x30c` is `GamePlayer::redispatch_requested`, while `+0x30d` is the
  high-score-entry/completion-pending byte checked after `complete_subgame`.
- 2026-07-11 owner closure promotes the contiguous root block to
  `Intro`, `MainMenu`, `StarManager`, `Options`, and
  `Exit`; this remains exact 68/68.

2026-07-13 canonical root graph: New Game, Credits, Exit, Options, and High
Scores now reload the typed `GameRoot*` global and follow the owned player,
`Exit`, `Options`, and `HighScore` members. Native's callback-separated root
reloads are preserved; output remains exact at 68/68 with all 16 operands
clean.

2026-07-15 live analysis replay: Binary Ninja now carries the exact 0x18-byte
`MainMenu` receiver and the adjacent `Options`/`Exit` root fields. The tracked
artifact therefore preserves the authored menu receiver while naming both
outbound state owners, with no raw root offsets or synthetic cross-owner view.
