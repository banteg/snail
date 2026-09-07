# 2026-09-07 uncurated entry check

A read-only inventory of the open `SnailMail_unwrapped.exe.bndb` found 2,259
Binary Ninja function entries. In the contiguous game/engine range from
`0x401000` through the final curated viewport constructor before `0x44e950`,
790 entries cover all 782 core and platform manifest functions plus eight
uncurated analysis entries. This is an inventory of analysis entries, not an
independent proof of every native function boundary.

Each of the eight extras was checked by addressed disassembly:

| Entry | Observed body |
| --- | --- |
| `0x40a190` | Jump to the bare return at `0x40a1a0` |
| `0x410bf8` | Eight NOP bytes before `0x410c00` |
| `0x411490` | Jump to the bare return at `0x4114a0` |
| `0x4119a0` | Jump to the bare return at `0x4119b0` |
| `0x411da0` | Jump to the bare return at `0x411db0` |
| `0x411dc0` | Jump to the bare return at `0x411dd0` |
| `0x43a2f8` | Eight NOP bytes before `update_movement_flag_emitters` |
| `0x43d228` | Eight NOP bytes before `initialize_subgoldy_ghost` |

These entries reveal no additional substantive game routine to recover within
that range. They were not added as new matches, and no manifest extent, scope,
normalization, or database analysis state was changed. The matching goal stays
within the existing 662 port-relevant functions. Code after this range includes
the separately identified D3DX library bodies; this bounded entry check does
not reclassify or exhaustively audit that later library region.

The inventory can be reproduced from the same database with `bn target list`,
then `bn --target SnailMail_unwrapped.exe.bndb py` to collect each function's
start, name, basic-block endpoints, and block-byte total. Compare starts with
`analysis/symbols/gameplay-functions.json`, and use `bn disasm` on the eight
addresses above.
