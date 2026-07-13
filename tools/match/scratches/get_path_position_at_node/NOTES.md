# get_path_position_at_node @ 0x42b9c0

Exact VC6 match: 100.00% (56/56 instructions, full prefix, no masked
operands).

Confirmed semantics:

- reads `primary_samples[node]` at stride `0xa8`;
- projects one borrowed `Vector3` local coordinate through the sample right/up
  basis;
- adds the sample position row;
- adds `row_index` to projected z;
- writes the projected x/y/z output; the final z copy naturally leaves its bits
  in `eax`, but both native callers immediately overwrite `eax`.

The iPhone v1.5 symbol table gives the original cross-port signature as
`cRPath::GetPos(tVector&, int, int, tVector&)`. Its ARM implementation at
`0x4f848` independently confirms the source shape: it computes
`position + local.x * right + local.y * up`, adds the integer row to z, and
copies the resulting three-float vector to the output reference. The shared
prototype and both parcel-placement callers therefore use `Vector3&` for the
input/output alias instead of the old `float*` cast. The two Windows callsites
at `0x444212` and `0x444482` discard EAX, and changing the candidate from an
invented integer return to `void` preserves the exact codegen. The local
header and live Binary Ninja prototype now model the method as
`void cRPath::GetPos(...)`.

The exact source shape keeps local y as a real `float`, builds a named up-basis
contribution, and gives the additions distinct lifetimes:

- `projected = local.x * right + position`;
- `projected = projected + scaled_up`;
- `final_position = projected` before adding `row_index` to z;
- one final assignment to the borrowed output reference.

Those ordinary value-copy boundaries explain the native `0x24` frame, saved
`esi` input-reference lifetime, duplicated x87 lanes, delayed output-pointer
load, and reuse of the dead up-contribution slot for final z. No volatile,
inline assembly, or dummy aliasing is involved.

Rejected probes:

- `/Op` regressed the scratch by growing the frame and forcing qword temporaries;
- semantic `Vector3` contribution/base/projected locals recovered the frame but
  only reached 34.23%;
- raw scalar field expressions without the explicit temp layout lost the frame
  or `esi` lifetime;
- an all-in-one inline vector expression reached 69.81% but lost the saved
  `esi` input-reference schedule;
- spelling the final copy component-by-component or through an inline copy
  helper regressed to 33.96%-40.00%;
- a distinct result for the whole second addition loaded the output pointer too
  early and folded the row with `fiadd`; copying only after that addition
  recovered the authored final-value lifetime and the exact tail.
