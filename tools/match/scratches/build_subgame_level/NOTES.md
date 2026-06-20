# `build_subgame_level` scratch notes

## Scope

This scratch reconstructs `Game::build_subgame_level(int level_index)` at
`0x437eb0` using scratch-local declarations and raw `Game` offsets. No shared
headers or unrelated scratches were changed.

The source shape was recovered from both decompile exports:

- `analysis/decompile/binja/functions/00437eb0-build_subgame_level.c`
- `analysis/decompile/ida/functions/00437eb0-build_subgame_level.c`

The Binary Ninja export was used mainly for block order. The IDA export was
used for switch cases, exact offsets, and the repeated intrusive-list insertion
shape. Exact or strong neighboring scratches supplied call-signature and
ordering anchors, especially `rebuild_track_runtime_from_segments`,
`initialize_runtime_pools_and_path_template_bank`, `update_subgame`, and
`activate_landscape_entry`.

## Recovered source shape

The accepted candidate models the complete function rather than returning
early after the easier prefix. Its major phases are:

1. Unhide the starfield and select the tutorial score-widget hide state.
2. Pick one of four music files from
   `next_math_random_value() * 0.000122070312f`.
3. Reset enemy, damage-gauge, callback, sub-lazer, salt-hazard, and voice
   systems, then load the frontend level.
4. Apply selected-record replay values or normal-mode speed and difficulty
   defaults.
5. Initialize track parcel slots, honor the score-widget hide latch, and call
   the exact `rebuild_track_runtime_from_segments(level_index)` anchor.
6. Select and activate a landscape, including the four space scripts and the
   random starfield mirror byte.
7. Insert and initialize the start/completion row controllers.
8. Reset subgame latches, release the mouse cursor, and initialize Subgoldy.
9. Insert the player-side render bodies into the active list, initialize the
   slug voice manager, attach its node, update mode-zero HUD text, reset pointer
   positions, and calculate the subgame rate.

## Source-shape decisions that improved the match

- A single `zero` local remains live from the music switch through later reset
  and list code, matching the native register lifetime better than repeated
  literal zeroes.
- The replay-selected path and normal path remain separate. The mode `0/4/7`
  speed sentinel is compared by its `-1.0f` bit pattern, while mode `1`, mode
  `2`, and mode `3` preserve their distinct conversion paths.
- The two challenge hazard scalars use separate normalized locals. Combining
  the expressions lets MSVC fold the constants to approximately `0.008f`,
  which loses the target's two-stage multiply sequence.
- `g_completion_bonus_x_source` is declared as two adjacent words so index 0
  can be consumed as an integer and index 1 as the neighboring float without a
  speculative second global.
- `rebuild_track_runtime_from_segments(level_index)` stays as a member call and
  is not reimplemented inline.
- The landscape default branch uses a local alias of the incoming level index.
  It keeps the branch semantically tied to the caller-provided index and gives
  an exact 555-instruction candidate under the fixed compiler.
- Start/completion row node pointers are scoped to their individual
  `ADDafter` operations. Shortening their lifetimes delayed the EBP save and
  substantially improved the row-controller region.
- The first row's flag commit occurs after its owner, position, and alpha
  setup. That ordering improved the measured result while remaining a natural
  initialization sequence.
- The repeated active-list operations are written as explicit intrusive-list
  insertions. Extracting them into a helper changed both code size and register
  allocation.
- The visible-body `0x80` flag update is expressed through the low byte of a
  local flag value. A direct full-word OR was cleaner but shortened the
  candidate to 552 instructions and scored lower.
- 2026-06-20 shared voice-manager header pass: the local one-method
  `VoiceManager` view was replaced with `voice_manager.h`. The focused matcher
  is unchanged at `79.82%`, `555/555`, `177/555` prefix, with the same
  `99 ok / 2 unresolved / 1` masked audit, so this is accepted as a
  call-surface consolidation rather than a source-shape win.

## Remaining differences

The exact prefix ends at target instruction 177, at the branch entering the
landscape-selection block. The first substantive code-generation difference is
inside the space-landscape switch: the target's default case reloads
`level_index` from the stack, whereas the candidate reuses EDI. This also moves
nearby labels by two bytes, so several otherwise-equivalent branch targets are
reported as changed.

The largest later mismatch is register allocation in the repeated active-list
tail. The target keeps the player object in EDI and the `0x200` membership flag
in EBP. The candidate instead keeps `0x200` in EDI for the first repeated
insertions. Attempts to force that allocation with typed overlays, earlier
player-pointer declarations, `register`, and named flag locals did not improve
code generation.

The two compiler-generated jump tables are now content-audited. The later
track dispatch table matches, while the first state dispatch table is a real
masked-operand mismatch. The two remaining unresolved operands are the
completion-bonus globals at `g_completion_bonus_x_source+0x4`.

## Rejected trials

| Trial | Measured reason for rejection |
|---|---|
| Combine the challenge scalar expressions | MSVC folded the two multiplies into one constant; prefix and relocation audit regressed. |
| Preinitialize `landscape_index` | Changed switch lowering and reduced the overall score. |
| Remove the landscape index alias | Produced 556 candidate instructions and a lower score. |
| Use a typed row-controller overlay | Shortened the exact prefix to 62 instructions and dropped the score to 58.99%. |
| Chain the row zero assignments | Changed scheduling and scored below the explicit stores. |
| Extract active-list insertion into a member or free inline helper | Produced 545 or 556 instructions and scored 61.45% or 75.79%. |
| Make `Player` inherit the list-node view, or keep a persistent typed player pointer | Did not recover the target's EDI/EBP assignment. |
| Replace the low-byte visible flag update with a direct word OR | Produced 552 instructions and a lower full-function score. |
| Reorder completion-row stores or vary alpha integer types | No improvement beyond the accepted 79.82% candidate. |
