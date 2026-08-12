# ObjectProcFringe

`0x41a4d0` is the authored free function
`ObjectProcFringe(cRObject*, int, int, int, int, char*)` from `ObjectProc.o`,
retained by Android and iOS. It builds, rotates, offsets, and edge-adjusts one
textured fringe quad in the nested world-bank initializer.

- VC6 symbol: `?ObjectProcFringe@@YAXPAUcRObject@@HHHHPAD@Z`
- exact Windows match: 367/367 instructions
- masked operands: 63/63 audited
- live caller: `initialize_game_assets_and_world`
