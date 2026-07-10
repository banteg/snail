# spawn_track_ring_or_special_effect @ 0x43df10

Live source map for the authored ring/special-effect spawner.

Current match:

- `53.45%`, `218/347` candidate/target instructions, prefix `28/347`, with
  `34` masked operands ok, `9` known switch-grouping/table mismatches, and no
  unresolved operands.
- The scratch is evidence-first rather than close-match source. The remaining
  mismatch is dominated by switch scheduling and grouped equivalent cases, not
  by the parent-field offsets below.
- A fully duplicated switch version was rejected because MSVC failed before
  emitting `scratch.obj`. Even splitting only kind `1` into its native
  `RR2`/`RR3` path hit the same no-object failure, so the source keeps grouped
  cases for compilability.

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
- The current grouped source intentionally uses only representative tags
  (`RR`/`RR1`, `RR4`/`RR5`, `RR10`) so it can compile; the masked operand audit
  mismatches around `RR2`/`RR3` are this known source grouping, not field-layout
  evidence.

Type consolidation:

- `RingOrSpecialEffectParent` now inherits shared `RenderableBod`, including
  the `BodNode` active/free-list prefix. The active/free anchor is modeled as
  `RingOrSpecialEffectListAnchor` (`BodList`) in
  `tools/match/include/ring_special_effect_types.h`.
- 2026-06-17 renderable inheritance correction: the spawner initializes the
  inherited transform at `slot +0x38`, and the particle/updater/collision
  consumers read the parent center as `transform.position` at `+0x68`. The
  scratch keeps its native-shaped raw `slot_base +0x35b7f4` position view to
  avoid the known register-ownership regression.
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
- 2026-06-16 active-list branch-order pass: the shared `g_game_base + 0x5a8`
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
- Retesting a separate authored kind-1 `RR2`/`RR3` arm still makes VC6 exit
  without producing `scratch.obj`. The grouped switch remains an honest
  partial; no duplicate arm or fake relocation was kept.
