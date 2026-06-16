# spawn_track_ring_or_special_effect @ 0x43df10

Live source map for the authored ring/special-effect spawner.

Current match:

- `36.83%`, `196/347` candidate/target instructions, with `38` masked
  operands ok.
- The scratch is evidence-first rather than close-match source. The remaining
  mismatch is dominated by switch scheduling and grouped equivalent cases, not
  by the parent-field offsets below.
- A fully duplicated switch version was rejected because MSVC failed while
  compiling the scratch. Keeping the grouped switch preserves useful struct
  evidence without adding source clutter.

Evidence:

- The ring/special-effect runtime bank is two parent slots at
  `game + 0x35b78c`, stride `0x1f8`.
- Parent list fields are the usual bod/list header lanes:
  `flags +0x04`, `next +0x08`, and `prev +0x0c`; the active-list bit is
  `0x200`.
- The spawner writes parent `owner_player +0x84`, `kind +0x88`,
  `owner_context +0x8c`, `state +0x80`, `active_phase +0x1e0`, and
  `active_phase_step +0x1e4`.
- Parent `+0x1d0` is not installed here; prior runtime notes and the
  initializer show that rate source is already present by the time child
  particles are initialized.

Type consolidation:

- `RingOrSpecialEffectParent` now carries the list header and active phase
  lanes in `tools/match/include/ring_special_effect_types.h`.
- `owner_context +0x8c` is intentionally generic: this spawner stores
  `*(player + 0x404)`, but that player-side field is not named confidently
  enough to promote here.
- 2026-06-16 correction: `+0x80` is named `state`, not `active`; the virtual
  updater uses `0` as inactive, `1` as normal orbit, and `2..5` as transition
  states.
