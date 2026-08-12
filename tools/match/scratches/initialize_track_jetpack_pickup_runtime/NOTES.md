# initialize_track_jetpack_pickup_runtime @ 0x4084d0

Exact authored `cRJetPack::cRJetPack()` constructor: 17/17 instructions with
six clean masked operands and VC6 symbol `??0cRJetPack@@QAE@XZ`.

The native order constructs inherited `cRBod`, then each embedded `cRVapour`
at `+0x74` and `+0x108`, installing `g_vapour_vtable` immediately after each
child's `cRBodPos` construction, and finally installs `g_jet_pack_vtable`.
That interleaving is reproduced by an inline `cRVapour::cRVapour()` definition;
there is no claim that Windows retains a standalone constructor body.

The complete `0x19c` extent agrees with the native `Size of cRJetPack` ledger.
The table at `0x497318` points to `cRJetPack::AI @ 0x43efb0`, while the child
table at `0x49731c` points to `cRVapour::AI @ 0x4425f0`. `JetPack` remains a
compatibility typedef.
