# spawn_track_health_pickup @ 0x43d6c0

Live source map for `cRSubGame::AddHealth(cRSubLoc*, cRSubGoldy*)`.

Current match:

- `90.08%`, `120/122` candidate/target instructions, with `7` masked operands
  clean and no unresolved or mismatched references.
- The scratch now uses the primary `SubHealth` field names for slot
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

2026-06-21 empty-list splice pass: writing the empty-list successor directly as
`node->list_next = 0` instead of reloading `(*first_ref)->list_next` improves
focused Wibo to `96.72%`, preserves `122/122` instruction-count parity, and
keeps all seven masked operands clean. The tied direct-zero variants all keep
the same score, while reload-through-`first_ref` spellings fall back to
`86.89%`; the remaining residual is the earlier slot-index subtract versus
late `cell` reload plus the target's reuse of the known-zero `first` value.

2026-07-03 empty-splice node-reuse pass: native reloads the freshly stored head
back into `ecx` before the `+0xc` next store, and the working spelling is
reassigning the existing `node` local (`node = *first_ref; node->list_next = 0;`)
between the prev and next stores. That reuses a live register lane instead of
allocating a fresh local, improving focused Wibo from `96.72%` to `97.54%` with
`122/122` instruction parity and all seven masked operands clean. Probed
alternatives all stayed at `86.89%` or worse: a fresh `head`/`reloaded` local,
a `BodNode*&` reference alias to the list head, repointing `first_ref` at the
next link, reusing `first` for the reload, storing `first` instead of literal
zero without the reload, the exact 100% `initialize_click_start` splice
spelling, and a `BodList*` typed local. Full-native splice spellings that
store through `(*first_ref)->list_next` flip the whole flags-test/OR region's
`eax`/`ecx` allocation and regress to `86.89%`. Storing `first` versus `0` in
the reuse shape is codegen-neutral; the literal-zero form is retained as the
clearer source. The only remaining residuals are the prologue `sub eax, ebx`
versus `mov ebp, [esp+0x1c]` scheduling swap (region 1) and the single
non-empty-splice `mov ecx, [ecx]` versus `mov eax, [ecx]` reload lane; staged
`cell`/`player` locals, split 29-word arithmetic, owner-store reordering, and
anchor-pointer staging were all codegen-neutral at `97.54%`.

2026-07-03 empty-list reload probes: the remaining 3-instruction residual is
one prologue transposition (`sub eax, ebx` vs the `player` arg load) plus the
empty-list branch reload register (`mov ecx, [ecx]` native vs `mov eax, [ecx]`
candidate). Three source shapes for the reload — direct
`(*first_ref)->list_next = 0`, a fresh `installed` local, and reusing the
`first` local — all regress to 86.89% by rotating eax/ecx ownership through
the earlier flags-test block. The `node = *first_ref` reuse is the only shape
that holds 97.54%. Treat as pinned register-ownership residual.

## 2026-07-11 authored owner and void contract

- The eight 0x74-byte records are now primarily named `SubHealth`, matching
  Android/iOS `cRSubHealth`; `TrackHealthPickup` is a compatibility alias.
- Android `cRSubGame::AddHealth(cRSubLoc*, cRSubGoldy*)` scans and initializes
  the same fixed array, then reaches its epilogue without establishing a
  result. Windows callers likewise ignore EAX, whose failure and success paths
  contain incompatible incidental values.
- The shared declaration is therefore corrected from an artificial `DWORD*`
  return to `void`. Focused matching honestly moves from 97.54% (122/122) to
  88.43% (120/122); all seven audited references remain clean. The lost shape
  is VC6's return/epilogue allocation, not missing behavior, and the fake
  pointer contract is not retained merely for score.

## 2026-07-12 shared list insertion recovery

Android calls `cLinkedList<cRBod>::Add` for the inherited pickup BOD. Moving the
already recovered empty/non-empty splice onto the owned inline `BodList` method
improves the honest void reconstruction from 88.43% to 90.08% while preserving
all seven audited references. The remaining differences are the occupied-pool
void epilogue and independent setup-tail scheduling, not list ownership.

2026-07-14 root-list closure: the inherited pickup BOD is inserted through
`GameRoot::active_bod_list`. Focused output remains 90.08%, 120/122
instructions, prefix 6/122, with seven clean operands.
