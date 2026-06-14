# get_path_position_at_node @ 0x42b9c0

Current source-shaped lead: 41.12% (56 target instructions, 51 candidate,
8-instruction prefix).

Confirmed semantics:

- reads `primary_samples[node]` at stride `0xa8`;
- projects local x/y through the sample right/up basis;
- adds the sample position row;
- adds `row_index` to projected z;
- writes the projected x/y/z output and returns the z bits in `eax`.

The current scalar-temp source recovers the native `0x24` stack frame, node
argument load, `primary_samples` load, saved `esi` local pointer, and initial
`local_y` load. The remaining miss is x87 scheduling: native duplicates the
live `local_y` and `local_x` stack values before multiplying each basis lane,
keeps the z contributions live on the x87 stack, and delays the output stores
until after forming the row-index z result. VC6 keeps collapsing/reordering
those computations for clean C expressions.

Rejected probes:

- `/Op` regressed the scratch by growing the frame and forcing qword temporaries;
- semantic `Vector3` contribution/base/projected locals recovered the frame but
  only reached 34.23%;
- raw scalar field expressions without the explicit temp layout lost the frame
  or `esi` lifetime.

Do not force this with volatile locals, asm, or dummy aliasing; resume only with
a source-idiom lead for the native duplicated-x87-lane schedule.
