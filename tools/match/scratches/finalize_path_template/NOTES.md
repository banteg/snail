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

2026-06-20 follow-up: `AttachmentSample::inverse_matrix` now uses the shared
`TransformMatrix` type directly. The source can call
`sample->inverse_matrix.invert_matrix_from_source(&sample->transform)` without
the old cast, and the matcher stays at the existing 69.41% baseline.

2026-06-21 segment-loop pass: keeping the dot source as a `Vector3* right`
while spelling the lateral-source writes as repeated sample-offset lvalues
raises the scratch from 69.41% to 74.67%. This recovers the native `edi`
byte-offset lifetime through the mirror/clamp reloads and the `fstp` dot-result
store, without changing the real `Vector3` member-call ABI. A tempting free
`__fastcall` declaration for `cross_vectors`/`dot_vector` scored 75.34% and
cleared the masked mismatch, but it is rejected because native cross-vector
calls pass the output in `ecx` and push both vector arguments.

The remaining mismatch is compiler shape in the cross/dot segment loop:
native schedules `cross_vectors` by pushing both arguments before loading the
local cross-product `this` pointer, while VC6 still materializes the local
address before the pushes for the member-call spelling. Secondary inverse-loop
base-local probes were codegen-neutral, and segment-limit locals regressed.

2026-06-21 adjacent-sample typing pass: spelling the cross-product inputs as a
typed `primary`/`next` sample pair while keeping the lateral-source writes as
raw repeated lvalues raises the scratch from 74.67% to 75.34% and clears the
masked call mismatch without changing the `Vector3::cross_vectors` thiscall
ABI. The key is keeping `primary` live for the subsequent dot call; scoped
typed arguments or raw-right recomputation regress to 71.11%, inline casts fall
back to the old 74.67% masked mismatch, and explicit segment-limit locals
reshape the prologue down near 60%.
