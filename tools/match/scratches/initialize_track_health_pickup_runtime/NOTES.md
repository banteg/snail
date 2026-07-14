# initialize_track_health_pickup_runtime @ 0x408510

Exact initializer for one authored `SubHealth` (`cRSubHealth` cross-port).

- Focused Wibo result: 100%, 7/7 instructions, with 2 masked operands OK.
- The scratch now uses the primary `SubHealth` type instead of a scratch-local
  runtime class; `TrackHealthPickup` remains a compatibility alias.
- The method now invokes inherited `BodBase::initialize_bod_base()` directly
  and installs the vtable through the inherited zero-offset object. This keeps
  the initializer exact while confirming that the pickup's first `0x38` bytes
  are the real BOD base, not an anonymous overlay.
- The installed table at `0x497320` points directly to
  `update_track_health_pickup`, independently agreeing with Android/iOS
  `cRSubHealth::AI()`.

2026-07-14 base inheritance closure: `SubHealth` now derives directly from
`BodBase`; its live `+0x10` position is inherited `BodBase::position`, and its
first authored field remains `state +0x38`. The constructor is still exact at
7/7 instructions with both masked operands clean.
