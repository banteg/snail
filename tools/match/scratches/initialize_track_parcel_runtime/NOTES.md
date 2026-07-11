# Exact match

`initialize_track_parcel_runtime` @ `0x408860` is the constructor-like proof
that the authored `Parcel`/`cRParcel` embeds the shared `BodBase` prefix. It
initializes that base, replaces the vtable with `g_parcel_vtable`, and returns
the same slot. The table's sole entry is `update_track_parcel @ 0x4431d0`.
Together with the native `Size of cRParcelManager` ledger, the constructor
closes the primary `ParcelManager` owner around 50 inline `0x8c` records. The
shared inherited layout remains 100% (7/7, two clean operands).
