# Exact match

`ParcelManager::update_track_parcels` walks its 50 fixed `Parcel` records and
makes the native vtable call for every nonzero state. The manager owns slot
storage; individual parcels only borrow the subgame, Player, and sprite
handles. Android and iOS retain this owner as `cRParcelManager::AI()`. The
shared typed version remains 100% (16/16) with the common 4-byte
`BodAiDispatch` overlay used only to express the native slot-zero call without
adding a second C++ vptr to the explicit `BodNode` layout. This retires the
former parcel-local virtual shell and shares the same ABI fact with SubRing,
SubLoc, LogoLetter, GolbShot, and Player consumers.

The 2026-07-14 extent pass derives the update bound from
`ParcelManager::slots`. Its normalized listing remains byte-identical
(`068d76a8897514e58d677a360937f96f428a740632fd7ce8ec6919de7d0e62ca`)
and exact at 16/16 instructions.

## 2026-07-14 parcel lifecycle ownership

The manager now dispatches every state except `PARCEL_STATE_INACTIVE`, making
the slot-liveness contract explicit without assigning behavior to the two
unproduced state values. Focused matching remains exact at 16/16 instructions.
