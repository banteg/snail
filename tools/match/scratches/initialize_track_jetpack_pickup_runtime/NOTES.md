# initialize_track_jetpack_pickup_runtime

`initialize_track_jetpack_pickup_runtime` @ 0x4084d0 is exact at 17/17
instructions with six clean masked operands. It is the Windows constructor for
the authored `JetPack` (`cRJetPack` cross-port) singleton at
`SubgameRuntime +0x355e64`.

The complete boundary is now closed:

- inherited JetPack BOD prefix and state through `+0x73`;
- embedded 0x94-byte `cRVapour` at `+0x74`;
- embedded 0x94-byte `cRVapour` at `+0x108`;
- exact end at `+0x19c`, the start of `SubHealth health_pickups[8]`.

Both child constructors install the authored cRVapour table at `0x49731c`;
the parent installs table `0x497318`, whose entry is
`update_track_jetpack_pickup`. The 0x19c extent exactly matches the native
`Size of cRJetPack` ledger. `TrackJetpackPickup` is a compatibility alias.
