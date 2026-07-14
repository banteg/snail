# Near match — 95.78% score, 199/204 instructions on standard flags

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
  the closest honest seed-after-return layout. A structured
  `break`/exhaustion form introduces an extra index check and regresses the
  current candidate to 95.31%, so it remains rejected.

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

## 2026-07-14 canonical root ownership

The fixed player is now reached through
`GameRoot::subgame.player`; every accepted-entry write traverses canonical
`Player` fields, including the embedded `follow_state`, live matrix, velocity,
exit gate, and `Squidge`. The installed heading likewise comes from the real
`SubgameRuntime::runtime_rows[row]` owner. Seven field-first absolute globals
are no longer needed by matching sources.

This ownership recovery improves the focused candidate from 84.69%, 188/204
instructions, 24 clean operands plus one mismatch to 95.78%, 199/204,
47 clean operands, with no unresolved or mismatched masked references. The
reference manifest now bounds `g_player_block` to the proven 0x4364-byte
`Player`, allowing canonical base-plus-field relocations to audit against older
narrow field aliases.

The entire accepted-entry seed block is instruction-identical. Remaining
honest deltas are one commutative swept-X addition order and VC6's placement of
the exhausted-loop epilogue: native duplicates the epilogue before the seed
block, while the current source branches to the shared tail. Volatile aliases,
dummy reloads, and neutral arithmetic remain rejected as fakematching.
