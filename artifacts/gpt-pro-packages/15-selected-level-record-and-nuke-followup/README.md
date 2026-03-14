# Selected Level Record And Nuke Follow-up

This is the incremental follow-up to bundle `14-cutscene-fall-handoff-and-subgame-state`.

Assume the recipient already has bundles `12` through `14`. This bundle is pure reverse-engineering follow-up; it does not add a new port snapshot.

This bundle only carries:
- fresh Binary Ninja and IDA exports for the death/resurrect path, selected-level-record routing, and the newly mapped nuke cluster
- narrow Binary Ninja xref and search reports for the still-unresolved bundle `14` offsets
- the symbol/field renames that were applied to the live Binary Ninja database and synced back into the repo maps

## What This Adds For Bundle 14's Open Questions

- `initialize_subgoldy_resurrect` now has exact field writes:
  - `+0x84 = 1`
  - `+0x80 = arg2`
  - `+0x8c = 0`
  - `+0x90 = 0x3c088889`

- `initialize_subgoldy_death` is now exported directly in both BN and IDA.
  - it only has two callers: `update_subgoldy` and `update_cutscene`
  - it chooses respawn vs final-loss strictly from `game->level_mode` and visible lives before tail-calling `initialize_subgoldy_resurrect`

- the `0x447110 / 0x4471e0 / 0x4470e0` cluster is confirmed as `cRNuke::{Init, AI, UnInit}`, not a fall or movement-sound helper

- `subgame + 0xff25d0 / +0xff25d1 / +0xff25d4` are now mapped as:
  - `selected_level_record_active`
  - `selected_level_record_persistent`
  - `selected_level_record`
  Writers come from the galaxy/challenge frontend flow; consumers come from subgame build/update logic.
  Exact-offset sweeps still do not recover a setter for `selected_level_record_persistent`.

- `Player.post_follow_value_b` still has only the known writes in `initialize_subgoldy_fall_state`

- the `player + 6208 / +6280` anchor writer is still unresolved; the full HLIL reexport still only shows `update_cutscene` reads

- the `-6 / -7` question is now narrower:
  - `play_movement_state_sound` still only has two movement-branch callsites
  - the actual `-6 / -7` thresholds in `update_subgoldy` gate one-shot attachment-exit voice/cutscene triggers, not the final respawn or game-over handoff

## Contents

- `ida/`
  - IDA pseudocode exports for the exact functions rechecked this pass
- `binja/`
  - fresh Binary Ninja decompiles for the same functions
- `binja/xrefs/`
  - direct caller/field-xref evidence for the renamed paths
- `binja/reports/`
  - narrow text reports for the still-unresolved offsets and the selected-level-record interpretation

## Suggested Reading Order

1. `binja/00446e30-initialize_subgoldy_death.txt`
2. `binja/00441fa0-initialize_subgoldy_resurrect.txt`
3. `binja/00441fd0-update_subgoldy_resurrect.txt`
4. `binja/xrefs/initialize_subgoldy_death.txt`
5. `binja/00447110-initialize_nuke.txt`
6. `binja/004471e0-update_nuke.txt`
7. `binja/004470e0-uninit_nuke.txt`
8. `binja/xrefs/initialize_nuke.txt`
9. `binja/reports/selected-level-record-flags.txt`
10. `ida/004092f0-update_galaxy.c`
11. `ida/00416370-update_challenge_setup_screen.c`
12. `ida/00435df0-set_subgame_features.c`
13. `ida/00435eb0-populate_runtime_track_cells_from_segments.c`
14. `ida/00437eb0-build_subgame_level.c`
15. `ida/00438b90-update_subgame.c`
16. `binja/reports/player-anchor-offsets-6208-6280.txt`
17. `binja/xrefs/field-Player.post_follow_value_b.txt`
18. `binja/reports/post-follow-value-b.txt`
19. `binja/xrefs/play_movement_state_sound.txt`
20. `binja/reports/fall-gate-nearby-helpers.txt`
