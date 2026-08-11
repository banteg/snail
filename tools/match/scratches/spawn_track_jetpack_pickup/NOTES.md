# spawn_track_jetpack_pickup @ 0x43d890

Live source map for `cRSubGame::AddJetPack(cRSubLoc*, cRSubGoldy*)`.

Current match:

- `87.29%`, `147/144` candidate/target instructions, with a `44/144` exact
  prefix, `9` clean masked operands, and no unresolved or mismatched
  references.
- The scratch uses the primary `JetPack` field names, the shared
  `BodList`/`BodNode` active-list shape, and the native bounded singleton
  traversal. The three-instruction candidate surplus is confined to the
  lane-wall tile compare schedule (`mov cl, 0xe` once in native versus two
  local byte-load/constant pairs in the candidate).
- The sprite output copy is now the same typed `Vector3` assignment accepted in
  the health spawner, reducing the tail residual to the bob-phase store versus
  `world_z` conversion scheduling.

Evidence:

- Allocates the single jetpack pickup runtime at `subgame +0x355e64`; the
  shared parent layout now lives in `track_jetpack_pickup.h`.
- The collision-visible lanes are inherited `BodBase::position +0x10`,
  `state +0x38`,
  `owner +0x3c`, `sprite +0x64`, `source_cell +0x68`, `bob_phase +0x6c`,
  and `bob_phase_step +0x70`, matching the corrected
  `handle_subgoldy_collisions` offsets `position 0x355e74` and
  `state 0x355e9c`.
- The runtime footprint is `0x19c`; `initialize_track_jetpack_pickup_runtime`
  proves the parent has two embedded renderable bodies beyond the
  collision/spawn prefix.
- The lateral `x` correction is lane/tile dependent: lane `3` shifts `+0.5`
  when the neighboring row bytes are `14`; lane `4` shifts `-0.5` for the
  mirrored neighbors.
- Sprite texture `124` is allocated at size `1.5`, and the bob phase uses the
  same numeric float-to-int parity test seen in the health pickup spawner.
- The active-list add path matches the same insertion semantics as health:
  insert the pickup before the old first node, clear the new head's prev link,
  and set the `0x200` linked bit.

2026-06-16 vtable correction: the earlier "different local view" was a shifted
symbol assumption. `0x43efb0` is the jetpack pickup updater installed by the
parent vtable, while the exact `0x43ee50` updater belongs to the speedup
singleton.

2026-06-16 pool-overlay/list-splice pass: the spawner now mirrors the health
pickup scratch's shifted slot-base shape, keeping `esi` based at
`subgame + slot_index * 0x19c` while using the shared
`cRSubGame::jetpack_pickup` member and promoted `JetPack`
fields. The active-list splice was
also reordered to put the empty-list case first, matching native fallthrough
and the health pickup shape. Focused Wibo improves from `52.86%` (`136/144`,
prefix `25/144`) to `73.76%` (`138/144`, prefix `31/144`), with all `9`
masked operands still OK.
Rejected follow-ups: pointer-to-local staging for the initial `PositionBits`
copy compiled identically, a local wall-tile byte compiled identically, and an
explicit odd-z bob-phase `else` regressed to `72.22%` by reversing the tail
block order.

2026-06-16 Vector3 staging correction: same correction as health. The native
function materializes float-sized `x/y/z` locals before storing the pickup
`world_position`, so the scratch now uses `Vector3 staged_position` instead of
the raw `PositionBits` view. Focused Wibo improves from `73.76%` to `79.30%`,
candidate size from `138/144` to `141/144`, and prefix from `31/144` to
`44/144`, with all `9` masked operands still OK. Retesting signed/named
wall-tile constants remained codegen-neutral and did not recover the native
`mov cl, 0xe` ordering, so the source keeps direct tile-id comparisons.

2026-06-19 pickup bob-tail pass: spelling the odd-z case as an explicit
early-return tail improves focused Wibo from `79.30%` to `81.79%`. Native
sets `bob_phase` to zero before the `__ftol` parity test, stores zero again on
the odd path, and has separate odd/even return tails; the early return is the
source shape that recovers that duplication. A destination `Sprite*` local for
the position copy stayed neutral at `79.30%`, direct typed `position.x/y/z`
stores regressed to `77.62%`, splitting the lane-wall test into nested or
independent `if` blocks stayed neutral at `79.30%`, and a `switch(lane)`
regressed to `76.49%`.

2026-06-20 pickup-family retry: focused Wibo still reports `81.79%`,
`147/144` candidate/target instructions, `44/144` prefix, and nine clean
masked operands. Naming the wall-tile constant as either `unsigned char` or
`int` is codegen-neutral and still leaves VC6 lowering the compares as
load-byte-then-`al = 0xe`, not native's early `cl = 0xe`. A destination
`Sprite* out_sprite` local for the final position copy is also neutral and
does not recover native's `edx` ownership. Before the typed copy below, the
first residual was still lane-wall compare scheduling, followed by list-splice
and position-copy register ownership.

2026-06-20 typed sprite-position copy: replacing the raw `DWORD*`
`out_position[0..2]` stores with `sprite->position = *live_position` improves
focused Wibo from `81.79%` to `86.60%`, with candidate size still `147/144`,
prefix `44/144`, and nine clean masked operands. The retained residual is now
the lane-wall constant/register schedule plus the independent bob-phase zero
store moving after the `world_z` `fld`; the typed copy matches the health
spawner's accepted source idiom.

2026-06-21 bob-phase pointer scheduling: writing the bob phase through a local
`float* bob_phase` keeps the initial zero store ahead of the `world_z` `__ftol`
conversion and improves focused Wibo from `86.60%` to `87.29%`, still with
`147/144` candidate/target instructions, prefix `44/144`, and nine clean
masked operands. The same score is possible with a raw `DWORD*`, but the float
pointer keeps the source semantic. Lane-wall probes using local
`unsigned char`, `char`, `int`, nested `if`, constant-left comparisons, and a
`switch` did not recover native's `mov cl, 0xe` compare schedule; the switch
form regressed to `83.85%`.

## 2026-07-11 authored owner and void contract

- The singleton is now primarily `JetPack`, matching Android/iOS `cRJetPack`;
  the primary shared owner is `JetPack`.
- Android `cRSubGame::AddJetPack(cRSubLoc*, cRSubGoldy*)` initializes the same
  singleton and reaches its epilogue without establishing a result. Windows
  callers also ignore EAX, whose occupied and success paths contain
  incompatible incidental values.
- Correcting the artificial `int` contract to `void` changes focused matching
  from 87.29% (147/144) to an honest 84.72% with exact 144/144 instruction
  count and all nine audited references clean. The fake result is not retained
  merely for register-allocation score.

## 2026-07-12 grid and active-list ownership

- The four former raw byte probes are exact `cRSubLoc` neighbors:
  `cell[-1].tile_id`, `cell[2].tile_id`, `cell[-2].tile_id`, and
  `cell[1].tile_id`. Their 0x54-byte stride explains every native displacement
  and removes the last anonymous grid access from this allocator.
- Android calls `cLinkedList<cRBod>::Add`; the Windows splice is now expressed
  through the same owned inline `BodList::add_bod` used by the health allocator.

Both changes are codegen-neutral at the honest 84.72%, `144/144` baseline with
nine clean references. The residual is limited to the void full-pool epilogue
and VC6's lane-14 constant/register schedule, not ownership.

2026-07-14 root-list closure: the singleton's inherited BOD now enters
`GameRoot::active_bod_list` directly. The honest 84.72%, 144/144 baseline and
all nine clean references are unchanged.

2026-07-14 BOD-base ownership: the cell anchor now lands in inherited
`JetPack::position`, while the same zero-offset `BodBase -> BodNode` enters the
active list. Exact constructor/updater evidence independently fixes the base;
this allocator stays byte-stable at the honest 84.72%, 144/144 baseline with
all nine operands clean.

2026-07-14 singleton traversal ownership: the occupied check now starts from
the owned `JetPack jetpack_pickup` member and advances a typed pointer. The
shifted receiver used by the remaining source shape derives its displacement
from `sizeof(JetPack)` rather than the unexplained 103-word stride, and the
inherited BOD conversion no longer needs a cast. Focused output remains the
honest 84.72%, 144/144 baseline, prefix 7, with all nine operands clean.

## 2026-07-14 shared pickup lifecycle ownership

The singleton availability test now names
`TRACK_PICKUP_STATE_INACTIVE`, and a successful spawn moves the authored
`cRJetPack` owner to `TRACK_PICKUP_STATE_ACTIVE`. Focused output remains
byte-stable at 84.72%, 144/144 instructions, prefix 7, with all nine operands
clean.

## 2026-07-14 analysis receiver and ABI closure

The stale BN `TrackPickupRuntime* __thiscall(Game*, ...)` prototype is replaced
by the cross-port- and caller-proven
`void __thiscall(cRSubGame*, cRSubLoc*, Player*)`. IDA replay verifies
the same declaration and receiver lvar. Refreshed artifacts now expose the
owned `jetpack_pickup` singleton, its lifecycle state, and honest empty
`return;` paths; incompatible incidental register values remain deliberately
unexported.

## 2026-07-17 singleton cursor ownership

The exact allocator retains `esi` at the shifted slot cursor and addresses the
singleton at `+0x355e64`; rebasing it to `JetPack*` would invent different
register ownership. The recovered analysis-only `JetPackSlotCursor` therefore
owns the prefix followed by one exact `0x19c`-byte `JetPack`. That object ends
at `0x356000`, exactly where the eight-record `SubHealth` pool begins. Applying
the cursor type to the exact MLIL variable makes both decompilers expose the
same nested BOD, sprite, source-cell, and bobbing owners while preserving the
native cursor shape.

## 2026-07-19 intrusive-list lifetime replay

The allocator's `233/EAX` lifetime is the borrowed address of
`GameRoot::active_bod_list.first`, so its real type is `BodNode **`, not
`JetPack **`. Preserving that exact identity removes Binary Ninja's false
`JetPack::vtable` traversal: both non-empty and empty branches now walk
`BodNode::list_prev/list_next`, matching IDA and the shared inline
`BodList::add_bod` source. The singleton remains owned by `cRSubGame`;
list membership does not create or transfer a JetPack owner. Focused matching
remains honestly unchanged at `84.72%`, `144/144` instructions, prefix `7/144`,
with nine clean masked operands.

## 2026-07-28 mobile-backed placement expression

Both mobile `cRSubGame::AddJetPack` bodies retain the complete
`cell position + (0, 1.5, 0)` placement before the Windows-only neighboring
lane correction. The scratch now represents that placement as one owned
`Vector3` result rather than separate x/y/z assignments. VC6 emits the same
144-instruction candidate, so the honest 84.72% score and all nine clean
references are unchanged.

## 2026-07-29 bounded singleton scan and lane schedule

The Windows allocator retains the same bounded scan shape recovered for the
health pickup pool: test the current slot state, advance the typed cursor by
the exact `0x19c` runtime size, then return from the inner bound check. Its
bound is one because `jetpack_pickup` is a singleton. Android and iOS
independently retain that singleton owner and occupied-state guard even though
their compilers collapse the traversal.

Restoring this authored bound improves focused matching from `84.72%` to
`87.29%` and extends the exact prefix from `7/144` to `44/144`. The candidate
grows from the target-aligned `144` instructions to `147`; that is an explicit
metric tradeoff rather than an exact match claim. The stronger source recovers
the complete native scan, while the three-instruction surplus is isolated to
the later lane-wall compares.

Three mutation sweeps covered 30 variants (25 unique): 3 improved, 11 were
byte-identical, and 16 regressed. Eight natural lane spellings—including
byte/int wall locals, nested branches, constant-left comparisons, and explicit
`else` blocks—were neutral; the `switch` form regressed. A full scan-by-lane
interaction matrix produced no further improvement. Native eagerly keeps tile
14 in `cl`, while VC6 materializes the constant separately for the two
candidate compares. No volatile access, fake external, or dummy operation was
introduced to force that register schedule.

## 2026-07-29 wall-constant owner closure

A fourth recorded sweep tests the remaining plausible scalar owners for tile
14: `SubLocTileId`, signed and unsigned byte/int locals, `const`, and
`register`, declared on both sides of the lane extraction. All six variants are
byte-identical at 87.29%, 147/144 instructions, prefix 44, and nine clean
references. VC6 eliminates every source local and retains the same two
load-byte/materialize-constant compare pairs; none induces native's single
eager `mov cl, 0xe`.

The ledger now contains 36 evaluations (31 unique), with 3 better, 17 neutral,
and 16 worse variants, one earlier sweep win, three trailing non-improving
sweeps, and no compile errors. Five repeated variants are the intentional
overlap between the earlier lane-only sweep and the scan/lane interaction
matrix. That history documents this backend register schedule but does not
define a stopping rule. No volatile local, fake global, or dummy use is justified, and the
stronger bounded-singleton source remains unchanged.

## 2026-08-12 recovery classification

The recovery is semantic-complete. The live Windows decompile and both mobile
bodies establish the `cRSubGame::AddJetPack` owner, singleton availability,
embedded `JetPack` lifecycle, source cell and lane-neighbor correction, active
BOD membership, sprite allocation and initialization, position handoff, and
bob-phase parity. All nine references are clean.

The three extra candidate instructions are confined to materializing wall tile
14 twice instead of keeping it once in `cl`; the later bob-tail difference is
equivalent floating-point scheduling. Neither hides a field, branch, or owner.
The completion judgment follows the native/mobile contract, not the old
experiment streak.
