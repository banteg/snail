# initialize_track_health_pickup_runtime @ 0x408510

Exact initializer for one authored `SubHealth` (`cRSubHealth` cross-port).

- Focused Wibo result: 100%, 7/7 instructions, with 2 masked operands OK.
- The scratch now uses the primary `SubHealth` type instead of a scratch-local
  runtime class; `TrackHealthPickup` remains a compatibility alias.
- The method casts through `BodBase` only for `initialize_bod_base()` and the
  vtable store. This keeps the exact initializer shape while confirming that
  the promoted pickup's first `0x38` bytes are the reused BOD base prefix.
- The installed table at `0x497320` points directly to
  `update_track_health_pickup`, independently agreeing with Android/iOS
  `cRSubHealth::AI()`.
