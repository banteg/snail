# build_track_fringe_supertramp_mesh reconstruction notes

Current recovery: semantic-complete (`compiler` residual). The live Windows
`cRPath` receiver and exact Android/iOS `BuildFringeSuperTramp` bodies
establish generated-object ownership, both edge extrusions, the terminal cap
vertices, and every face/UV publication. Candidate and target are both 421
instructions with all 25 references clean; the remaining regions are store
scheduling only.

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

- match: 94.54%
- target/candidate instructions: 421 / 421
- prefix: 69 / 421
- masked operands: 25 clean, 0 unresolved, 0 mismatched

Remaining gap:

The candidate now has the target's exact `0x5c` frame, instruction count, and
major register/lifetime shape. Its three localized mismatch regions contain
only independent store scheduling: two two-instruction moves while copying the
shared vector-subtraction result, and one face-pair region with nineteen
face-index/UV store-order differences. The cap expressions, cap copies, final
face, and epilogue are now exact. No behavior or ownership gap remains.

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

## 2026-07-15 Binary Ninja object-owner replay

The repeatable Binary Ninja path/object replay now carries the canonical
`Object*` through `BodBase +0x24`, `set_bod_object`, and the vertex/face
allocation helpers. The tracked decompile exposes the generated object's flags,
blend mode, vertices, and facequads plus the sampled
`self->bod.object->vertices` source bank; `PathTemplateStripMesh` no longer
appears. The remaining raw offsets are derived row/face cursor expressions,
not an unresolved owner. Focused matching remains byte-identical at 92.87%.

## 2026-07-19 generated cap lifetimes

The paired guarded replay now separates this builder's generated `Object*`,
vertex bank, and face bank from the sampled `Path::bod.object` source. Its tail
also retains typed `Vec3*` lifetimes for the final generated row, the two
extrapolated cap vertices, and the subsequent cap-to-row copies. Those pointers
all borrow the allocation owned by the generated Object; none is a second bank
or an ownership transfer.

The same replay covers the ordinary fringe builder and verifies the canonical
`Path`, `BodBase`, `Object`, `ObjectFaceQuad`, and `Vec3` layouts before either
function is touched. An attempted name for the compiler's interior face cursor
was rejected because it degraded shifted-structure recovery, so that cursor
remains automatic. Matching source is unchanged at the current 94.54%,
421/421-instruction frontier with 25 clean operands.

## 2026-07-25 shared row and face-pair cursor ownership

The main row and face loops now use the same analysis-only offset-pointer views
as the ordinary fringe builder: a `0x30` four-vertex row carried at
`inner_a.z`, and a `0x60` pair of `ObjectFaceQuad`s carried at
`first_face.vertex_0`. These are non-owning cursors into the generated
`Object` banks; the terminal cap pointers remain separate borrowed lifetimes
over that same vertex allocation.

An IDA probe that typed the carried address as a parent-struct pointer was
rejected because it falsely labeled six references after the row cursor's
post-increment. The committed shifted scalar-pointer form renders the main row
correctly while leaving those post-increment references raw, rather than
inventing field ownership. Binary Ninja likewise retains honest raw offsets in
the cap tail. Matching source and the focused result remain unchanged at
94.54%, 421/421 instructions, prefix 69/421, with all 25 masked operands clean.

## 2026-07-29 recorded store-scheduling frontier

Three recorded mutation sweeps evaluated 41 unique source variants around all
three remaining regions. None improved the 94.54%, exact 421/421-instruction,
prefix-69 baseline: 27 variants were byte-identical and 14 degraded.

- Fifteen left/right edge-direction forms cover initialization versus
  assignment, explicit shared-operator and assignment calls, named and const
  difference values, and borrowed row pointers/references. Every form is
  byte-identical, leaving the same two shared vector-return copy schedules.
- Ten first-face index forms cover signed, unsigned, and 16-bit bases; shifted
  bases; named scalar indices; and pointer/reference face owners. Named
  indices and face borrows are neutral. Retaining a reusable base removes
  native instructions or perturbs allocation and regresses.
- Sixteen first/second-face UV forms cover face and UV borrows, union-field
  aliases, named constants, per-corner pointers, and whole-`ObjectUv` values.
  Scalar aliases are neutral; materializing corner or aggregate owners changes
  instruction count and regresses.

The ledger records three trailing non-improving sweeps. The canonical direct
indexing and scalar UV publication remain the strongest source-backed forms,
consistent with the authored mobile builder. The residuals are bounded VC6
scheduling differences rather than missing geometry, ownership, or control
flow.
