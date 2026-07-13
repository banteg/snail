# initialize_new_game_menu @ 0x417bc0

New Game submenu initializer, using the same front-end music/backdrop setup as
the main and help menu initializers.

- Full Wibo result: 2026-06-18, 100.00%, 182/182 instructions, 48 masked
  operands ok.
- Hides `GameRoot::star_manager`, loads `Menubg.txt`, centers the backdrop, and
  seeds `GameRoot::render_skip_countdown = 2`.
- Allocates Tutorial, Postal Mode, Time Trial, Challenge Mode, Help, and Back
  widgets into the promoted `Intro` slots.
- If the tutorial has not started yet, disables Postal/Time Trial/Challenge by
  OR-ing widget flag `0x8000`.
- 2026-07-11 owner closure removes the synthetic cross-root view; the root menu
  block and render countdown remain exact at 182/182.

## 2026-07-12 authored cRIntro ownership

The symbol-bearing iOS `cRIntro::Init()` body independently performs the same
fade, star hide, main-menu music, `Menubg.txt` backdrop, centered border setup,
and mode/help/back widget construction. Its literal sequence names Tutorial,
Postal Adventure, Pro-Challenge, Time Trial, Challenge Mode, Help, and Back.
Windows omits the mobile-only Pro-Challenge pointer and closes its exact
root-owned `Intro` at 0x48 bytes. Promoting the synthetic `NewGameMenu` owner to
`Intro` preserves the exact 182/182 body and all 48 clean operands.

## 2026-07-13 root-owner cleanup

The star field, landscape bank, backdrop, border pool, and render-skip
countdown now use canonical `GameRoot` members. Removing the screen-local
`NewGameBorderManager` view keeps the initializer exact at 182/182 with all 48
operands clean.
