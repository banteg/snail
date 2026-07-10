# get_path_position_at_node @ 0x42b9c0

Current source-shaped lead: 77.78% (56 target instructions, 52 candidate,
8-instruction prefix).

Confirmed semantics:

- reads `primary_samples[node]` at stride `0xa8`;
- projects one borrowed `Vector3` local coordinate through the sample right/up
  basis;
- adds the sample position row;
- adds `row_index` to projected z;
- writes the projected x/y/z output and returns the z bits in `eax`.

The iPhone v1.5 symbol table gives the original cross-port signature as
`cRPath::GetPos(tVector&, int, int, tVector&)`. Its ARM implementation at
`0x4f848` independently confirms the source shape: it computes
`position + local.x * right + local.y * up`, adds the integer row to z, and
copies the resulting three-float vector to the output reference. The shared
prototype and both parcel-placement callers therefore use `Vector3&` for the
input/output alias instead of the old `float*` cast.

Modeling the original inline vector scale/add operators and keeping the
up-basis contribution as a named `Vector3` raises the Windows scratch from
41.12% to 77.78%. It preserves the native `0x24` stack frame, saved `esi`
input-reference lifetime, and 8-instruction prefix. The honest residual is
still VC6 x87 scheduling: the target duplicates the live local-y value before
each multiply and delays loading the output reference until the final copy;
the candidate loads basis lanes separately and folds the integer row with
`fiadd`.

Rejected probes:

- `/Op` regressed the scratch by growing the frame and forcing qword temporaries;
- semantic `Vector3` contribution/base/projected locals recovered the frame but
  only reached 34.23%;
- raw scalar field expressions without the explicit temp layout lost the frame
  or `esi` lifetime;
- an all-in-one inline vector expression reached 69.81% but lost the saved
  `esi` input-reference schedule;
- spelling the final copy component-by-component or through an inline copy
  helper regressed to 33.96%-40.00%.

Do not force this with volatile locals, asm, or dummy aliasing; resume only with
a source-idiom lead for the native duplicated-x87-lane schedule.
