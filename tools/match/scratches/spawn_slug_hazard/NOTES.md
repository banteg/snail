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

2026-06-20 larger source-shape pass: focused Wibo improves from `86.52%` to
`92.79%` (`159/160` instructions, `48/160` prefix, 16 clean masked operands).
Three source-shaped changes were retained:

- splitting the initial state/player destinations into `state_ref` and
  `player_ref` keeps the native state store before the player store and
  recovers the first 48-instruction prefix;
- using the proven typed `BodNode`/`BodList` tail-insertion idiom recovers the
  native `g_game_base + 0x5a8` materialization and adds the extra clean masked
  operand;
- spelling the hit-flash step, hit-points, and node-flags tail through local
  destination references keeps the x87 flash-step store before the HP/flag
  writes and fixes the HP/flag scheduling residual.

Current residual: the velocity staging still differs. Native keeps
`game+0x38` live on x87, loads a float zero, stores that zero through the local
vector x/y lanes, then multiplies the z lane by `-0.2f`; the candidate still
pre-multiplies z and writes x/y with integer zero stores.

Rejected probes:

- Promoting the initial state/player/matrix setup to a typed
  `SlugHazardRuntime*` regressed to 53.92% by changing saved-register
  ownership and keeping the slot node live too broadly.
- Keeping the list node live through the later flag clear regressed to 59.56%.
  Reload the flag dword at `+0x04` instead.
- Naming a `float zero`, using a `Vector3(0.0f, 0.0f, z)` constructor, seeding
  `velocity.z` before scaling it, splitting `velocity_x/velocity_y/velocity_z`
  locals, and using double `0.0` literals are neutral for the retained score
  and do not recover the native x87 zero stores.
- Staging `g_game_base + 0x5a8` and the initial node flags as raw locals is
  neutral after the prefix fix; the typed BOD idiom is the accepted list shape.
