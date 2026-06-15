# update_track_jetpack_pickup @ 0x43ee50

Exact match under the standard `msvc6.5 /O2 /G5 /W3` profile.

Recovered behavior:

- skip when shared `TrackRuntimeCell +0x09` is hidden;
- state `0` returns immediately;
- state `2` unlinks the pickup from the shared `g_game_base + 0x5a8` bod list,
  pushes it onto the free stack, clears `0x200`, and kills the sprite;
- state `1` performs the same teardown once `world_z` falls behind
  `owner->interaction_max_z`.

The local source shape intentionally keeps the state-1 and state-2 unlink
blocks duplicated. VC6 otherwise merges the error tails and loses the exact
native layout.
