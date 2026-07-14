# Exact match

`ParcelManager::allocate_track_parcel_slot` scans its 50 inline `Parcel`
records by testing each slot's `state` field at `+0x38` with stride `0x8c`.
It returns the first inactive slot, or reports
`Too Many Parcels increase RPARCEL_MAXIMUM` and returns null if every slot is
active. Android independently retains this member as
`cRParcelManager::New()`.

The exact source shape keeps both the recovered index and the state-field
cursor. The bounded `while (index < 50 && *state != 0)` condition preserves
the native top-tested loop, while the in-loop exhaustion check avoids a
duplicate post-loop error path.

2026-06-16 layout assertion pass: `track_parcel_runtime.h` now asserts
`sizeof(Parcel) == 0x8c` and `sizeof(ParcelManager) == 0x1b58`.
This exact allocator, `update_track_parcels`, `spawn_track_parcel`, and the
parcel/ring loop in `handle_subgoldy_collisions` all consume the same 50-slot
pool geometry.

2026-07-14 traversal ownership: the state scan now advances a typed `Parcel*`
through `ParcelManager::slots` instead of adding the 0x23-word representation
of the 0x8c-byte stride. Matching remains exact at 18/18 instructions with both
operands clean.

## 2026-07-14 parcel lifecycle ownership

Allocation now tests `PARCEL_STATE_INACTIVE` directly. This closes the free
slot contract against reset and every updater teardown while preserving the
exact 18/18 instruction body and both clean operands.
