# update_new_game_menu

First structured scratch for `update_new_game_menu` @ `0x417eb0`.

Match status: 63.94%, 273 target instructions, 265 candidate instructions, 32
masked operands all resolved. Prefix is 41/273. No byte-shaped source.

Recovered relationships:

- menu buttons at `+0x30/+0x34/+0x38/+0x3c/+0x40/+0x44` dispatch postal,
  time trial, challenge, tutorial, help, and back respectively;
- the text-input wakeup also accepts the shared live input confirm edge
  `GameInputOwner.input.pressed_buttons & 0x4000`;
- `replay_attract_bank_cursor` at `+0x00` rotates through `0..4`, but only
  banks `0`, `1`, and `3` probe replay/high-score records;
- record bases `game+0x6ffae8`, `game+0x85c128`, and `game+0x9b8768` are
  0x1fac0-stride persistent record banks, with selected modes `0`, `1`, and
  `4`;
- the menu seeds the same replay-launch scratch as high-score and click-start:
  `game+0x1066be8/+0x1066be9/+0x1066bec/+0x1066bf0`;
- the launch return state is `2` from the new-game attract path and `18` from
  the high-score browser path.

Source-shape note: `destroy_main_menu` itself still matches as a no-arg helper,
but this caller is spelled as a `NewGameMenu` member call because native sets
`ecx = this` before the call.

Residual mismatch: the native replay-attract loop is jump-threaded around the
`0/1/3` bank cases, while this scratch is a straightforward `if/else` loop.
The button dispatch is structurally close; remaining differences are mostly
`g_game_base` reload scheduling.
