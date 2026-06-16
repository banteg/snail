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
- 2026-06-13 follow-up: the pool scan now advances the slot pointer before the
  overflow check, matching the native control-flow semantics and improving the
  scratch to 64.31% (`tools/match/match.sh
  tools/match/scratches/spawn_track_garbage_hazard --full`). A local
  three-word staged-position array was tested because the native uses stack
  staging before projection, but it changed register ownership (`this` moved
  out of `edi`) and regressed the match; leave the remaining frame/staging gap
  alone until stronger source evidence appears.
- 2026-06-13 source-shaping follow-up: a typed `PositionBits` staging record
  assigned into the live slot position recovers the native `0x10` stack frame.
  A source-equivalent `while (1)` pool scan now matches the native loop head
  and overflow branch shape exactly. A follow-up independent setup reorder
  stores the player owner before deriving the scale pointer, matching the
  native slot/player/scale setup sequence. Reordering the staged position
  writes to x/z/y aligns the native x/z load order before the y store. Current
  result: 91.87%, 140/143 insns
  (`tools/match/match.sh tools/match/scratches/spawn_track_garbage_hazard
  --full`).
- 2026-06-13 follow-up: spelling the y coordinate as a two-step `staged_y`
  temporary (`scale`, then `+= cell_y`) recovers the native `fld scale` side of
  the projection staging block. Current result: 92.58%, 140/143 insns
  (`tools/match/match.sh tools/match/scratches/spawn_track_garbage_hazard
  --full`).
- 2026-06-13 pin audit: a pointer-to-local staging spelling compiled to the
  same 92.58% code, while explicit staged-record field copies changed
  function-wide register ownership and regressed to 52.86%. Revert both forms.
- Pinned at 92.58%, 140/143 insns. Current residuals are source-shape/register
  issues, not known semantic gaps: projection staging still differs in x87
  operand order plus x/z local register allocation. Aggregate initialization,
  y-first staging, destination-pointer hoisting, pointer-to-local staging, and
  field-wise live-position copies were tested; only x/z/y staging plus the
  two-step y temporary helped. Do not force the remaining projection order with
  dummy volatile locals.
- 2026-06-16 Sprite audit: the sprite tail now spells the confirmed `Sprite`
  fields by name (`gravity_step`, `progress`, `progress_step`,
  `size_start`, `size_end`, and `position`) while deliberately reloading the
  sprite through the slot field for each write. A cleaner local `Sprite*`
  spelling is semantically equivalent but regresses to 77.26% because MSVC keeps
  the pointer live and collapses the native-looking reloads. Current result
  remains 92.58%, 140/143 insns.
- 2026-06-16 garbage slot audit: the spawn tail confirms
  `GarbageHazardSlot::source_cell` at `+0xb8` and `hidden` at `+0xbc`, now
  recorded in the shared header. A typed `GarbageHazardSlot*` spelling in this
  scratch regressed to 60.56% by changing saved-register ownership from the
  function prologue, so the scratch keeps the raw offset writes while the
  header carries the recovered fields.
