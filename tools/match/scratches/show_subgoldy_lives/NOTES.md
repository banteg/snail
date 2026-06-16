# show_subgoldy_lives

Current match: 100.00%, 23/23 instructions, with two clean masked operands.

Type cleanup: the raw `game + 0x35bb98` loop is now represented as
`Game::life_stock_widgets[9]`.

Evidence:

- `initialize_subgame` allocates and initializes nine sprite-button widgets at
  `game+0x35bb98..0x35bbb8`.
- `destroy_subgame` kills the same nine-widget range.
- `show_subgoldy_lives` only toggles the first `Player::visible_life_stock`
  entries visible and hides the rest.

This also consolidates the adjacent gameplay score/life HUD widget fields into
the shared scratch-local `game.h` view instead of repeating local `Game`
definitions.

Source-shape note: native keeps an absolute `Game` byte offset in the loop
induction register, so the scratch derives the start/end offsets from the
`Game::life_stock_widgets` member expression but still performs a byte-offset
load from `game`. A direct pointer iterator over the array regressed to 40% by
changing register ownership and loop shape.
