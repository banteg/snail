# spawn_track_health_pickup @ 0x43d6c0

Live source map for `cRSubGame::AddHealth(cRSubLoc*, cRSubGoldy*)`.

Current match:

- `72.95%`, `122/122` candidate/target instructions, with `7` masked operands
  ok.
- The scratch now uses the promoted `TrackHealthPickup` field names for slot
  initialization and sprite ownership. The key source-shape fix is staging the
  cell position through a normal `Vector3` local, not the older raw-bit
  `PositionBits` view.

Evidence:

- `initialize_track_health_pickup_runtime` now uses this same promoted
  `TrackHealthPickup` type, casting through `BodBase` only for the exact base
  initializer and vtable store. That confirms the shared first `0x38` bytes
  are the BOD base prefix whose payload is reused as pickup world/state fields.
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
- The `Vector3` staging correction recovers the native position-local stack
  materialization. The remaining prefix break is now the order of the slot-index
  multiply/subtract versus the late `cell` reload.
- The active-list splice is now expressed through `BodList`/`BodNode`, but it
  still differs in register allocation and branch layout from the native splice.

2026-06-16 list-splice branch-order pass: reordered the shared active-list
insert source so the empty-list case is the fallthrough and the non-empty insert
is the taken branch. This matches the native splice direction also recovered in
the jetpack pickup spawner, improves focused Wibo from `48.98%` (`123/122`) to
`50.00%` (`122/122`), and keeps the `7` masked operands clean. The prologue and
staged-position copy remain the main residuals.

2026-06-16 Vector3 staging correction: BN and the target asm both show three
float-sized position locals before copying into `world_position`. Replacing the
raw `PositionBits` staging with an ordinary `Vector3 staged_position` recovers
that stack-local copy and corrects the earlier assumption that x/z needed a
raw-bit struct here. Focused Wibo improves from `50.00%` to `72.95%`, prefix
from `2/122` to `16/122`, with all `7` masked operands still OK.
