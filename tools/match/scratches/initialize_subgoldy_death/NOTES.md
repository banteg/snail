# initialize_subgoldy_death

- Exact match: 100.00%, 14/14 instructions.
- Uses typed `Game::level_mode`, `Player::game`, and `Player::visible_life_stock`
  fields, matching the exact resurrect helpers without raw-offset glue.
- `END=0x446e5f` is required because the native `ret` at `0x446e5e` is followed
  by a `nop` and the switch jump table beginning at `0x446e60`; without the
  explicit extent, the matcher disassembles table bytes as instructions.
- Semantics: Postal mode (`level_mode == 0`) sends the last-life path to
  `initialize_subgoldy_resurrect(1)` and non-final deaths to
  `initialize_subgoldy_resurrect(0)`. Challenge and Time Trial failures are
  final-loss paths, while tutorial mode uses the non-final resurrect lane.
