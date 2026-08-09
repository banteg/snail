# initialize_track_jetpack_pickup_runtime

`initialize_track_jetpack_pickup_runtime` @ 0x4084d0 is exact at 17/17
instructions with six clean masked operands. It is the Windows constructor for
the authored `cRJetPack` singleton at `cRSubGame +0x355e64`.

The complete boundary is now closed:

- inherited 0x38-byte `BodBase`, then cRJetPack state through `+0x73`;
- embedded 0x94-byte `cRVapour` at `+0x74`;
- embedded 0x94-byte `cRVapour` at `+0x108`;
- exact end at `+0x19c`, the start of `SubHealth health_pickups[8]`.

Both child constructors install the authored cRVapour table at `0x49731c`;
the parent installs table `0x497318`, whose entry is
`update_track_jetpack_pickup`. The 0x19c extent exactly matches the native
`Size of cRJetPack` ledger. `JetPack` remains a compatibility typedef.

2026-07-14 base inheritance closure: `JetPack` now invokes its inherited
`BodBase::initialize_bod_base()` directly. The parent remains exact at 17/17
instructions with six clean operands, both embedded Vapour constructors remain
unchanged, and the complete object still ends at `+0x19c`.

2026-07-17 child inheritance closure: both embedded `Vapour` owners now derive
from the exact `RenderableBod` subobject this constructor initializes. The
temporary cast-only views are retired; the two child callback stores resolve
through their inherited bodies while the constructor remains exact at 17/17.

## 2026-08-09 primary cRJetPack ownership

The matcher now emits this leaf as the authored `cRJetPack::cRJetPack()`
constructor and selects the owner-qualified VC6 symbol
`??0cRJetPack@@QAE@XZ`. Live Windows disassembly shows the canonical sequence:
construct the inherited `BodBase`, construct both embedded `cRVapour` prefixes,
install their shared table, install the parent table, and return the receiver
in `eax`. Raw bytes at `0x497318` are `b0 ef 43 00 f0 25 44 00`: the parent
table points to `cRJetPack::AI @ 0x43efb0`, and the adjacent cRVapour table
points to `cRVapour::AI @ 0x4425f0`. The body remains exact at 17/17 with all
six references clean.

The automated mobile crosswalk leaves this constructor unverified because no
exported mobile constructor survives. That does not weaken the Windows
constructor shape or the independently preserved cRJetPack RTTI, vtable, size
ledger, and AI owner. The opaque parent lanes at `+0x40..+0x43` and
`+0x48..+0x63` remain unnamed, and the two cRVapour children remain
constructor-proved embedded owners rather than invented active trail state.
