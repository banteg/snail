# finalize_path_template

First tracked scratch for `finalize_path_template @ 0x42c600`.

Recovered behavior:

- scans secondary sample positions and stores the maximum `(int)(z + 1.0f)` in
  `AttachmentPathTemplate::row_span_count`;
- builds inverse transforms for both primary and secondary sample arrays at
  sample `+0x40`;
- computes each segment's lateral source from the cross product of adjacent
  forward vectors dotted against the current right vector;
- mirrors and clamps the lateral source into the native `[-0.1, 0]` range;
- clears the terminal sample's lateral source;
- marks the strip mesh runtime-ready and clears the imported-X-mesh flag.

This promotes `AttachmentPathTemplate +0x24` as `strip_mesh`, widens
`AttachmentSample::inverse_matrix` to the full 16-float transform window, and
names the strip mesh flag lane at `+0x10`.

The remaining mismatch is compiler shape in the cross/dot segment loop:
native keeps the sample offset in `edi`, reloads `primary_samples`, stores the
dot result with `fstp`, then reloads the lateral source for mirror/clamp.
The scratch uses the same semantic offset walk, but VC6 still keeps a sample
pointer for part of the loop and schedules the x87 stack differently.
