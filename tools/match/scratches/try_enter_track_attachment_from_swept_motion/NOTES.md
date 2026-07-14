# WIP — 84.69% score, 188/204 instructions on standard flags

The candidate uses the project-standard `msvc6.5 /O2 /G5 /W3`. Current
source-shape recoveries:

- `cell->anchor_position` is copied as a `Vector3`, reproducing the native
  anchor-load prologue and three persistent stack lanes.
- Both local probes are real vector subtractions. The swept endpoint is a
  vector addition before the second subtraction; the obsolete scalar-copy
  scaffolding was removed without changing codegen.
- The two sample gates read the array element before forming a pointer. This
  recovers both native sample-base calculations and raises the honest focused
  score from 75.63% to 84.69%.
- `do { ... } while (--idx >= 0); return;` plus the accepted-probe jump keeps
  the native seed-after-return layout. A structured `break`/exhaustion form
  introduced an extra check and regressed to 84.26%, so it was rejected.

Recovered behavior and ownership:

- Scan `Path::secondary_samples` backward from `segment_count - 1`, with the
  exact 0xa8-byte `AttachmentSample` stride, skipping samples whose authored
  world-up Y component is non-positive.
- Rotate `position - (cell anchor + sample position)` into sample-local space;
  require the integer-half-width bounds plus `y >= -0.2`, `z > 0`, and
  `z < delta_length`.
- Rotate `(position + sweep) - sample origin` again and accept when local
  `y <= 0.001f`.
- On acceptance, `0x42c98a` clears
  `Player::attachment_exit_pending` at player+0x41d. The caller rechecks that
  byte before its secondary-slot probe, so a successful primary entry retires
  the gate while a miss leaves the secondary candidate eligible.
- The seeded block at game+0x430100 is `Player::FollowState` at player+0x384,
  not a standalone global. It owns the borrowed `Path`, borrowed `SubLoc`,
  sample index, progress, vertical offset, orientation fields, and Player
  backlink.
- The same Player owns the adjacent position, velocity, exit byte, and inline
  `cRSquidge`; the installed heading comes from
  `SubgameRuntime::runtime_rows[row].installed_heading_delta`.
- The final validation is
  `FollowState::update_track_attachment_follow_state(player.velocity.z,
  &player.live_matrix.position, &player.velocity)`.

The two native callers discard EAX, both empty exits return without producing
a value, and the final helper result is not semantically consumed. Binary Ninja
now records `void __thiscall(Path*, six floats, TrackRowCell*)`, replacing the
stale `int PathTemplate::*` view. iOS names the broader family
`cRPath::Search(cRSubGoldy*, tVector, tVector, tVector, cRSubLoc*)`; the Windows
split keeps only seven stack dwords for position, sweep, and the borrowed cell.

Remaining honest deltas are one commutative swept-X addition order, the loop
branch polarity, and the seed block. Native repeatedly reloads the relocatable
Game base and uses x87 stores for two float fields, while VC6 coalesces the
direct owner expressions and uses integer copies. Volatile aliases, dummy
reloads, and neutral arithmetic were rejected as fakematching; these residuals
remain until a real authored owner/source expression explains them.
