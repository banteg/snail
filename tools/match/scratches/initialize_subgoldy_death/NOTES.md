# initialize_subgoldy_death

- Exact match: 100.00%, 14/14 instructions.
- Uses shared `SubgameRuntime::level_mode`, `Player::game`, and
  `Player::visible_life_stock` fields, matching the exact resurrect helpers
  without raw-offset glue.
- `END=0x446e5f` is required because the native `ret` at `0x446e5e` is followed
  by a `nop` and the switch jump table beginning at `0x446e60`; without the
  explicit extent, the matcher disassembles table bytes as instructions.
- Semantics: Postal mode (`level_mode == 0`) sends the last-life path to
  `initialize_subgoldy_resurrect(1)` and non-final deaths to
  `initialize_subgoldy_resurrect(0)`. Challenge and Time Trial failures are
  final-loss paths, while tutorial mode uses the non-final resurrect lane.
- 2026-06-20 Player header consolidation: the current shared `player.h`
  declaration preserves the exact instruction stream and switch-table audit
  (`100.00%`, `14/14`, `3 ok / 0`), so this scratch no longer carries a compact
  local `Player` shell.
- 2026-06-20 Player ABI cleanup: the local method now returns `int`, matching
  `player.h` and the IDA decompiler's carried `result`. Focused Wibo stays
  exact at `100.00%`, `14/14`, with `3 ok` masked operands.
- 2026-06-21 subgame owner cleanup: the compact local `Game` view was replaced
  with a `SubgameRuntime` cast at the existing `Player::game` pointer. Focused
  Wibo remains exact at `100.00%`, `14/14`, with `3` clean masked operands.
