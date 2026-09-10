# ObjectProcFringe

## 2026-09-11 complete inline-table proof

The unchanged C++ source now passes **100% normalized and encoded-body proof**:
368 code instructions, 44 compared table bytes, and 63 clean references
at identical instruction and byte positions. This corrects table boundary
recognition, not source reconstruction. Earlier scores below are historical.

The [boundary report](../../inline-table-boundaries-20260911.md) and
[receipt](../../inline-table-boundaries-20260911.json) preserve source/config
identities, complete range accounting, table destinations, positional reference
audits, and encoded-body hashes.

`0x41a4d0` is the authored free function
`ObjectProcFringe(cRObject*, int, int, int, int, char*)` from `ObjectProc.o`,
retained by Android and iOS. It builds, rotates, offsets, and edge-adjusts one
textured fringe quad in the nested world-bank initializer.

- VC6 symbol: `?ObjectProcFringe@@YAXPAUcRObject@@HHHHPAD@Z`
- exact Windows match: 367/367 instructions
- masked operands: 63/63 audited
- live caller: `initialize_game_assets_and_world`
