# build_track_fringe_supertramp_mesh reconstruction notes

`build_track_fringe_supertramp_mesh` creates the generated supertramp fringe
mesh for an attachment path template. It allocates an `Object` into the
template's second `BodBase` slot at `+0x60`, marks it as imported/generated,
then requests four vertices per segment plus two cap vertices and two side
facequads per segment plus one terminal cap face.

Important type notes:

- `Path +0x60` is the same second `BodBase` used by
  `build_track_fringe_mesh`; the generated object pointer is at `+0x84`.
- The source strip mesh lives at `Path +0x24`.
- Each generated row copies source columns `1/0` for the left edge and
  `width_cells - 1 / width_cells` for the right edge, then extrudes the outer
  generated vertices by 0.4 units along the normalized edge direction.
- The terminal cap extrapolates from the last two generated rows, copies those
  extrapolated cap vertices back over the last row's outer vertices, and emits
  a final facequad.

Current focused result:

- match: 22.19%
- target/candidate instructions: 421 / 363
- prefix: 0 / 421
- masked operands: 19 clean, 0 unresolved, 0 mismatched

Remaining gap:

The scratch remains early progress, but the native vector-expression family is
now recovered. The target uses a `0x5c` frame versus the candidate's `0x60`,
keeps `this` in `esi`, the generated object in `ebx`, and centers the row loop
cursor at the row's second vertex Z component. The remaining gap is dominated
by those register/lifetime choices plus terminal-cap and face-store scheduling.

## 2026-07-12 shared fringe source recovery

Android's named `cRPath::BuildFringeSuperTramp` confirms that this builder uses
the same two vector edge extrusions as `BuildFringe`, then extrapolates its two
cap vertices with the same subtract/scale/add operator chain. The scratch now:

- reads sampled vertices directly from the owned `Path::strip_mesh`;
- materializes the proved local-result subtraction and by-value vector
  scale/add operations for both row edges and both terminal cap vertices;
- reuses the row cursor for face emission; and
- writes UV corner `3` before corners `0..2`, matching the Android store family.

This raises the focused candidate from `303` to `363` instructions and the
match from `17.13%` to `22.19%`, with `19` clean masked operands. The modest
fuzzy increase understates the recovery: sixty previously absent instructions
now come from real vector temporaries rather than padding or compiler barriers.
