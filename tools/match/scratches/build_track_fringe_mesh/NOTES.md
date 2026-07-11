# build_track_fringe_mesh reconstruction notes

`build_track_fringe_mesh` creates the generated side/fringe strip mesh for an
attachment path template. It allocates an `Object` into the template's second
`BodBase` slot at `+0x60`, copies the current track skirt colour into that BOD,
requests four vertices and two facequads per segment, extrudes the outer edge by
0.4 units along the normalized edge direction, optionally clamps X by side, and
builds the two textured facequads for each segment.

Current focused result:

- match: 42.07%
- target/candidate instructions: 318 / 281
- prefix: 0 / 318
- masked operands: 17 clean, 0 unresolved, 0 mismatched

Important type notes:

- `Path +0x60` is a second `BodBase`, corroborating the
  `initialize_path_template_record_pair` constructor and this mesh builder.
- The source mesh for sampled track vertices remains the first BOD/object slot
  at `Path +0x24`; the generated mesh lives in the second
  BOD's `object` field at `+0x84`.
- Non-mirrored templates use source columns `1/0` for the first edge and
  `width_cells - 1 / width_cells` for the opposite edge; mirrored templates swap
  those pairs.
- `clamp_side == -1.0f` clamps positive generated X values to zero; values other
  than `1.0f` clamp negative generated X values to zero.

Remaining gap:

The scratch is behaviorally useful but still early progress. The target keeps a
larger stack frame and uses a cursor centered on the generated row's second
vertex Z component, which changes many addressing modes and x87 spill slots.
The facequad loop also schedules texture lookups and UV stores differently. The
current source leaves those compiler-shape differences visible.
