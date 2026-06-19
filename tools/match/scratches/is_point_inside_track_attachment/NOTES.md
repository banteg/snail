# is_point_inside_track_attachment @ 0x42ca90

First typed scratch for the attachment-volume containment probe.

The function scans `secondary_samples` backward, subtracts the source
`TrackRowCell::anchor_position`, rotates the probe point by each sample's
`inverse_matrix`, and accepts points inside the widened local lane bounds:
X within the integer half-width plus `0.3`, Y in `[-0.3, 0.3)`, and Z between
`0` and `sample->delta_length`.

Important ABI correction: this is the `update_sub_lazer_projectile` callsite
shape, not a three-float helper. The method consumes a by-value `Vector3 probe`,
an unused by-value `Vector3 swept_motion`, and a `TrackRowCell*`, so native
returns with `ret 0x1c`.

Current match: 99.10%, 111/111 instructions, 42-instruction prefix, six masked
operands clean.

Residuals:

- The remaining miss is a single independent scheduling swap in the local-vector
  constructor: native subtracts `origin_z` before reloading the staged
  `delta_y`, while the scratch reloads `delta_y` before the `fsub`.

2026-06-20 attachment probe pass:

- Replacing the aggregate `sample_origin = Vector3(...)` with field stores and
  keeping the `inverse_matrix` pointer between the Y and Z origin stores moves
  the matrix-argument push before the Y/Z spills, matching the native loop-body
  schedule.
- Rewriting the loop as `while (idx >= 0) { ... idx--; }` matches the native
  false-then-true epilogue layout and removes the extra loop-tail jump.
- Focused matcher improves from 87.89% to 99.10% (111/111 instructions,
  prefix 42/111, six clean masked operands).

Rejected probes:

- Treating the function as `(float px, float py, float pz, TrackRowCell*)`
  was wrong: the generated `ret 0x10` contradicted native `ret 0x1c`.
- Holding a long-lived `AttachmentSample*` kept both a sample pointer and the
  sample byte offset live, forcing `this` into `ebp` and dropping the match to
  55.75%.
- Replacing `sample_origin` with explicit origin floats lost the native
  `0x30` frame and dropped the match to 68.49%.
- Breaking out of the loop and returning from a tail `idx` test added an early
  false epilogue and regressed to 85.71%.
- A `bool inside` result local introduced an extra saved register and dropped
  the match to 51.33%.
- Passing `secondary_samples[idx].inverse_matrix` directly was codegen-neutral;
  the accepted schedule needs the source-level pointer between origin Y and Z.
- Explicit `local.x/y/z` stores collapsed the frame to 0x24 and regressed to
  65.44%.
- Folding `delta_z = probe.z - origin_z` changed the x87 polarity to `fsubr`
  and regressed to 98.20%.
- Applying the same field-origin ordering to
  `try_enter_track_attachment_from_swept_motion` was codegen-neutral at 79.80%,
  so that scratch stays unchanged.
