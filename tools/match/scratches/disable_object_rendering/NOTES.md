# ObjectProcNull

`0x41a0a0` is the authored free function `ObjectProcNull(cRObject*)` from
`ObjectProc.o`, retained under the same name and owner by Android and iOS. It
sets the render-suppression flag on the two path fringe objects created during
world initialization.

- VC6 symbol: `?ObjectProcNull@@YAXPAUcRObject@@@Z`
- exact Windows match: 3/3 instructions
- live callers: two sites in `initialize_game_assets_and_world`
