# ObjectProcTileFloorFast

`0x41a1c0` is the authored free function
`ObjectProcTileFloorFast(cRObject*, char*, float)` from `ObjectProc.o`,
retained by Android and iOS. It builds one horizontally sliced World00 floor
quad and is also the shared constructor for corner tiles.

- VC6 symbol: `?ObjectProcTileFloorFast@@YAXPAUcRObject@@PADM@Z`
- exact Windows match: 61/61 instructions
- masked operands: 7/7 audited
- live callers: three world-bank sites plus `ObjectProcTileFloorCornerFast`
