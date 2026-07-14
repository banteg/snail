# build_track_fringe_supertramp_mesh reconstruction notes

`build_track_fringe_supertramp_mesh` creates the generated supertramp fringe
mesh for an attachment path template. It allocates an `Object` into the
template's second `BodBase` slot at `+0x60`, disables culling with
`OBJECT_FLAG_DISABLE_CULLING`, then requests four vertices per segment plus two
cap vertices and two side facequads per segment plus one terminal cap face.

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

- match: 92.87%
- target/candidate instructions: 421 / 421
- prefix: 69 / 421
- masked operands: 25 clean, 0 unresolved, 0 mismatched

Remaining gap:

The candidate now has the target's exact `0x5c` frame, instruction count, and
major register/lifetime shape. Its seven bounded mismatch regions contain only
independent store scheduling: two vector-temporary stores, face-index and UV
stores, one component store in each cap expression, cap copy/push scheduling,
and a final UV/epilogue reorder. No behavior or ownership gap remains.

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

## 2026-07-13 owner-relative source recovery

The Windows compiler shape recovered once the scratch stopped naming indexing
temporaries that neither the Android source nor the assembly requires. The
source now:

- advances a generated-row `Vector3*` cursor while indexing sampled strip
  vertices directly through the owning `Path` fields;
- writes both side faces with direct `row * 4` vertex indices rather than an
  invented `vertex_base`;
- writes the terminal face directly through
  `facequads[segment_count * 2]`; and
- forms and copies the two cap vertices with direct owner-relative vector
  expressions, without invented `previous_row`, `final_row`, or `cap` views.

Those changes moved the focused result from `22.19%` through `32.36%`,
`58.10%`, and `78.74%` to `92.87%`. A scalar component-by-component version of
the cap expressions was rejected: it regressed to `76.44%` and only `377`
instructions. Android flattened those operators in its decompile, but the
Windows target retains the by-value vector operator family.

Binary Ninja now records the recovered prototype as
`void __thiscall build_track_fringe_supertramp_mesh(Path* self, char* texture_path)`.
The typed decompile resolves the generated object through the embedded fringe
`BodBase` at `Path +0x60`, the source strip through the leading BOD, and the
loop dimensions through `Path::segment_count` and `Path::width_cells`.

## 2026-07-14 generated-mesh owner

The generated `Object*` now comes directly from
`Path::fringe_mesh_bod.object`; the former cast was a stale holdover from when
that embedded BOD field was untyped. Focused output remains byte-identical at
92.87%, 421/421 instructions, prefix 69/421, with all 25 operands clean.
