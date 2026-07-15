# initialize_direct3d_renderer_defaults @ 0x411630

Initializes the process renderer before Direct3D device creation.

- The contiguous globals at `0x4b7770` and `0x4b7780` are recovered as two
  Win32 `RECT` values: captured client bounds and uncaptured clip bounds. Both
  start as the integer-authored 640x480 view; the latter is expanded through
  `AdjustWindowRectEx` with the one-use style value `0x06cf0000`.
- Clears the renderer's `Direct3D8*`, device pointer, multisample state, and
  initialized byte, while seeding 640x480 requested dimensions, depth-stencil
  format `0x50`, and creation flags `0x20`.
- The dwords at `+0xbcb0/+0xbcb4` remain explicitly unknown: this function
  writes `0` and `0x17`, but no other native consumer proves their semantics.
  Their shared owner now records them as individual typed dwords rather than
  one anonymous eight-byte padding range.

Focused match is exact: 38/38 instructions with all 15 masked operands clean.

## 2026-07-15 Binary Ninja replay

The live database now types this member as
`void __thiscall(Direct3DRenderer*)` and renders every `+0xbb90..+0xbcbc`
write through the canonical receiver. `g_direct3d_renderer` owns one complete
0xbcc0-byte value; its device pointer is not recreated as a standalone global.
