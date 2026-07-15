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

2026-07-15 SDK ownership:

- VC6's bundled `<windows.h>` / `<ddraw.h>` now own `IDirectDraw`,
  `IDirectDrawSurface`, `DDSURFACEDESC`, `GUID`/`IID`/`CLSID`, module handles,
  imported Win32/COM APIs, and the DirectDraw constants used by the primary
  surface probe.
- Queried DX2/DX3/DX4/DX7 and DirectMusic objects are typed as their authentic
  `IUnknown` base because this helper only calls `Release`; the bundled SDK
  predates the later full interface declarations, so no replacement interfaces
  are invented.
- The 0x6c-byte raw word array is recovered as `DDSURFACEDESC` with `DDSD_CAPS`
  and `DDSCAPS_PRIMARYSURFACE` fields. The exact zeroing loop remains visible
  and still lowers to native's 27-dword `rep stosd`.

Removing three scratch vtables and seven approximate API declarations is fully
codegen-neutral: the object remains exact at 370/370 instructions with 57 clean
masked operands, and the type audit no longer reports the synthetic DirectDraw,
DirectDrawSurface, or DirectMusic owners.
