# Exact match

`ParcelManager::update_track_parcels` walks its 50 fixed `Parcel` records and
makes the native vtable call for every nonzero state. The manager owns slot
storage; individual parcels only borrow the subgame, Player, and sprite
handles. Android and iOS retain this owner as `cRParcelManager::AI()`. The
shared typed version remains 100% (16/16) with a narrow dispatch overlay used
only to express the native virtual call without adding a second C++ vptr to
the explicit `BodNode` layout.
