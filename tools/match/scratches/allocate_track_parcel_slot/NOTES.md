# Exact match

`allocate_track_parcel_slot` scans the 50-entry parcel runtime pool by testing
each slot's `state` field at `+0x38` with stride `0x8c`. It returns the first
inactive slot, or reports `Too Many Parcels increase RPARCEL_MAXIMUM` and
returns null if every slot is active.

The exact source shape keeps both the recovered index and the state-field
cursor. The bounded `while (index < 50 && *state != 0)` condition preserves
the native top-tested loop, while the in-loop exhaustion check avoids a
duplicate post-loop error path.
