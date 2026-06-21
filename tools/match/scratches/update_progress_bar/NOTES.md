# update_progress_bar

`update_progress_bar` queues the three direct-HUD quads for the left-column
track progress indicator:

- `0x9d` cursor at x=12, y=`remaining_height + 111`
- `0x9b` empty/top bar at x=13, y=150, height=`remaining_height`
- `0x9c` lit/bottom bar at x=13, y=`150 + remaining_height`,
  height=`256 - remaining_height`

The progress input is `(Game+0x42fdec - Game+0x74668) /
(Game+0x74670 - Game+0x74668)`: the current row lane is a float, while the
active row window start/end are integers. The remaining height curve is
`(1 - clamp(progress, 0, 1)) * 232 + 12`.

## Scratch status

Added on 2026-06-18. Focused Wibo verifies a clean 100% match: 110/110
instructions, prefix 110/110, 19 masked operands OK, no unresolved or
mismatched operands.

Source-shape notes:

- `update_progress_bar` is kept as a `ProgressBar` member, matching the
  callsite shape from `update_subgoldy`; the callee does not read `this`.
- `g_game` must be declared non-volatile here. The volatile declaration was
  otherwise semantic-equivalent but caused VC6 to reserve stack locals before
  loading `g_game`; native loads `g_game` first, then subtracts `esp`.
- The active row window is modeled as a small typed view at `game + 0x74668`
  instead of one huge sparse `Game` struct, because VC6 rejects the large
  padding array needed to span from `+0x42fdec` to `+0x74668`.

2026-06-20 type consolidation: `ProgressBar` now lives in
`include/progress_bar.h` as the one-word player subobject used at
`Player +0x3f0`. Focused rerun remains exact at 100.00%, 110/110
instructions, with 19 masked operands OK. The `update_subgoldy` callsite uses
the shared header and keeps its existing 72.51% residual profile.

2026-06-21 root-view naming cleanup: the root-level progress source is now a
`ProgressBarGameView` instead of another local `Game` shell. Focused Wibo
remains exact at `100.00%`, `110/110` instructions, with `19` clean masked
operands.
