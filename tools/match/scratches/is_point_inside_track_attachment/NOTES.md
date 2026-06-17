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

Current match: 87.89%, 112/111 instructions, 15-instruction prefix, six masked
operands clean.

Residuals:

- Native pushes the `inverse_matrix` argument before spilling the intermediate
  sample-origin Y/Z temporaries; the clean staged source spills them before the
  push.
- Native lays out the false epilogue before the true epilogue and branches to
  the true tail after the final `delta_length` compare. VC6 keeps the inline
  `return true` epilogue before the loop-exhausted false return.

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
