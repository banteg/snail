# query_directx_runtime_version

Startup DirectX runtime capability probe at `0x44afc0`.

The probe dynamically loads `DDRAW.DLL`, checks `DirectDrawCreate` and
`DirectDrawCreateEx`, verifies several DirectDraw/DirectDrawSurface interface
queries, checks `DINPUT.DLL` only far enough to confirm `DirectInputCreateA`
exists, probes DirectMusic COM creation, then loads `D3D8.DLL` and
`dpnhpast.dll`.

Scratch result: 100%, 370/370 instructions, with all 57 masked operands
resolved. The final source-shape fix was declaration order for the initialized
DirectDraw locals; VC6 emits the initial zero stores in declaration order while
keeping the same stack slots.
