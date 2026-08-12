# ObjectProcLandScapeUpdate

`0x41a360` is the authored free function
`ObjectProcLandScapeUpdate(cRObject*, float, float, cRTexture*, bool)` from
`ObjectProc.o`, retained by Android and iOS. It samples retained TGA pixels,
averages RGB, optionally cubes the value, and writes scaled vertex heights for
`cRFace::AI`.

- VC6 symbol: `?ObjectProcLandScapeUpdate@@YAXPAUcRObject@@MMPAUcRTexture@@_N@Z`
- semantic-complete Windows result: 60.36%, 113 candidate / 109 target instructions
- masked operands: 13/13 audited
- residual: compiler-shaped stack/register scheduling; no semantic gap known
- live caller: `cRFace::AI`
