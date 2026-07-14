# `update_track_attachment_follow_state` result

## Matcher summary

| Metric | Before | After |
|---|---:|---:|
| Match | 46.44% | **72.89%** |
| Target instructions | 726 | 726 |
| Candidate instructions | 678 | 698 |
| Exact prefix | 0 / 726 | **122 / 726** |
| Stack frame | `0x160` | **`0x180`** |
| Masked operands | 45 ok, 0 unresolved, 0 mismatch | **63 ok, 0 unresolved, 0 mismatch** |

The measured improvement is **+26.45 percentage points**. The first remaining mismatch is target instruction 122, where both sides emit `je` but branch to differently laid-out blocks.

## Accepted source-shape changes

- Reconstructed a single top-tested segment-consumption loop with a real `p_delta_length` local and explicit terminal path.
- Split template-pointer lifetimes and reloads to recover the native entry allocation and register pressure.
- Repeated special-runtime row lookups literally for each flag/value store.
- Used direct primary-sample expressions for scalar and orientation interpolation.
- Recovered the kind-42 helper as a member-shaped call, plus the native blend polarity and matrix-position zeroing order.
- Added semantic `Vec3` staging for ordinary offsets and the Supertramp terminal launch result.
- Added ordinary-path x/y/z component intermediates to improve x87 scheduling.
- Recovered aggregate `Vec3` publication into the embedded Player live-matrix rows.
- Replaced the final field-first row and matrix globals with canonical `GameRoot`, `SubgameRuntime`, `SubRow`, and `Player` ownership paths.
- Recovered `FollowState +0x20..+0x28` as one `orientation_up` vector and the side-exit output as a whole-vector copy.
- Kept separate semantic clamp returns for the side-exit path.

## Rejected trials

- Four-vector ordinary rewrite: `43.99%`, frame grew to `0x184`.
- Early sibling-loop transplant: `42.13%`, before the required pointer/control-flow reconstruction.
- Scalar terminal rewrites and aggregate ordinary result vector: frame collapsed to `0x174`; the latter peaked at `68.67%`.
- Branch-local basis-pointer attempts: more instructions but lower best score (`67.05%`).
- Active sample-pointer kind-42 form: `65.52%`.
- Literal nested IDA clamp tail: `67.80%`, below the simpler semantic return shape.
- Several row-local, voice-expression, terminal-boolean, and expression-order probes were codegen-neutral.

## Final audit

- Fixed toolchain: `msvc6.5 /O2 /G5 /W3`.
- No inline assembly, volatile padding, fake globals, dummy externs, or normalizer-specific tricks.
- Final matcher output: `72.89%`, target `726`, candidate `698`, prefix `122`, masks `63/0/0`.
