# build_track_fringe_supertramp_mesh reconstruction notes

`build_track_fringe_supertramp_mesh` creates the generated supertramp fringe
mesh for an attachment path template. It allocates an `Object` into the
template's second `BodBase` slot at `+0x60`, marks it as imported/generated,
then requests four vertices per segment plus two cap vertices and two side
facequads per segment plus one terminal cap face.

Important type notes:

- `AttachmentPathTemplate +0x60` is the same second `BodBase` used by
  `build_track_fringe_mesh`; the generated object pointer is at `+0x84`.
- The source strip mesh lives at `AttachmentPathTemplate +0x24`.
- Each generated row copies source columns `1/0` for the left edge and
  `width_cells - 1 / width_cells` for the right edge, then extrudes the outer
  generated vertices by 0.4 units along the normalized edge direction.
- The terminal cap extrapolates from the last two generated rows, copies those
  extrapolated cap vertices back over the last row's outer vertices, and emits
  a final facequad.

Current focused result:

- match: 17.13%
- target/candidate instructions: 421 / 303
- prefix: 0 / 421
- masked operands: 17 clean, 0 unresolved, 0 mismatched

Remaining gap:

The scratch is behaviorally useful but still early progress. The target keeps a
larger stack frame, uses `esi` for `this`, keeps the generated object in `ebx`,
and centers the row loop cursor at the row's second vertex Z component. The
terminal cap also spills intermediate x87 values into the larger frame. The
current source leaves those compiler-shape differences visible.
