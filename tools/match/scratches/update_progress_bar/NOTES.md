# update_progress_bar

`update_progress_bar` queues the three direct-HUD quads for the left-column
track progress indicator:

- `0x9d` cursor at x=12, y=`remaining_height + 111`
- `0x9b` empty/top bar at x=13, y=150, height=`remaining_height`
- `0x9c` lit/bottom bar at x=13, y=`150 + remaining_height`,
  height=`256 - remaining_height`

The progress input is
`(Player::position.z - SubgameRuntime::first_block_row_count) /
(SubgameRuntime::completion_row_start - first_block_row_count)`. The former raw
root offsets are therefore the embedded player's live z and the authored
first/completion block boundaries, not a separate active-row window. The
remaining height curve is `(1 - clamp(progress, 0, 1)) * 232 + 12`.

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
- The initial scratch used a small root-offset window because VC6 rejected the
  large padding array needed to span the player and subgame fields. The shared
  owners now express the same offsets without that synthetic view.

2026-06-20 type consolidation: `ProgressBar` now lives in
`include/progress_bar.h` as the one-word player subobject used at
`Player +0x3f0`. Focused rerun remains exact at 100.00%, 110/110
instructions, with 19 masked operands OK. The `update_subgoldy` callsite uses
the shared header and keeps its existing 72.51% residual profile.

2026-06-21 root-view naming cleanup: the root-level progress source is now a
`ProgressBarGameView` instead of another local `Game` shell. Focused Wibo
remains exact at `100.00%`, `110/110` instructions, with `19` clean masked
operands.

2026-07-11 ownership closure: `Player` now owns the one-word `ProgressBar` at
`+0x3f0`, while this updater reads `Player::position.z` and the enclosing
`SubgameRuntime::first_block_row_count/completion_row_start` directly through
`GameRoot`. The synthetic root view and active-row window are removed. Focused
Wibo remains exact at 110/110 instructions with 19 clean masked operands.
