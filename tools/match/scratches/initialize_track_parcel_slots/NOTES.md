# Exact match

`ParcelManager::initialize_track_parcel_slots` initializes all 50 inline
`Parcel` records owned by the manager. Each inactive slot borrows the enclosing
`SubgameRuntime` at `g_game_base +0x74618`; no slot owns or allocates that
backlink. Android independently retains this member as
`cRParcelManager::Init()`. The shared typed version remains 100% (13/13, one
clean operand).
