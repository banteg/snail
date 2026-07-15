# draw_galaxy_line

Exact scratch for the galaxy route line helper at `0x409b00`.

Relationship notes:

- This is a `Galaxy` member used by `update_galaxy` to turn two route points
  into a textured quad through `queue_textured_quad_corners`. Its body does not
  read object fields, so its `ret 0x1c` body is also compatible with a false
  standalone stdcall declaration; both native callsites independently prove
  the authored receiver with `ecx = Galaxy*`.
- The local `Vector3` is a normalized 2D segment with `z = 0`; the perpendicular
  half-width terms then become the four corner points.
- The queued quad uses texture ids `0x99/0x9a` at callsites, flags `0x1000000`,
  UVs `[0,0]..[1,1]`, layer `15`, and blend `0`.

Exact match: 100.00%, 67/67 instructions, with four masked operands audited.

2026-07-12 owner closure: promoting the helper to
`Galaxy::draw_galaxy_line` preserves the exact body while recovering the
receiver setup in `update_galaxy`.

## 2026-07-15 Binary Ninja lifecycle replay

Live readback now preserves the true `Galaxy*` receiver plus the texture,
endpoint, width, and `tColour*` arguments. This removes the false-stdcall
ambiguity from the database while focused matching remains exact at 67/67
with four clean operands.
