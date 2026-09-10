# Exact match

## 2026-09-11 complete inline-table proof

The unchanged C++ source now passes **100% normalized and encoded-body proof**:
19 code instructions, 32 compared table bytes, and 3 clean references
at identical instruction and byte positions. This corrects table boundary
recognition, not source reconstruction. The obsolete END override is removed so the target includes alignment and the complete native table. Earlier scores below are historical.

The [boundary report](../../inline-table-boundaries-20260911.md) and
[receipt](../../inline-table-boundaries-20260911.json) preserve source/config
identities, complete range accounting, table destinations, positional reference
audits, and encoded-body hashes.

`set_subgame_features` seeds `game->runtime_flags` for the current mode before
runtime track population. If a selected-level record override is active, it
copies the record's flag word at `+0x38`; otherwise the native presets are:

- modes `0` and `1`: `0xf5cfff`
- mode `4`: `0x75cfff`
- mode `7`: `0xe4cfff`
- all other modes: `0x600484`

The exact source shape keeps the native pre-switch seed `0x484`, then shares
the `0x600484` default assignment across the bounded switch. The scratch uses
`END=0x435e3c` because bytes after the final `ret` are the native jump table
data for this switch, not executable function body.

## 2026-07-14 game-wide feature owner

The native whole-word writes now use `SubgameRuntimeFlagPreset` names instead
of anonymous mode masks. `SubgameRuntimeFlag` separately names only bits with
proved Windows consumers; preset-only bits `0x040000`, `0x100000`, and
`0x200000` remain intentionally opaque. Focused output remains exact at
100.00%, 19/19 instructions, full prefix, and three clean operands.

## 2026-07-18 selected-record owner replay

The focused analyzer replay now owns the complete exact boundary used here:
`cRSubGame::level_mode`, `runtime_flags`, the selected-record activation
byte, and the borrowed `SubSolution* selected_level_record`. This preserves the
native distinction between the embedded working record and the optional
borrowed replay/level record while keeping the scratch exact at 19/19 with
three clean operands.

## 2026-07-26 cross-port result ABI

Android and iOS both preserve the exact `cRSubGame::SetFeatures()` symbol and
decompile it as `void`. The Windows caller in
`cRSubGame::GenerateLevel(int)` also discards EAX before the next independent
call. Removing the synthetic record/mode returns leaves the VC6 output
byte-identical at 19/19 instructions: the apparent Windows result was only the
last value naturally loaded into EAX.
