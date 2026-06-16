# spawn_garbage_smoke_particle

`spawn_garbage_smoke_particle` @ 0x43d5a0 is the smoke-effect producer called
from the pinned `update_garbage_hazard` burst state.

Behavior:

- Gates on `byte_4df934 & 0x10` before doing any sprite work.
- Allocates sprite id 33 from `g_sprite_manager` for the owning player slot.
- Marks the sprite as effect-rendered (`flags |= 0x800`), zeros progress and
  lifetime lanes, and derives progress/lifetime rates from `game->subgame_rate`.
- Seeds white color, scale `(0.30000001, 1.3)`, velocity scaled by `0.2`, and
  position copied from the garbage hazard.

Match status: 76.82% (75 candidate instructions vs 76 target, 5/76 exact
prefix). This is source-shaped and useful as a garbage-smoke semantic anchor,
but not exact.

Residual:

- The native target keeps the color copy at `sprite + 0x2c`, delays
  `sprite += 0x48` until after preparing the velocity destination, and stores
  scaled velocity through stack locals. The best source-shaped aggregate color
  assignment moves `sprite += 0x48` earlier and stores velocity with a different
  x87/local schedule.
- The native function is typed by IDA as a byte return but leaves the success
  path's copied `position.z` dword in `eax`; modeling a byte return recovers the
  native prologue but adds a final `mov al, [position.z]` in the candidate.

Rejected source-shape probes:

- Cdecl `allocate_sprite(archive, ...)` regressed the call shape; existing
  sprite scratches confirm this is `g_sprite_manager.allocate_sprite(...)`.
- An `int` return with a byte flag local forced an extra stack slot and
  regressed to 63.69%.
- A separate scaled-velocity aggregate local over-allocated the stack and
  regressed to 67.55%.
- 2026-06-16 Player consolidation: the owner slot now comes from shared
  `player.h` (`Player::player_slot`) with the same 76.82% score and clean
  `9 ok` masked audit.
