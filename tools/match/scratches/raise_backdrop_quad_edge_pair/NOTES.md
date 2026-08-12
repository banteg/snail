# ObjectProcTileFastRamp

`0x41a170` is the authored free function
`ObjectProcTileFastRamp(int, cRObject*)` from `ObjectProc.o`, retained by
Android and iOS. Selectors -1, 0, and 1 raise the intended ramp edge pair.

- VC6 symbol: `?ObjectProcTileFastRamp@@YAXHPAUcRObject@@@Z`
- exact Windows match: 19/19 instructions
- masked operands: 4/4 audited
- live callers: three sites in `initialize_game_assets_and_world`
