# spawn_track_parcel

Exact match.

- Spawns one runtime parcel from the exact `allocate_track_parcel_slot` pool.
- The function is a `SubgameRuntime` method with two stack arguments. Callers
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
- The shared `SubgameRuntime` now carries the fixed parcel pool at +0x125e480;
  `ParcelManager` owns 50 inline `Parcel` records, while each `Parcel` inherits
  its position from `BodBase` and borrows the
  embedded Player and SpriteManager handle. Keeping this scratch exact proves
  those ownership links for the update and collision paths.
- Android `cRSubGame::AddParcel(tVector*, cRSubGoldy*)` explicitly returns the
  allocated `cRParcel*` in `r0`, or null on exhaustion. This confirms that the
  exact Windows `Parcel*` return is authored API semantics rather than a
  caller-ignored register artifact. iOS v1.9 adds the source `cRSubRow*`
  argument, but preserves the same SubGame/Parcel ownership relationship.
