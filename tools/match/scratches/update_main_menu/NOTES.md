# update_main_menu @ 0x419e00

First scratch for main-menu dispatch. Focused Wibo result:
100.00%, 68/68 instructions, 16 masked operands ok.

- New Game tears down the main menu, sets `frontend_next_state = 2`, and raises
  the shared front-end dirty byte at `+0x30c`.
- Credits does the same with state `14`.
- Exit opens the completion/exit prompt path by saving the previous front-end
  state, copying the exit widget layout y into `CompletionPrompt::prompt_y`,
  setting prompt state `10`, and switching front-end state to `8`.
- Options raises `OptionsMenu::active`, records the previous state, and switches
  to state `6`.
- High Scores switches to state `18` and seeds `HighScoreScreen::mode = 0`.
- Root `+0x30c` is `GamePlayer::redispatch_requested`, while `+0x30d` is the
  high-score-entry/completion-pending byte checked after `complete_subgame`.
- 2026-07-11 owner closure promotes the contiguous root block to
  `NewGameMenu`, `MainMenu`, `StarField`, `OptionsMenu`, and
  `CompletionPrompt`; this remains exact 68/68.
