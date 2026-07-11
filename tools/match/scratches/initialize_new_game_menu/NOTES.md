# initialize_new_game_menu @ 0x417bc0

New Game submenu initializer, using the same front-end music/backdrop setup as
the main and help menu initializers.

- Full Wibo result: 2026-06-18, 100.00%, 182/182 instructions, 48 masked
  operands ok.
- Hides `GameRoot::star_manager`, loads `Menubg.txt`, centers the backdrop, and
  seeds `GameRoot::render_skip_countdown = 2`.
- Allocates Tutorial, Postal Mode, Time Trial, Challenge Mode, Help, and Back
  widgets into the promoted `NewGameMenu` slots.
- If the tutorial has not started yet, disables Postal/Time Trial/Challenge by
  OR-ing widget flag `0x8000`.
- 2026-07-11 owner closure removes the synthetic cross-root view; the root menu
  block and render countdown remain exact at 182/182.
