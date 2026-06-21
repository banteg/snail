# spawn_track_health_pickup @ 0x43d6c0

Live source map for `cRSubGame::AddHealth(cRSubLoc*, cRSubGoldy*)`.

Current match:

- `86.07%`, `122/122` candidate/target instructions, with `7` masked operands
  ok.
- The scratch now uses the promoted `TrackHealthPickup` field names for slot
  initialization and sprite ownership. The key source-shape fix is staging the
  cell position through a normal `Vector3` local, not the older raw-bit
  `PositionBits` view.
- The sprite output copy is now the normal `Vector3` assignment from the live
  pickup position into `sprite->position`; VC6 emits the same scalar stores
  with the native destination-register ownership.

Evidence:

- `initialize_track_health_pickup_runtime` now uses this same promoted
  `TrackHealthPickup` type, casting through `BodBase` only for the exact base
  initializer and vtable store. That confirms the shared first `0x38` bytes
  are the BOD base prefix whose payload is reused as pickup world/state fields.
- Scans eight health pickup slots at `subgame +0x356000`, stride `0x74`. The
  source keeps the native slot-base arithmetic by viewing the shifted slot base
  as a `SubgameRuntime*` and accessing `slot->health_pickups[0]`. A direct
  `this->health_pickups[slot_index]` member made VC6 choose the wrong base
  register.
- Seeds the promoted partial `TrackHealthPickup` fields: `world_position +0x10`,
  `state +0x38`, `owner +0x3c`, `sprite +0x64`, `source_cell +0x68`,
  `bob_phase +0x6c`, and `bob_phase_step +0x70`.
- Allocates sprite texture `57`, marks sprite flag `0x800`, clears gravity and
  progress fields, and writes `size_start/size_end = 0.60000002f`.
- Writes `source_cell +0x68`; this is distinct from
  `TrackHealthPickup::owner_game +0x44`, the reset-initialized subgame pause
  view read by `update_track_health_pickup`.
- Initializes `bob_phase +0x6c` from a numeric float-to-int conversion of
  `world_position.z`, matching the native `__ftol` lane: even z starts at
  `0.5f`, odd z stays `0.0f`.

This scratch now uses the shared `SubgameRuntime::health_pickups` layout, but
keeps the shifted slot-base source shape because rebasing to a direct pickup
pointer still does not match native register ownership.

Remaining mismatch:

- A plain `TrackHealthPickup* pickup = (TrackHealthPickup*)(slot_base + 874496)`
  local is source-plausible but wrong for this scratch: it rebases `esi` at the
  pickup object, drops the focused score to 40.00%, and changes the native
  `[slot_base + 0x356000 + field]` addressing into small member offsets. The
  shifted `SubgameRuntime*` view keeps the real struct visible without making that
  invalid register-ownership assumption.
- The `Vector3` staging correction recovers the native position-local stack
  materialization. The remaining prefix break is now the order of the slot-index
  multiply/subtract versus the late `cell` reload.
- The active-list splice is now expressed through `BodList`/`BodNode`, but it
  still differs in register allocation and branch layout from the native splice.
- The remaining sprite/setup tail residual after the typed `Vector3` copy is
  the independent zero bob-phase store being scheduled before the `world_z`
  `fld`; native loads `world_z`, then stores zero before entering the `__ftol`
  lane.

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

2026-06-16 bob-phase if/else retry: replacing the default-zero plus even-z
override with a natural `if even -> 0.5f else -> 0.0f` branch regressed focused
Wibo from `72.95%` to `71.02%` and grew the candidate to `123/122`
instructions.

2026-06-19 pickup bob-tail pass: using the odd-first branch instead matches
the target tail direction better and improves focused Wibo from `72.95%` to
`74.80%`, with candidate size `124/122` and all `7` masked operands still OK.
Native stores zero before `__ftol`, stores zero again on the odd path, and
jumps over the even `0.5f` store to the shared step-index tail; this source now
keeps that explicit odd-zero lane.

2026-06-20 pickup-family retry: focused Wibo still reports `74.80%`,
`124/122` candidate/target instructions, `16/122` prefix, and seven clean
masked operands. Spelling the 29-word slot stride as
`slot_index + (slot_index * 7) * 4` is codegen-neutral: VC6 still schedules the
late `cell` reload before `sub eax, ebx`, while native finishes the slot-index
subtract first. Explicit raw `zero` and `size_bits` locals for the sprite setup
are also neutral and leave the existing `ecx`/`eax` register reversal. Keep the
current shifted `SubgameRuntime*` view and typed sprite stores; the remaining
gaps are scheduling/register ownership, not a new pickup layout.

2026-06-20 typed sprite-position copy: replacing the raw `DWORD*`
`out_position[0..2]` stores with `sprite->position = *live_position` improves
focused Wibo from `74.80%` to `85.37%`, with candidate size still `124/122`,
prefix `16/122`, and seven clean masked operands. This also matches the
jetpack spawner's accepted source idiom. A separate `node_flags` snapshot and
an explicit `slot_words = 29 * slot_index` local were codegen-neutral, leaving
the initial slot arithmetic and active-list register reversal unchanged.

2026-06-21 native-tail value pass: spelling the decompiler-backed incidental
return as `result = 7 * (slot_index + 30156)` and using
`step_index + (result << 2)` for the 29-word bob-step store improves focused
Wibo from `85.37%` to `86.07%` and restores `122/122` instruction-count
parity. A separate `store_index = 29 * step_index` local is codegen-neutral and
keeps the extra multiply in the tail, while the `result`-based address reuses
the native live return value. The first mismatch remains the earlier
slot-index subtract versus late `cell` reload; the active-list register
reversal and bob-phase `fld` schedule are unchanged.

2026-06-21 bob-phase pointer scheduling: matching the jetpack spawner, writing
the bob phase through a local `float* bob_phase` keeps the initial zero store
ahead of the `world_z` `__ftol` conversion and improves focused Wibo from
`86.07%` to `86.89%`, with instruction-count parity and seven clean masked
operands preserved. A raw `DWORD*` pointer looked equivalent semantically but
regressed to `67.21%` by changing the sprite setup and tail into bit-mask
arithmetic, so keep the typed float pointer.
