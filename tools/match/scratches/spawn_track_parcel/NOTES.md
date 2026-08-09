# spawn_track_parcel

Exact match.

- Spawns one runtime parcel through exact `cRParcelManager::New()` allocation.
- The function is a `cRSubGame` method with two stack arguments. Callers
  pass a `Player*` hint as the second argument, but native ignores it and binds
  the runtime's owned `Player player` at `subgame+0x3bb764`.
- The parcel starts in state `1`, copies the requested world position to both
  parcel and sprite positions, assigns the Player owner pointer, and
  initializes the parcel sprite as white, visible, unrotated, and unit-scale.
- `bob_phase` starts at `0.5` for even integer z rows and `0.0` for odd rows;
  `bob_phase_step` is the native `0x3c520d21` float.
- `END=0x443854` excludes alignment/trampoline bytes after the final null
  return.
- The exact source shape keeps the non-null body explicit, returns from both
  bob-phase branches, and leaves the null return as the final tail block.
- The shared `cRSubGame` now carries the fixed parcel pool at +0x125e480;
  `cRParcelManager` owns 50 inline `cRParcel` records, while each `cRParcel` inherits
  its position from `BodBase` and borrows the
  embedded Player and SpriteManager handle. Keeping this scratch exact proves
  those ownership links for the update and collision paths.
- Android `cRSubGame::AddParcel(tVector*, cRSubGoldy*)` explicitly returns the
  allocated `cRParcel*` in `r0`, or null on exhaustion. This confirms that the
  exact Windows `cRParcel*` return is authored API semantics rather than a
  caller-ignored register artifact. iOS v1.9 adds the source `cRSubRow*`
  argument, but preserves the same SubGame/Parcel ownership relationship.

## 2026-07-14 parcel lifecycle ownership

The spawner now enters `PARCEL_STATE_TRACK_ACTIVE`, pairing the exact producer
with the manager's inactive-slot allocator and the collision consumer. Focused
matching remains exact at 96/96 instructions with all five operands clean.

## 2026-07-18 analyzer lifecycle replay

Native xrefs show two callers, `update_subgame` and
`update_row_event_display`. Both borrow the embedded manager through the
`cRSubGame` receiver; the returned `cRParcel*` remains manager-owned while
its Player, Sprite, and subgame links are borrowed. The paired replay now pins
that complete lifecycle and reanalyzes both producers plus
`handle_subgoldy_collisions`. Matching remains exact at 96/96 instructions
with all five operands clean.

The stable matcher key remains `spawn_track_parcel`, while its authored method
and VC6 spelling are `cRSubGame::AddParcel(...)` and
`?AddParcel@cRSubGame@@QAEPAVcRParcel@@PAUtVector@@PAVcRSubGoldy@@@Z`.
