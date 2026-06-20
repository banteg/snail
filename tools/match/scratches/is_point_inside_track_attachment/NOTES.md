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
- 2026-06-20 residual scheduling audit: focused Wibo still reports 99.10%,
  111/111 instructions, 42/111 prefix, and six clean masked operands. Folding
  only the Y subtract (`delta_y = probe.y - origin_y`) regresses to 97.30% by
  flipping that lane to `fsubr`. The following source-plausible shapes are
  codegen-neutral and leave the same lone `delta_y` reload / `delta_z` fsub
  swap: spelling the Z subtract as `delta_z = delta_z - origin_z`, assigning
  through a short-lived `Vector3 local_delta`, aliasing the middle constructor
  argument as `local_y`, and subtracting `sample_origin.z` directly. Keep the
  current two-step Y/Z subtracts plus direct `local = Vector3(...)` assignment
  unless a new source lead explains the scheduler choice.
- 2026-06-20 vector-local retry: making `local` block-scoped at the assignment
  point has the same bad shape as explicit `local.x/y/z` stores: VC6 shrinks
  the frame to `0x24` and drops to 71.30%. Reordering the Y/Z source
  statements is codegen-neutral at 99.10%, and building the vector from raw Z
  before `local.z -= origin_z` regresses to 52.86% by adding saved `ebp` and
  flipping the Z subtract to `fsubr`. The long-lived aggregate assignment
  remains the only accepted frame shape.
- 2026-06-20 follow-up: making the Z subtract a constructor-argument side
  effect and spelling the third argument as `delta_z - origin_z` are both
  codegen-neutral at 99.10%. They still leave the lone `mov ecx` /
  `fsub [origin_z]` scheduling swap, so the clearer baseline is retained.
- 2026-06-20 larger near-proof continuation: declaration order for `local` and
  `sample_origin`, subtracting directly from `sample_origin.z`, and assigning
  through a temporary `local_delta` are all codegen-neutral at 99.10%. The
  residual remains the same single independent reload/subtract scheduling swap
  in the local-vector constructor; keep this helper pinned unless a real
  original-source local-lifetime lead appears.
