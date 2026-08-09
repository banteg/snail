# refresh_fringe_object_draw_list @ 0x439b00

Exact match: 100.00%, 63/63 instructions.

This is the Windows callback for one authored `cRFringe`. It refreshes the
object's skirt tint from
`get_track_skirt_color`, then removes the object from the active BOD list and
pushes it onto the shared free stack once its `world_z` falls behind the live
fringe threshold at `Player::active_window_min_z`.

The exact source shape has two useful details:

- keep `world_z` in a `float` local before copying the returned `tColour`;
  a `double` local preserves the value semantically but emits an extra x87
  threshold load and regresses the match;
- spell the list removal as the same typed intrusive-list logic as exact
  `recycle_bod_to_free_list`, with the `0x200` missing-owner error as the
  direct branch and `0x40` active-iteration error as the second guard.

The Windows constructor installs the table at `0x497344`, whose entry points
directly here. Android's `cRFringe::AI()` is a four-byte no-op, so the class
identity is shared while the renderer-specific offscreen recycling behavior is
Windows-only. The authored class remains exact at 63/63 with eight
clean operands.

## 2026-07-13 root owners

The color refresh now reaches the embedded `GameRoot::subgame`, and teardown
borrows `GameRoot::active_bod_list`. The exact 63/63 object is unchanged,
confirming that `Fringe` owns its body and color while root/subgame owners
supply the shared list lifecycle and track-skirt color policy.

2026-07-14 cull-owner closure: the last raw threshold access now follows
`GameRoot::subgame.embedded_player()->active_window_min_z`, the same cull plane
used by the other pickup and hazard lifecycles. The canonical root pointer and
active-list owner preserve the exact 63/63 instructions and all eight operands.

## 2026-07-18 callback ABI closure

The live BN database still inferred this callback as
`float __fastcall(BodNode*)` from incidental register state. The installed
fringe vtable, ECX receiver, exact `Fringe::refresh_fringe_object_draw_list()`
source, and Android `cRFringe::AI()` identity establish the durable analyzer
ABI as `void __thiscall refresh_fringe_object_draw_list(Fringe*)`. This is an
ownership correction only; the exact 63/63 matcher remains unchanged.

## 2026-08-09 primary cRFringe::AI ownership

The matcher now defines this table-only callback as `cRFringe::AI()` and binds
`?AI@cRFringe@@QAEXXZ`; `Fringe` remains compatibility vocabulary for the
analyzer replay. Windows has no direct code xref: raw bytes `00 9b 43 00` at
`0x497344` are the sole table reference. The mobile crosswalk independently
marks the Android `cRFringe::AI()` owner verified with high confidence; no iOS
body is claimed. The exact Windows lifecycle body remains 63/63 with all eight
references clean.

Android's no-op does not erase the Windows renderer-specific tint refresh,
cull-plane test, or intrusive-list recycle. Conversely, those Windows actions
are not projected onto the compact mobile object. No Fringe-specific payload
lanes exist past the inherited 0x38-byte `BodBase` boundary.
