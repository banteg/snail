# spawn_track_health_pickup @ 0x43d6c0

Live source map for `cRSubGame::AddHealth(cRSubLoc*, cRSubGoldy*)`.

Current match:

- `52.89%`, `120/122` candidate/target instructions, with `7` masked operands
  ok.
- The first `16` target instructions now match. The key source-shape fix was
  staging the cell position through the shared `PositionBits` local, which
  recovers the native `0x10` byte stack frame.

Evidence:

- Scans eight health pickup slots at `game + 0x356000`, stride `0x74`.
- Seeds the promoted partial `TrackHealthPickup` fields: `world_position +0x10`,
  `state +0x38`, `owner +0x3c`, `sprite +0x64`, `source_cell +0x68`,
  `bob_phase +0x6c`, and `bob_phase_step +0x70`.
- Allocates sprite texture `57`, marks sprite flag `0x800`, clears gravity and
  progress fields, and writes `size_start/size_end = 0.60000002f`.
- Writes `source_cell +0x68`; this is distinct from
  `TrackHealthPickup::visibility_cell +0x44`, which is read by
  `update_track_health_pickup`.
- Initializes `bob_phase +0x6c` from a numeric float-to-int conversion of
  `world_position.z`, matching the native `__ftol` lane: even z starts at
  `0.5f`, odd z stays `0.0f`.

This scratch intentionally keeps the game health pool as word-indexed pointer
math until a shared `Game` health-pool layout is recovered.

Remaining mismatch:

- Native schedules `sub eax, ebx` before loading `cell` into `ebp`; current VC6
  source loads `cell` first.
- The active-list splice and sprite initialization use the same offsets but
  still differ in register allocation and local zero/constant choices.
