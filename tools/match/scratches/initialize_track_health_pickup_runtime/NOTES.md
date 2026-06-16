# initialize_track_health_pickup_runtime @ 0x408510

Exact initializer for the health-pickup runtime slot.

- Focused Wibo result: 100%, 7/7 instructions, with 2 masked operands OK.
- The scratch now uses the promoted `TrackHealthPickup` type instead of a
  scratch-local runtime class.
- The method casts through `BodBase` only for `initialize_bod_base()` and the
  vtable store. This keeps the exact initializer shape while confirming that
  the promoted pickup's first `0x38` bytes are the reused BOD base prefix.
