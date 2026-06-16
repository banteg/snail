# spawn_track_ring_or_special_effect @ 0x43df10

Live source map for the authored ring/special-effect spawner.

Current match:

- `36.83%`, `196/347` candidate/target instructions, with `38` masked
  operands ok.
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
  `owner_context +0x8c`, `state +0x80`, `active_phase +0x1e0`, and
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

- `RingOrSpecialEffectParent` now inherits the shared `BodNode` prefix and
  the active/free anchor is modeled as `RingOrSpecialEffectListAnchor`
  (`BodList`) in `tools/match/include/ring_special_effect_types.h`.
- `owner_context +0x8c` is intentionally generic: this spawner stores
  `*(player + 0x404)`, but that player-side field is not named confidently
  enough to promote here.
- 2026-06-16 correction: `+0x80` is named `state`, not `active`; the virtual
  updater uses `0` as inactive, `1` as normal orbit, and `2..5` as transition
  states.
