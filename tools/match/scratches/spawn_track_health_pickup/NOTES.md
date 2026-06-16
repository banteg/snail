# spawn_track_health_pickup @ 0x43d6c0

Live source map for `cRSubGame::AddHealth(cRSubLoc*, cRSubGoldy*)`.

Current match:

- `48.98%`, `123/122` candidate/target instructions, with `7` masked operands
  ok.
- The scratch now uses the promoted `TrackHealthPickup` field names for slot
  initialization and sprite ownership. The key source-shape fix from the prior
  version, staging the cell position through the shared `PositionBits` local,
  is still present.

Evidence:

- Scans eight health pickup slots at `game + 0x356000`, stride `0x74`. The
  source keeps the native slot-base arithmetic and layers a typed
  `HealthPickupPoolSlotView::pickup` overlay over it, because a direct
  `Game` pool member made VC6 choose the wrong base register.
- Seeds the promoted partial `TrackHealthPickup` fields: `world_position +0x10`,
  `state +0x38`, `owner +0x3c`, `sprite +0x64`, `source_cell +0x68`,
  `bob_phase +0x6c`, and `bob_phase_step +0x70`.
- Allocates sprite texture `57`, marks sprite flag `0x800`, clears gravity and
  progress fields, and writes `size_start/size_end = 0.60000002f`.
- Writes `source_cell +0x68`; this is distinct from
  `TrackHealthPickup::visibility_cell +0x44`, which is read by
  `update_track_health_pickup`.
- Initializes `bob_phase +0x6c` from a numeric float-to-int conversion of
  `world_position.z`, matching the native `__ftol` lane: even z starts at
  `0.5f`, odd z stays `0.0f`.

This scratch intentionally keeps the game health pool base scratch-local until
the shared `Game` layout is recovered across health, jetpack, speedup, and the
collision walker.

Remaining mismatch:

- A plain `TrackHealthPickup* pickup = (TrackHealthPickup*)(slot_base + 874496)`
  local is source-plausible but wrong for this scratch: it rebases `esi` at the
  pickup object, drops the focused score to 40.00%, and changes the native
  `[slot_base + 0x356000 + field]` addressing into small member offsets. The
  padded scratch-local pool-slot view keeps the real struct visible without
  making that invalid register-ownership assumption.
- The typed `TrackHealthPickup` field view makes VC6 preserve `this` in `esi`
  near the prologue instead of using the original stack spill, so the prefix is
  shorter than the earlier word-indexed scratch.
- The active-list splice is now expressed through `BodList`/`BodNode`, but it
  still differs in register allocation and branch layout from the native splice.
