## 2026-03-23 18:33 - Iteration: tighten installed attachment entry sweep

### Target
- Installed attachment entry in `try_enter_track_attachment_from_swept_motion` parity

### Why this target
- Attachment follow is still central gameplay scaffolding, and the Zig port still depended on a source-row fallback because the geometric entry test was weaker than the recovered Windows helper.

### Original behavior evidence
- Confirmed:
  - Binary Ninja decompile of `try_enter_track_attachment_from_swept_motion` (`0x42c770`) scans the installed sample array from `sample_count - 1` down to `0`.
  - The helper skips candidate samples when `sample + 0x14` is negative, which matches the sampled record's `basis_up.y` lane in the current runtime-structure notes.
  - The helper uses raw local sweep thresholds: lateral span `width/2 +/- 0.3`, start `y >= -0.2`, start `z` inside the sample `delta_length`, and end `y <= 0.001`.
- Likely:
  - The old Zig row-progress window could miss valid installed-entry candidates on curved attachments because Windows does not limit the scan to the source-row progress band.
- Unknown:
  - Whether the remaining source-row fallback can be removed entirely once more live installed-entry cases are verified.

### Zig changes
- `zig/src/gameplay.zig`
- Replaced the windowed installed-entry scan with a dedicated tail-to-head sweep helper that matches the recovered Windows thresholds and upside-down-sample rejection.
- Kept the source-row fallback intact as a backup path, but narrowed when the geometric sweep fails.
- Added focused tests for deep-sample matching and inverted-sample rejection.

### Verification
- Ran `zig fmt zig/src/gameplay.zig`.
- Ran `zig build test`.
- Added unit coverage that proves the new sweep can match a deep tail-side sample and refuses an upside-down sample even when the other local thresholds are satisfied.

### Remaining gaps
- The source-row fallback still exists.
- The port still does not model the full Windows installed-bank ownership or the family-specific nonlinear entry and exit branches.

### Next target
- Recover enough of the remaining installed-bank and nonlinear kind-`42` entry semantics to remove more of the source-row fallback without guessing.
