# ObjectProcTileFloorCornerFast

`0x41a290` is the authored free function
`ObjectProcTileFloorCornerFast(int, cRObject*, char*)` from `ObjectProc.o`,
retained by Android and iOS. It builds a sliced floor tile, selects a corner
through the shared `{3, 2, 0, 1}` table, and clamps its x/z magnitudes to 0.3.

- VC6 symbol: `?ObjectProcTileFloorCornerFast@@YAXHPAUcRObject@@PAD@Z`
- exact Windows match: 55/55 instructions
- masked operands: 10/10 audited
- live callers: twelve ordered world-bank sites
