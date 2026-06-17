# spawn_slug_hazard

First scratch for `spawn_slug_hazard` @ `0x43dc80`
(`cRSubGame::AddSlug(cRSubLoc*, cRSubGoldy*)`).

Recovered relationships:

- scans the eight-slot slug pool at `game+0x3563a0`, stride `0xec`, using
  `state +0x80`;
- seeds the renderable transform position from `TrackRowCell::anchor_position`
  with a fixed `+1.7f` Y lift, then projects through
  `project_position_onto_track_attachment`;
- inserts the slot's zero-offset `BodNode` before the shared BOD-list tail;
- allocates sprite texture `118`, forces white color, size `2.0f`, and mirrors
  the projected position into `Sprite::position`;
- confirms `SlugHazardRuntime::player +0xc0`, `sprite +0xac`,
  `source_cell +0xb0`, `passed_player +0xb4`,
  `player_encounter_latched +0xd9`, and the blink/voice progress tail.

Current result: 86.52%, 159/160 instructions, with 15 clean masked operands.
The main residuals are scheduling/order issues in the initial state/player
stores, velocity staging, and the hit-flash/HP tail.

Rejected probes:

- Promoting the initial state/player/matrix setup to a typed
  `SlugHazardRuntime*` regressed to 53.92% by changing saved-register
  ownership and keeping the slot node live too broadly.
- Keeping the list node live through the later flag clear regressed to 59.56%.
  Reload the flag dword at `+0x04` instead.
