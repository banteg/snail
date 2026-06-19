# `build_camera_view_matrix` recovery notes

Target: `build_camera_view_matrix @ 0x451ad9` (`stdcall`, `ret 0x10`).

This is the renderer view-matrix helper called by `render_camera`. It builds a
D3D-style look-at matrix from camera eye, target, and up vectors:

- `forward = normalize(eye - target)`;
- `right = normalize(cross(forward, up))`;
- corrected up is `cross(forward, right)`;
- the translation row stores the negative dot products against `eye`.

The two normalizations call the real DirectX vector-normalize thunk at
`0x44ebc1` (`D3DXVec3Normalize`, a jump through `dword [0x4ace54]`).

`scratch.conf` pins `END=0x451c21` because this is the final curated gameplay
symbol and the matcher otherwise has no following manifest symbol to bound the
native function extent.

The current scratch is semantic rather than proof-grade. Native keeps an
`ebp` frame and x87-heavy D3DX scheduling, while the standard `msvc6.5 /O2 /G5
/W3` scratch compiles as an FPO function with different stack addressing and
constant stores. This is consistent with the existing
`initialize_translation_matrix` scratch: these late matrix helpers are D3DX8
static-library code, not ordinary game translation units.
