# Selected Level Record And Nuke Follow-up

This is the incremental follow-up to bundle `14-cutscene-fall-handoff-and-subgame-state`.

Assume the recipient already has bundles `12` through `14`. This bundle is pure reverse-engineering follow-up; it does not add a new port snapshot.

This bundle only carries:
- fresh Binary Ninja and IDA exports for the death/resurrect path, selected-level-record routing, the newly mapped nuke cluster, and the gameplay row-event display controller
- fresh Binary Ninja and IDA exports for the gameplay parcel runtime cluster (`initialize_track_parcel_runtime`, `initialize_track_parcel_slots`, `allocate_track_parcel_slot`, `update_track_parcel`, and `spawn_track_parcel`)
- a fresh Binary Ninja struct/export/report pass for the player completion-handoff controller in `update_subgoldy`
- a fresh Binary Ninja and IDA cutscene/snail-skin pass for the resolved hotspot writer chain behind the old `player + 6208 / +6280` anchor question
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

- `game + 0x12727d8` is now mapped as the gameplay `row_event_display` controller.
  - `register_parcel_delivery` belongs to this controller, not to the completion screen
  - the old loose `+0x12727ec` dword is `row_event_display.state`
  - the old loose `+0x12727f0` byte is now known to live inside the same controller, though its exact meaning is still unresolved

- the gameplay parcel runtime is now typed and named cleanly.
  - the live slot array base is `game + 0x125e480`, not `+0x125e430`
  - `initialize_runtime_pools_and_path_template_bank` seeds it through `initialize_track_parcel_runtime`
  - `build_subgame_level` resets it through `initialize_track_parcel_slots`
  - `spawn_track_parcel` allocates from it through `allocate_track_parcel_slot`
  - the old `update_jetpack_visual` name at `0x4431d0` is rejected; that body is `update_track_parcel`
  - the earlier `cRParcel::AI -> 0x43f520` guess is also rejected; `0x43f520` is only a small slug-hazard helper

- the player completion-handoff block in `update_subgoldy` is now typed cleanly.
  - `player + 0x440 / +0x444 / +0x448 / +0x44e` are now:
    - `completion_handoff_active`
    - `completion_handoff_timer`
    - `completion_handoff_timer_step`
    - `completion_handoff_voice_gate`
  - that block owns the `2.0`-second one-shot voice and the `5.0`-second fade/`complete_subgame` handoff
  - `row_event_display + 0x18` is still unnamed, but its one recovered gameplay role is now narrower: it can fast-forward `completion_handoff_timer` to `5.1` when the current runtime cell carries flag `0x40`

- the `player + 6208 / +6280` anchor question is now resolved as the snail hotspot chain.
  - `build_snail_hotspots` seeds a `19`-entry local hotspot bank at `player + 0x16cc`
  - `update_snail_skin` writes the world-space hotspot bank at `player + 0x17b0`
  - `+0x1840` / `+0x1888` are `snail_hotspots_world[12]` (`CameraSkidStop`) and `snail_hotspots_world[18]` (`CameraIntroTalk`)
  - `build_snail_hotspots` also seeds hotspot `17` as `CameraSlugDeath`, but no direct runtime consumer for that slot was recovered in this pass
  - `update_cutscene` uses `CameraIntroTalk` as the repeated snapshot target and the `CameraSkidStop -> CameraIntroTalk` lerp as the state-`5` completion blend
  - the exact gameplay roles of the two source matrices, and the reason later cutscene legs keep reusing the authored `CameraIntroTalk` hotspot, are still not clean enough to freeze

- `Player.post_follow_value_b` still has only the known writes in `initialize_subgoldy_fall_state`

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
  - narrow text reports for the still-unresolved offsets, the resolved cutscene hotspot chain, the selected-level-record interpretation, and the row-event display controller mapping
  - the parcel-runtime correction report for the renamed `track_parcels` / `update_track_parcel` path
  - the player completion-handoff controller report from the refreshed `update_subgoldy` slice

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
10. `binja/RowEventDisplayController.txt`
11. `binja/00404cf0-update_row_event_display.txt`
12. `binja/00405040-register_parcel_delivery.txt`
13. `binja/00404830-flush_row_event_display.txt`
14. `binja/reports/row-event-display-controller.txt`
15. `binja/TrackParcelRuntime.txt`
16. `binja/00408860-initialize_track_parcel_runtime.txt`
17. `binja/00443160-initialize_track_parcel_slots.txt`
18. `binja/00443190-allocate_track_parcel_slot.txt`
19. `binja/004431d0-update_track_parcel.txt`
20. `binja/00443730-spawn_track_parcel.txt`
21. `binja/reports/track-parcel-runtime.txt`
22. `binja/Player.txt`
23. `binja/00445d50-build_snail_hotspots.txt`
24. `binja/00445cd0-update_snail_skin.txt`
25. `binja/004428d0-initialize_cutscene.txt`
26. `binja/004466d0-update_cutscene.txt`
27. `binja/reports/player-anchor-offsets-6208-6280.txt`
28. `binja/xrefs/build_snail_hotspots.txt`
29. `binja/xrefs/update_snail_skin.txt`
30. `binja/reports/completion-handoff-controller.txt`
31. `ida/004428d0-initialize_cutscene.c`
32. `ida/00445d50-build_snail_hotspots.c`
33. `ida/00445cd0-update_snail_skin.c`
34. `ida/004466d0-update_cutscene.c`
35. `ida/00404cf0-update_row_event_display.c`
36. `ida/00405040-register_parcel_delivery.c`
37. `ida/00404830-flush_row_event_display.c`
38. `ida/00408860-initialize_track_parcel_runtime.c`
39. `ida/00443160-initialize_track_parcel_slots.c`
40. `ida/00443190-allocate_track_parcel_slot.c`
41. `ida/004431d0-update_track_parcel.c`
42. `ida/00443730-spawn_track_parcel.c`
43. `ida/004092f0-update_galaxy.c`
44. `ida/00416370-update_challenge_setup_screen.c`
45. `ida/00435df0-set_subgame_features.c`
46. `ida/00435eb0-populate_runtime_track_cells_from_segments.c`
47. `ida/00437eb0-build_subgame_level.c`
48. `ida/00438b90-update_subgame.c`
49. `binja/xrefs/field-Player.post_follow_value_b.txt`
50. `binja/reports/post-follow-value-b.txt`
51. `binja/xrefs/play_movement_state_sound.txt`
52. `binja/reports/fall-gate-nearby-helpers.txt`
