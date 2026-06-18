# update_track_speedup @ 0x43ee50

Exact match under the standard `msvc6.5 /O2 /G5 /W3` profile.

Recovered behavior:

- skip when the singleton's `owner_game +0x09` `subgame_pause_gate` byte is set;
- state `0` returns immediately;
- state `2` unlinks the pickup from the shared `g_game_base + 0x5a8` bod list,
  pushes it onto the free stack, clears `0x200`, and kills the sprite;
- state `1` performs the same teardown once `world_position.z` falls behind
  `owner->interaction_max_z`.

The local source shape intentionally keeps the state-1 and state-2 unlink
blocks duplicated. VC6 otherwise merges the error tails and loses the exact
native layout.

2026-06-16 vtable correction: this is the speedup singleton updater, not the
jetpack pickup updater. The proof is `initialize_track_speedup_runtime`, which
installs vtable `data_497314`; that vtable's first entry is `0x43ee50`.
The field window also lines up with `game + 0x355db0`: position at
`+0x68..+0x70`, state at `+0x80`, owner at `+0x84`, game pointer at
`+0x8c`, and sprite at `+0xac`. The full position vector is cross-confirmed
by `handle_subgoldy_collisions`.

2026-06-17 symbol sync: the tracked IDA/BN decompile exports and the live BN
session now name `0x43ee50` as `update_track_speedup`, matching the gameplay
manifest and this exact scratch.

2026-06-16 renderable-prefix consolidation: the shared
`TrackSpeedupRuntime` header now records the renderable transform rows at
`+0x38..+0x77`, with `world_position +0x68` as
`RenderableBod::transform.position`. The initializer calls
`initialize_renderable_bod()`, this exact updater consumes `world_position.z`,
and `handle_subgoldy_collisions` consumes the full x/y/z vector. The type stays
`BodNode`-based because the zero-offset intrusive list overlay is real and is
used by both teardown paths.
