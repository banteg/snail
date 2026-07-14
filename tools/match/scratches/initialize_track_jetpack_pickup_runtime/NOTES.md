# initialize_track_jetpack_pickup_runtime

`initialize_track_jetpack_pickup_runtime` @ 0x4084d0 is exact at 17/17
instructions with six clean masked operands. It is the Windows constructor for
the authored `JetPack` (`cRJetPack` cross-port) singleton at
`SubgameRuntime +0x355e64`.

The complete boundary is now closed:

- inherited 0x38-byte `BodBase`, then JetPack state through `+0x73`;
- embedded 0x94-byte `cRVapour` at `+0x74`;
- embedded 0x94-byte `cRVapour` at `+0x108`;
- exact end at `+0x19c`, the start of `SubHealth health_pickups[8]`.

Both child constructors install the authored cRVapour table at `0x49731c`;
the parent installs table `0x497318`, whose entry is
`update_track_jetpack_pickup`. The 0x19c extent exactly matches the native
`Size of cRJetPack` ledger. The primary shared owner is now `JetPack`.

2026-07-14 base inheritance closure: `JetPack` now invokes its inherited
`BodBase::initialize_bod_base()` directly. The parent remains exact at 17/17
instructions with six clean operands, both embedded Vapour constructors remain
unchanged, and the complete object still ends at `+0x19c`.
