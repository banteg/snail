# Exact match

`initialize_track_parcel_runtime` @ `0x408860` is the exact constructor proof
that the authored `cRParcel` embeds the shared `BodBase` prefix. It initializes
that base and replaces the vtable with `g_parcel_vtable`; the constructor ABI
returns the same receiver. The table's sole entry is `update_track_parcel @
0x4431d0`, the verified cross-port `cRParcel::AI()` member. Together with the
native `Size of cRParcelManager` ledger, the constructor closes the primary
`cRParcelManager` owner around 50 inline `0x8c` records. The stable matcher key
binds the exact VC6 spelling `??0cRParcel@@QAE@XZ`; `Parcel` remains only
compatibility vocabulary. The shared inherited layout remains 100% (7/7, two
clean operands).
