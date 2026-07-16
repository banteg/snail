# spawn_track_ring_or_special_effect @ 0x43df10

Live source map for the authored ring/special-effect spawner.

Current match:

- `93.10%`, `349/347` candidate/target instructions, prefix `20/347`, with
  `74` masked operands ok, one explicit jump-table-label mismatch, and no
  unresolved operands.
- All nine authored kind paths are present with their native RNG streams. The
  remaining differences are a redundant bounded-scan proof check, two x87
  store schedules, activation-store scheduling, and local branch labels.
- No compiler flag, volatile barrier, artificial return, or matcher-only state
  is retained.

Evidence:

- The ring/special-effect runtime bank is two parent slots at
  `game + 0x35b78c`, stride `0x1f8`.
- Parent list fields are the usual bod/list header lanes:
  `list_flags +0x04`, `list_prev +0x08`, and `list_next +0x0c`; the
  active-list bit is `0x200`. The older scratch-local `next`/`prev` labels
  were offset-correct but directionally misleading against `BodNode`.
- The spawner writes parent `owner_player +0x84`, `kind +0x88`,
  `owner_lives_snapshot +0x8c`, `state +0x80`, `active_phase +0x1e0`, and
  `active_phase_step +0x1e4`.
- Parent `+0x1d0` is not installed here; prior runtime notes and the
  initializer show that rate source is already present by the time child
  particles are initialized.

Native switch map:

- Kinds `0..4` are semantically similar orbiting track effects but native keeps
  separate authored RNG tags and duplicated position setup:
  `0 -> RR/RR1`, `1 -> RR2/RR3`, `2 -> RR4/RR5`, `3 -> RR6/RR7`,
  `4 -> RR8/RR9`.
- Kind `2` is the taller/deeper placement (`y + 3.5`, `z + 17.0`); kinds
  `0`, `1`, `3`, and `4` use `y + 2.5`, `z + 6.0`.
- Kinds `5..8` are also separate in native for RNG tags:
  `5 -> RR10`, `8 -> RR11`, `6 -> RR12`, `7 -> RR13`. All use the
  ring-speed-derived `active_phase_step`.
- The current source recovers every path separately. Source case order follows
  the native physical family order for the moving effects (`5`, `8`, `6`,
  `7`), so `RR10` through `RR13` align without operand substitutions.

Type consolidation:

- `RingOrSpecialEffectParent` now inherits shared `RenderableBod`, including
  the `BodNode` active/free-list prefix. The active/free anchor is modeled as
  `RingOrSpecialEffectListAnchor` (`BodList`) in
  `tools/match/include/ring_special_effect_types.h`.
- 2026-06-17 renderable inheritance correction: the spawner initializes the
  inherited transform at `slot +0x38`, and the particle/updater/collision
  consumers read the parent center as `transform.position` at `+0x68`. The
  current scratch expresses both through the typed manager-relative slot view
  recovered in the 2026-07-16 pass below.
- 2026-06-16 lives-snapshot correction: parent `+0x8c` is now named
  `owner_lives_snapshot`. The spawner stores `Player::lives` (`+0x404`) and
  `update_ring_or_special_effect_parent` compares the current lives count against that
  snapshot before entering state `4`; the same player lane is also used by
  `handle_subgoldy_collisions` and `update_subgoldy`.
- 2026-06-16 correction: `+0x80` is named `state`, not `active`; the virtual
  updater uses `0` as inactive, `1` as normal orbit, and `2..5` as transition
  states.
- 2026-06-16 source-shape pass: the free-slot scan now uses the same explicit
  break/advance/overflow spelling as the garbage pool scans, recovering the
  native `sub esp, 0x10` prologue and a 22-instruction prefix. The placement
  switch now stages a local `Vector3` before copying to the parent position,
  and keeps a scratch-local `slot_position` view at `slot_base +0x35b7f4`
  because native holds the unadjusted game-relative slot base through the
  authored placement arms. This improves the score from 36.83% to 49.82%.
- A delayed `slot_position` declaration reached 50.09%, but introduced an
  unresolved switch-table operand. Keep the 49.82% spelling because its operand
  audit is cleaner.
- 2026-06-16 active-list branch-order pass: the shared root active-list
  insert now puts the empty-list case first, matching the health and jetpack
  pickup spawners' native list shape. Focused Wibo improves from `49.82%` to
  `51.23%` with the same 34 clean masked operands and the same eight known
  switch-grouping mismatches.
- 2026-06-16 rejected owner/kind ordering probe: moving
  `slot->owner_player = player` before the `kind` local looks closer to the
  target's immediate owner store, but it changes register ownership and
  regresses focused Wibo from `51.23%` to `44.99%`. Keep the current
  `kind`-then-owner source order until the surrounding switch shape changes.
- 2026-06-16 ring pool promotion: the shared header now records
  `RingOrSpecialEffectPool` as two parent slots at `game+0x35b78c`, stride
  `0x1f8`, total `0x3f0`. This is promoted from the spawner's pool scan and
  corroborated by the collision consumer; the spawner source remains
  raw/base-shaped because that is part of its current best codegen form.
- 2026-06-21 subgame receiver cleanup: the method now uses the shared
  `SubgameRuntime` receiver and its existing `subgame_rate`, `level_mode`,
  `base_subgame_rate`, and `get_track_grid_cell_at_world_position` members
  instead of a scratch-local `Game` shell. Focused Wibo remains `51.23%`,
  `223/347`, with the same `34` clean masked operands and the same eight known
  switch-grouping mismatches.

2026-07-10 pool ownership and source-order pass:

- `SubgameRuntime` now owns a typed `RingOrSpecialEffectPool` at `+0x35b78c`.
  The two parents and each parent's ten particle records are embedded storage;
  `owner_player`, `rate_source`, and particle `parent` are non-owning links.
  The source row cell is sampled for placement but is not retained by the
  parent.
- Computing the selected pool slot before the phase-rate expression lets VC6
  retain the incoming Player in `ebx`, improving the focused score from
  `51.23%` to `52.28%`. Using the typed embedded slot/transform view improves
  it again to `52.37%` while removing raw `+0x35b78c/+0x68` ownership math.
- Declaring the position view early but assigning it immediately before the
  kind switch recovers six more exact prefix instructions and reaches
  `53.45%`, `218/347`, prefix `28/347`.
- The native nine-entry table at `0x43e44c` is now curated as
  `spawn_track_ring_or_special_effect_kind_jump_table`. Its content honestly
  mismatches the compilable grouped switch, converting the former unresolved
  operand into an explicit ninth mismatch.
- Retesting a separate authored kind-1 `RR2`/`RR3` arm with its phase-step
  store inside the arm still makes VC6 exit without producing `scratch.obj`.
  The later 2026-07-13 pass below recovers the real arm while preserving the
  store through a post-switch semantic tail.

2026-07-11 authored class names:

- The two embedded parent slots are now `SubRing`, and their ten inline
  children are `SubRingStar`, following the preserved iOS/Android
  `cRSubRing` and `cRSubRingStar` symbols.
- `SubRingPool` owns the fixed storage; Player, SubgameRuntime rate source,
  child parent links, and Sprite pointers retain their borrowed/manager-owned
  lifetimes. Focused matching remains 53.45%, 218/347.

## 2026-07-13 void AddRing contract and shared dispatch

- All five Windows `update_subgame` callsites discard EAX. The independent iOS
  `cRSubGame::AddRing` body returns from its pool-full and invalid-cell paths
  without establishing a result and ends by invoking `cRSubRing::AI()`.
- `spawn_track_ring_or_special_effect` is therefore `void`. The fabricated
  `TrackRowCell*` return and scratch-local return-valued virtual class are
  retired in favor of the shared, cast-only `BodAiDispatch` ABI view.
- VC6 now coalesces the void early exits and no longer preserves the old
  incidental return registers. The honest focused result is 51.07%, 213/347
  instructions, prefix 9/347, with 34 clean operands and the same nine
  documented grouped-switch mismatches. No barrier or dummy return is retained
  to recover the former score.

## 2026-07-13 VC6 optimizer failure boundary

- The authored kind-1 arm was bisected under the normal `/O2 /G5 /W3` build.
  Its placement, `RR2` x randomization, and `RR3` phase call all compile; adding
  the `active_phase_step = default_phase_step` tail makes VC6 delete
  `scratch.obj` and exit `50` after only echoing `scratch.cpp`.
- `WIBO_DEBUG=1` confirms the guest compiler raises its `INTERNAL COMPILER
  ERROR` path. `/Zm200` through `/Zm1000` do not change the failure, so this is
  not the compiler front-end heap limit. Disabling global optimization with
  `/Og-` or frame-pointer omission with `/Oy-` avoids it, which localizes the
  failure to the optimized backend/tail-merging shape; neither flag is retained
  because the native target was built with the normal `/O2` profile.
- Reordering the phase-step store, sharing it through an explicit label, and
  taking a typed pointer to the field still trigger the ICE. The grouped switch
  was the honest compilable partial at this point; no volatile barrier, fake
  return, raw offset, or non-native compiler flag is kept.

## 2026-07-13 authored kind-1 path

- Kind `1` now has its real duplicated placement path and authored `RR2`/`RR3`
  streams. Moving only its ordinary `active_phase_step = default_phase_step`
  store to a `kind == 1` tail immediately after the switch avoids the verified
  VC6 backend failure without changing behavior or introducing matcher-only
  state.
- Focused matching improves from `51.07%`, `213/347` candidate/target
  instructions, prefix `9/347`, and `34` clean operands to `52.86%`, `247/347`,
  prefix `3/347`, and `45` clean operands. Known masked mismatches fall from
  nine to six, with no unresolved operands.
- Fully duplicating kinds `0..4`, sharing their outer locals, or adding a
  distinct kind `4` arm still hits the same VC6 internal compiler error. A
  distinct kind `3` or kind `8` arm compiles but regresses correspondence, so
  neither is retained. The kind-1 recovery is the bounded honest improvement.

## 2026-07-14 authored moving-effect paths

- The native switch carries distinct random streams for moving-effect kinds
  `5` through `8`: `RR10`, `RR12`, `RR13`, and `RR11`, respectively. Binary
  Ninja also shows four independent placement paths whose identical phase and
  speed calculation is tail-merged by VC6.
- Restoring the complete four-arm family gives the optimizer the native merge
  opportunity that was absent from the earlier isolated kind-8 probe. Focused
  matching improves from `52.86%`, `247/347` candidate/target instructions,
  prefix `3/347`, and `45` clean masked operands to `55.14%`, `295/347`, prefix
  `3/347`, and `42` clean masked operands. All six remaining masked mismatches
  are explicit and none are unresolved.
- Retesting the ordinary kind-1 phase-step store inside its authored arm after
  this switch expansion still makes VC6 exit `50` without producing
  `scratch.obj`. The verified post-switch semantic tail remains; no compiler
  flag, volatile barrier, or dummy state was introduced to evade the backend
  failure.

## 2026-07-14 authored kind-3 path

- With the complete moving-effect family present, the independently authored
  kind-3 placement arm now gives VC6 a useful merge graph. Restoring its
  `RR6`/`RR7` streams improves focused matching from `55.14%`, `295/347`
  candidate/target instructions, prefix `3/347`, and `42` clean operands to
  `64.09%`, `327/347`, prefix `3/347`, and `48` clean operands. Ten masked
  mismatches remain explicit and none are unresolved.
- Kind `4` is the only placement stream still coalesced with kind `0`. A
  distinct `RR8`/`RR9` arm continues to trigger VC6 exit `50` in every bounded
  native-semantic spelling tested: staged or direct position writes, an in-arm
  phase-step store, the existing post-switch store pattern, and no phase-step
  store at all. Those probes were reverted rather than retaining an incomplete
  or optimizer-directed implementation.
- The caller declaration remains `float random_float_below(...)`. Although the
  standalone callee is reconstructed with a wider return type, this target
  caller performs `fcomp dword` and `fmul dword` operations. Declaring the call
  as `double` changes those to qword operations and regresses focused matching
  to `61.13%`; it also does not remove the kind-4 compiler failure.

## 2026-07-14 root-list closure

The manual native-order parent splice now begins at
`GameRoot::active_bod_list`; its local `SubRingListAnchor` view only preserves
the authored `SubRing*` link types. Focused output remains 64.09%, 327/347
instructions, prefix 3/347, with 48 clean operands and the same ten explicit
switch-family mismatches.

## 2026-07-14 pool-scan ownership

The compiler-sensitive free-slot scan still advances a byte pointer, but its
base now derives from `offsetof(SubgameRuntime, ring_effects)` and its step from
`sizeof(SubRing)`. This removes the final hard-coded `+0x35b78c` pool address
and `0x1f8` parent stride without changing the emitted code. Focused output
remains honestly at 64.09%, 327/347 instructions, with 48 clean operands and
the same ten explicit kind-switch mismatches.

## 2026-07-14 fixed parent and child extents

The runtime constructor and size ledger prove two embedded `0x1f8` `SubRing`
parents, while the exact particle initializer and parent updater prove ten
embedded `0x20` `SubRingStar` children per parent. The shared owner now carries
`SUB_RING_POOL_CAPACITY` and `SUB_RING_PARTICLE_COUNT`; the free-parent scan no
longer repeats raw `2`, and every child loop borrows the same bound.

All five dependent normalized listings remain byte-identical:

- spawner: `cff66af6bf1bdff20727ebc2c6018b82b6cb9173a2273a3c02e65af56973cc9c`
- particle initializer: `a8c10dd83dfdc6db3bc0dd25b8b9709dd1e0c0b973e1f28ebabb14d9482adcc4`
- parent updater: `0940726eee8e7a0a108d1a2d58301241c610d08414c729dc7685b0f5f9950488`
- parent constructor: `a02f4e5d58e4322ce0393c0db796f2d37ae5cc9bb63372a84ae6c8c25f7c3bf1`
- runtime constructor: `755c2d4b3862bccde9a1fae74b792b0500699dda1c378c9f673ef0c27b829bba`

## 2026-07-14 ring kind and lifecycle ownership

The spawner now accepts and stores `SubRingKind`, and its free-slot/activation
stores use `SubRingState`. Producer-backed values distinguish default normal,
randomized slow, explosive-ramp, and the four authored row kinds. Values `0`
and `1` remain explicit unknown tokens because no live Windows producer is
recovered. Focused output remains 64.09%, 327/347 instructions, prefix 3/347,
with 48 clean operands and the same ten documented switch-grouping mismatches.

## 2026-07-15 durable owner replay

Both decompilers now replay the spawner on its real `SubgameRuntime*` receiver,
typed `SubRingPool` storage, `SubRingKind` input, and `SubRingState` lifecycle.
The paired exports agree with the databases and retire IDA's stale raw-integer
receiver and result-bearing prototype. This is ownership-only: focused output
remains honestly 64.09%, 327/347 instructions, prefix 3/347, with 48 clean
operands and the same ten explicit switch-family mismatches.

## 2026-07-15 authored integer kind contract

iOS v1.5/v1.9 preserve `cRSubGame::AddRing(cRSubLoc*, int,
cRSubGoldy*, float)`, so the public kind argument is an ordinary integer at
the authored API boundary. Windows code generation is byte-identical when the
matcher and analysis prototypes use `int`; the selected parent still stores a
typed `SubRingKind` after the switch validates and normalizes that value.

Restoring the remaining distinct kind-4 `RR8`/`RR9` arm was retested with the
correct integer signature, but VC6 still exits through its optimizer ICE
without producing an object. An explicit shared-tail spelling compiles but
regresses to 61.29%, and a semantic tag-selection spelling regresses to
60.03%, so both were reverted. The honest frontier remains 64.09%, 327/347
instructions, with 48 clean operands and ten explicit switch-family
mismatches; no optimizer barrier, volatile state, or artificial control flow
is retained.

## 2026-07-16 complete authored switch and slot cursor

- The optimizer-failure boundary above was caused by the scratch widening each
  randomized x offset to `double`. Windows multiplies these lanes with dword
  constants, and Android independently keeps them as `float`. Restoring float
  locals and `3.0f` both removes the qword arithmetic and lets ordinary VC6
  `/O2 /G5 /W3` compile the complete kind-4 `RR8`/`RR9` path. The kind-1
  phase-step store also returns to its own arm; the post-switch workaround is
  gone.
- The iPhone v1.5 binary places
  `cRSubGame::AddRing(cRSubLoc*, int, cRSubGoldy*, float)` at `0x1f710`, size
  `0x800`, in `SubGame.o`. Android's body at `0x69eb8` independently mutates
  the integer kind argument and preserves the distinct `RR` through `RR13`
  streams. The Windows source now mutates `requested_kind` directly instead of
  inventing a second value owner.
- `SubRingSlotCursor` is a typed manager-relative view: its prefix is derived
  from `offsetof(SubgameRuntime, ring_effects)` and its payload is one
  `SubRing`. VC6 therefore retains the native `SubgameRuntime + index *
  sizeof(SubRing)` cursor while every large displacement remains tied to the
  real embedded owner. Once placement and activation finish, the source borrows
  `&slot_cursor->ring`; the compiler performs the same one-time cursor-to-object
  handoff before the active-BOD splice and child initialization.
- The pool search is a bounded two-slot scan followed by an explicit exhausted
  check. This recovers the native pool-full epilogue and a 20-instruction exact
  prefix; VC6 retains one redundant proof comparison on the found path.
- Moving-effect source order follows the native physical blocks (`5`, `8`,
  `6`, `7`), eliminating the former `RR11`/`RR12`/`RR13` operand mispairings.
  Focused matching rises from `64.09%`, `327/347`, prefix `3`, and ten masked
  mismatches to `93.10%`, `349/347`, prefix `20`, and `74` clean masked
  operands. The sole remaining audited mismatch is the compiler-local jump
  table label map; nothing is unresolved.
