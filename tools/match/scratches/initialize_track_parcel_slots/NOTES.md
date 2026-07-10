# Exact match

`initialize_track_parcel_slots` initializes all 50 slots owned by the embedded
`TrackParcelPool`. Each inactive slot borrows the enclosing `SubgameRuntime`
at `g_game_base +0x74618`; no slot owns or allocates that backlink. The shared
typed version remains 100% (13/13, one clean operand).
