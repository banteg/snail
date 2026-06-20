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
- 2026-06-16 Player consolidation check: including shared `player.h` and using
  `Player::game` / `Player::visible_life_stock` kept the instruction stream at
  14/14 but changed the switch-table relocation audit from `3 ok` to
  `2 ok, 1 mismatch` (`$L395` instead of
  `initialize_subgoldy_death_jump_table`). Keep the local `Player` shell until
  that symbol-shape issue has a targeted fix.
- 2026-06-20 Player ABI cleanup: the local method now returns `int`, matching
  `player.h` and the IDA decompiler's carried `result`. The source keeps the
  local field shell for the jump-table relocation reason above, and focused
  Wibo stays exact at `100.00%`, `14/14`, with `3 ok` masked operands.
