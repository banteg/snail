# `update_track_attachment_follow_state` result

## Matcher summary

| Metric | Before | After |
|---|---:|---:|
| Match | 46.44% | **75.66%** |
| Target instructions | 726 | 726 |
| Candidate instructions | 678 | 712 |
| Exact prefix | 0 / 726 | **122 / 726** |
| Stack frame | `0x160` | **`0x180`** |
| Masked operands | 45 ok, 0 unresolved, 0 mismatch | **65 ok, 0 unresolved, 0 mismatch, 0 unaudited** |

The measured improvement is **+29.22 percentage points**. The first remaining mismatch is target instruction 122, where both sides emit `je` but branch to differently laid-out blocks.

## Accepted source-shape changes

- Reconstructed a single top-tested segment-consumption loop with a real `p_delta_length` local and explicit terminal path.
- Split template-pointer lifetimes and reloads to recover the native entry allocation and register pressure.
- Repeated special-runtime row lookups literally for each flag/value store.
- Used direct primary-sample expressions for scalar and orientation interpolation.
- Recovered the kind-42 helper as a member-shaped call, plus the native blend polarity and matrix-position zeroing order.
- Added semantic `Vec3` staging for ordinary offsets and the Supertramp terminal launch result.
- Added ordinary-path x/y/z component intermediates to improve x87 scheduling.
- Recovered aggregate `Vec3` publication into the embedded Player live-matrix rows.
- Replaced the final field-first row and matrix globals with canonical `GameRoot`, `cRSubGame`, `SubRow`, and `Player` ownership paths.
- Recovered `FollowState +0x20..+0x28` as one `orientation_up` vector and the side-exit output as a whole-vector copy.
- Recovered the side-exit x clamp as one conditional expression, restoring the native x87 `-4/+4` constants and clearing both unaudited operands.
- Named the signed path segment count before deriving the terminal index, improving the native last-index lifetime and downstream alignment.

## Rejected trials

- Four-vector ordinary rewrite: `43.99%`, frame grew to `0x184`.
- Early sibling-loop transplant: `42.13%`, before the required pointer/control-flow reconstruction.
- Scalar terminal rewrites and aggregate ordinary result vector: frame collapsed to `0x174`; the latter peaked at `68.67%`.
- Branch-local basis-pointer attempts: more instructions but lower best score (`67.05%`).
- Active sample-pointer kind-42 form: `65.52%`.
- Literal nested IDA clamp tail: `67.80%`, below the simpler semantic return shape.
- Several row-local, voice-expression, terminal-boolean, and expression-order probes were codegen-neutral.
- Five ordinary result-vector forms fell to `66.43%`–`66.81%`.
- Shared output-position pointer lifetimes were neutral or regressed to `74.69%`.
- Hoisted path-component owners and all 63 ordinary position operand orders were byte-neutral.

## Final audit

- Fixed toolchain: `msvc6.5 /O2 /G5 /W3`.
- No inline assembly, volatile padding, fake globals, dummy externs, or normalizer-specific tricks.
- Final matcher output: `75.66%`, target `726`, candidate `712`, prefix `122`, masks `65/0/0/0`.
