# update_track_speedup @ 0x43ee50

Exact match under the standard `msvc6.5 /O2 /G5 /W3` profile.

Recovered behavior:

- skip when the singleton's `owner_game +0x09` paused byte is set;
- state `0` returns immediately;
- state `2` unlinks the pickup from the shared `g_game_base + 0x5a8` bod list,
  pushes it onto the free stack, clears `0x200`, and kills the sprite;
- state `1` performs the same teardown once `world_z` falls behind
  `owner->interaction_max_z`.

The local source shape intentionally keeps the state-1 and state-2 unlink
blocks duplicated. VC6 otherwise merges the error tails and loses the exact
native layout.

2026-06-16 vtable correction: this is the speedup singleton updater, not the
jetpack pickup updater. The proof is `initialize_track_speedup_runtime`, which
installs vtable `data_497314`; that vtable's first entry is `0x43ee50`.
The field window also lines up with `game + 0x355db0`: transform z at
`+0x70`, state at `+0x80`, owner at `+0x84`, game pointer at `+0x8c`,
and sprite at `+0xac`.
