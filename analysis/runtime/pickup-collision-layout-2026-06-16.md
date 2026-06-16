# Pickup and collision runtime layout, 2026-06-16

This pass reconciled the collision scratch with the pickup spawners,
constructors, and exact helper methods. The key correction is that several
local `Game` fields in `handle_subgoldy_collisions` were stale by one runtime
region; the target asm and initializer ledger agree on the lower offsets.

Confirmed collision-adjacent lanes:

| region | base / field | evidence |
|---|---:|---|
| health pickups | pool `game + 0x356000`, stride `0x74` | `initialize_runtime_pools_and_path_template_bank`, `spawn_track_health_pickup`, `handle_subgoldy_collisions` |
| health state/position | state `+0x356038`, position `+0x356010` | `spawn_track_health_pickup`, collision target asm |
| speedup singleton | position `+0x355e18`, state `+0x355e30` | constructor offset `this + 874348`, reset, collision target asm |
| jetpack singleton | parent base `+0x355e64`, position `+0x355e74`, state `+0x355e9c` | constructor offset `this + 874393`, `spawn_track_jetpack_pickup`, reset, collision target asm |
| ring/special effect parents | base `+0x35b78c`, stride `0x1f8`, state `+0x35b80c`, kind `+0x35b814` | ring spawner/updaters, reset, collision target asm |
| parcel HUD/total | HUD owner `+0x35bb94`, total `+0x1b01e0` | `initialize_subgame`, `build_subgame_level`, collision target asm |

Related pool anchors corrected in the collision scratch:

- slug slots: `game + 0x3563a0`, stride `0xec`
- sub-lazer slots: `game + 0x356b00`, stride `0xb0`
- salt slots: `game + 0x3578c0`, stride `0x98`
- garbage list head: `game + 0x359140`
- track parcel/ring slots: base `game + 0x125e480`, position `+0x10`,
  state `+0x38`

Follow-up vtable check corrected a shifted symbol assumption:
`0x43ee50` is the speedup singleton updater, while `0x43efb0` is the jetpack
pickup parent updater installed by `initialize_track_jetpack_pickup_runtime`.
The shared jetpack parent layout now lives in `track_jetpack_pickup.h`.
