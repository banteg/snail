# spawn_track_garbage_hazard

spawn_track_garbage_hazard @ 0x43da80 = `cRSubGame::AddGarbage(cRSubLoc*,
cRSubGoldy*)`.

Recovered semantics:

- scans the 50-slot garbage pool at `game+0x359144` for the first slot whose
  state at `+0x84` is zero;
- pushes the slot onto `game+0x359140` active garbage chain via `+0x80`;
- seeds random presentation scale at `+0x9c`, state `1`, and the live matrix
  position at `+0x68..+0x70`;
- calls `project_position_onto_track_attachment(game, &position,
  &slot+0xa0)` before linking the shared body-list node;
- inserts the body node before the tail sentinel at `game+0x3bb764`;
- allocates a garbage sprite with the second RNG draw, mirrors the slot scale
  into sprite `+0x60/+0x64`, copies the live body position to sprite `+0x48`,
  stores the source cell at `+0xb8`, and clears the hidden byte at `+0xbc`.

Residuals:

- 2026-06-13: WIP scratch scores 63.38% under the standard
  `msvc6.5 /O2 /G5 /W3` configuration. The semantic blocks are all present:
  pool scan, active-chain push, tagged `"Gadd"` scale RNG draw, attachment
  projection, shared body-list insertion, sprite variant RNG draw, sprite
  field setup, source-cell store, and hidden-byte clear.
- Current residuals are source-shape/register issues, not known semantic gaps:
  the native source reserves a 0x10-byte local frame and stages x/y/z before
  the projection call, while the current scratch lets VC6 keep more values in
  registers; the loop condition also compiles as a preloaded test instead of
  the native memory compare at the top of the scan.
- 2026-06-13 follow-up: the pool scan now advances the slot pointer before the
  overflow check, matching the native control-flow semantics and improving the
  scratch to 64.31% (`tools/match/match.sh
  tools/match/scratches/spawn_track_garbage_hazard --full`). A local
  three-word staged-position array was tested because the native uses stack
  staging before projection, but it changed register ownership (`this` moved
  out of `edi`) and regressed the match; leave the remaining frame/staging gap
  alone until stronger source evidence appears.
