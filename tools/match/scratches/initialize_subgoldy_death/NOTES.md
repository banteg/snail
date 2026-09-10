# initialize_subgoldy_death

## 2026-09-11 complete inline-table proof

The unchanged C++ source now passes **100% normalized and encoded-body proof**:
15 code instructions, 32 compared table bytes, and 3 clean references
at identical instruction and byte positions. This corrects table boundary
recognition, not source reconstruction. The obsolete END override is removed so the target includes alignment and the complete native table. Earlier scores below are historical.

The [boundary report](../../inline-table-boundaries-20260911.md) and
[receipt](../../inline-table-boundaries-20260911.json) preserve source/config
identities, complete range accounting, table destinations, positional reference
audits, and encoded-body hashes.

- Exact match: 100.00%, 14/14 instructions.
- Uses shared `cRSubGame::level_mode`, `Player::game`, and
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
- 2026-07-16 Player ABI correction: both direct callers discard EAX and every
  branch only tail-forwards the resurrect selector residue. Natural void calls
  plus source-level returns preserve the exact `14/14` instruction stream and
  all three clean operands, so `player.h` and both decompilers no longer expose
  a synthetic integer result.
- 2026-06-21 subgame owner cleanup: the compact local `Game` view was replaced
  with a `cRSubGame` cast at the existing `Player::game` pointer. Focused
  Wibo remains exact at `100.00%`, `14/14`, with `3` clean masked operands.
- 2026-08-09 selector closure: the checked-in BN and IDA exports preserve the
  exact mode switch, and the March 15 CDB session observed both Postal arms at
  their native calls: `0x446e59` passes `0` with spare lives and `0x446e51`
  passes `1` at zero lives. Hazard death and a floor-gap fall enter through
  different callers, but both reach this same selector. Android
  `cRSubGoldy::DeathInit()` independently keeps the same Postal life test,
  Challenge/Time Trial final-loss cases, tutorial respawn case, and calls to
  `RessurectInit(int)`.
