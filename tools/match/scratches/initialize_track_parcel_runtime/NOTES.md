# Exact match

`initialize_track_parcel_runtime` @ `0x408860` is the constructor-like proof
that `TrackParcelRuntime` embeds the shared `BodBase` prefix. It initializes
that base, replaces the vtable with the parcel updater table, and returns the
same slot. The shared inherited layout remains 100% (7/7, two clean operands).
