# draw_galaxy_line

Exact scratch for the galaxy route line helper at `0x409b00`.

Relationship notes:

- This is a `Galaxy` member used by `update_galaxy` to turn two route points
  into a textured quad through `queue_textured_quad_corners`. Its body does not
  read object fields, so its `ret 0x1c` body is also compatible with a false
  standalone stdcall declaration; both native callsites independently prove
  the authored receiver with `ecx = cRGalaxy*`.
- The local `Vector3` is a normalized 2D segment with `z = 0`; the perpendicular
  half-width terms then become the four corner points.
- The queued quad uses texture ids `0x99/0x9a` at callsites, flags `0x1000000`,
  UVs `[0,0]..[1,1]`, layer `15`, and blend `0`.

Exact match: 100.00%, 67/67 instructions, with four masked operands audited.

2026-07-12 owner closure: promoting the helper to
`cRGalaxy::Line` preserves the exact body while recovering the
receiver setup in `update_galaxy`.

## 2026-07-15 Binary Ninja lifecycle replay

Live readback preserves the true `cRGalaxy*` receiver plus the texture,
endpoint, width, and `tColour*` arguments. This removes the false-stdcall
ambiguity from the database while focused matching remains exact at 67/67
with four clean operands.

## 2026-07-26 Android owner and void ABI

The unstripped Android build preserves the complete helper as
`cRGalaxy::Line(int, float, float, float, float, float, tColour&)`. Its body
normalizes the same segment, derives the same perpendicular half-width, calls
the long `OSDPrintUV` overload, and returns explicitly without a value.

Every Windows callsite also discards EAX. Declaring the Windows member `void`
therefore recovers the authored contract without changing its exact 67/67
instruction body or four clean operands. The nested Windows queue helper still
has its own platform-specific integer queue-offset ABI; the value merely
survives incidentally through this void member.

## 2026-08-09 primary cRGalaxy ownership

The matcher now emits the exact Android-authored surface
`cRGalaxy::Line(int, float, float, float, float, float, tColour&)` and binds
`?Line@cRGalaxy@@QAEXHMMMMMAAUtColour@@@Z`. The reference is the same pointer
ABI already proven in the Windows body and both Windows receiver-bearing
callsites. Focused output remains exact at 67/67 with all four operands clean.
