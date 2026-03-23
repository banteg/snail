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

## 2026-03-23 18:45 - Iteration: restore native negative ring shove

### Target
- Runtime ring kinds `3/7` motion parity in `handle_subgoldy_collisions` / `update_subgoldy`

### Why this target
- The Zig runtime still treated native `3/7` ring collisions as the long authored slow-status timer, while Binary Ninja now pins both the collision write and the short recovery math tightly enough to replace that guess.

### Original behavior evidence
- Confirmed:
  - `handle_subgoldy_collisions` (`0x444cf0`) routes ring kinds `3/7` to the `sfx 43` branch, writes `-0.1` into `player->velocity.z`, and skips `add_subgoldy_score`.
  - `update_subgoldy` (`0x43b120`) adds `track_center_x^2 * 0.004 * 0.25` to `player->velocity.z` each tick while that lane is negative, then clamps it back to `0`.
  - The same Win32 runtime still quantizes gameplay world `x` with `floor(x + 4.0)` and clamps the player to `[-4.0, 4.0]`, which keeps `track_center_x` at `4.0` for this motion slice.
- Likely:
  - Once the negative shove crosses zero, Windows hands control back to the broader forward-speed controller rather than leaving the velocity lane at `0`.
- Unknown:
  - The exact positive-speed controller that repopulates `Player.velocity.z` after negative rings or garbage hits is still not mapped end-to-end.

### Zig changes
- `zig/src/gameplay.zig`
- Added a runner-local native `velocity.z` override for runtime ring kinds `3/7`, seeded from the recovered `-0.1` write and advanced with the recovered zero-crossing recovery.
- Extended track stepping to handle brief backward row motion so the recovered shove actually moves Turbo backward.
- Removed the old runtime path that reused `slow_ticks` for native `3/7` collisions; authored `.slow` annotations still keep the existing timer-based behavior.
- `docs/rewrite/subsystem-status.md`
- `docs/re/audio-callsite-map.md`
- Updated the runtime-status and audio notes so they no longer claim the negative-velocity lane is still missing.

### Verification
- Ran `zig fmt zig/src/gameplay.zig`.
- Ran `zig build test`.
- Added unit coverage for the seeded `-6 rows/second` shove, the first backward row step, zero `slow_ticks` on native `3/7` collisions, and the handoff back to the base forward-speed scaffold after the override clears.

### Remaining gaps
- The broader native forward-speed controller behind `Player.velocity.z` is still unresolved.
- Garbage impacts still write into the Zig high-level motion scaffold instead of the same recovered velocity owner.

### Next target
- Port the garbage-impact motion owner so both native negative rings and garbage hits feed the same recovered velocity controller.
