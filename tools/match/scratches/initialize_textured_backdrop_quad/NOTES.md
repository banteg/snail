# ObjectProcTileFast

`0x41a0b0` is the authored free function
`ObjectProcTileFast(cRObject*, char*, float)` from `ObjectProc.o`, retained by
Android and iOS. It creates the three ramp tiles and the Universe hole quad.

- VC6 symbol: `?ObjectProcTileFast@@YAXPAUcRObject@@PADM@Z`
- exact Windows match: 57/57 instructions
- masked operands: 6/6 audited
- live callers: four sites in `initialize_game_assets_and_world`
