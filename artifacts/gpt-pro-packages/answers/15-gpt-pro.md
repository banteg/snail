Bundle 15 closes two of bundle 14's highest-value targets outright and narrows the remaining three.

## Findings

* **`initialize_subgoldy_resurrect` is no longer inferred.**
  The direct BN/IDA export shows exact writes:
  `+0x84 = 1`, `+0x80 = arg2`, `+0x8c = 0`, `+0x90 = 0x3c088889`.
  That removes the last ambiguity around the death/resurrect local timer seed.

* **`initialize_subgoldy_death` still is the real failure handoff selector.**
  It has only two callers, `update_subgoldy` and `update_cutscene`, and it chooses respawn vs final-loss strictly from `game->level_mode` and visible lives before tail-calling `initialize_subgoldy_resurrect`.
  So the final failure path is still cutscene-controlled, not a simple `world_y <= -7` gameplay cutoff.

* **The nearby `0x447110 / 0x4471e0 / 0x4470e0` cluster is `cRNuke`, not a fall helper.**
  The bodies match the Android nuke ring exactly:
  25 sprites, `owner_y - 5`, phase step `2 * dt`, radius `7.0`, collision-only caller, kill-all uninit.
  That removes one of the main “maybe this nearby helper is part of the fall gate” candidates.

* **`subgame + 16721360 / +16721361 / +16721364` can now be named more cleanly.**
  The best read is:
  - `selected_level_record_active`
  - `selected_level_record_persistent`
  - `selected_level_record`
  `update_galaxy` and `update_challenge_setup_screen` seed the active bit and record pointer, then `set_subgame_features`, `populate_runtime_track_cells_from_segments`, `build_subgame_level`, and `update_subgame` consume them to override course metadata and rebuild routing.
  Exact-offset HLIL and raw-disassembly sweeps still do not recover any `selected_level_record_persistent = 1` writer.

* **`game + 0x12727d8` is not another loose subgame flag block.**
  It is the gameplay `row_event_display` controller.
  The old `+0x12727ec` dword is `row_event_display.state`, and `flush_row_event_display`, `update_row_event_display`, and `register_parcel_delivery` all line up cleanly once the controller is typed.
  That also corrects one earlier mismatch: `register_parcel_delivery` updates the row-event display controller, not the completion screen.

* **The old `game + 0x12727f0` byte is now narrowed to one unresolved controller gate.**
  It lives inside `row_event_display + 0x18`, not beside it as a separate ownership flag.
  `update_subgoldy` still consumes it with current-cell flag `0x40`, and `update_row_event_display` clears it during the `state == 3` leg, but the exact gameplay name is still not clean enough to freeze.

* **`Player.post_follow_value_b` still has no recovered consumer.**
  Typed BN xrefs still show only the known writes in `initialize_subgoldy_fall_state`.
  The full HLIL reexport did not add any new player-side read.

* **The player cutscene anchors at `+6208` / `+6280` are still writer-less.**
  The refreshed full HLIL export still reduces to the same `update_cutscene` reads already known from bundle 14.
  Exact-offset raw disassembly search still does not surface a writer.

* **`play_movement_state_sound` did not unlock the `-6 / -7` thresholds.**
  It still has only two callsites, both in `update_subgoldy`.
  The thresholds themselves are now better pinned down from that fall slice:
  `attachment_exit_progress > 0.7` arms the first one-shot gate, `world_y < -6` can dispatch cutscene animation `5` on that branch, and `world_y < -7` arms the second one-shot gate.
  So those thresholds are attachment-exit voice/cutscene gates, not the final respawn or game-over selector.

## Net

Bundle 15 confirms three things more firmly:

1. Failure handoff still lives in the player cutscene/death selector.
2. The `0xff25d0 / 0xff25d1 / 0xff25d4` cluster is a selected-level-record override path, not tutorial-only ownership.
3. `game + 0x12727d8` is a gameplay row-event display controller, and the old `+0x12727ec/+0x12727f0` pair belongs to that controller rather than standing alone as subgame flags.
4. The nearby `0x4471xx` helper cluster is a collision ring effect system, not part of the fall gate.
5. The `-6 / -7` thresholds are in-fall attachment-exit gates, not death-resolution timing.

## Remaining best targets

1. **Writers for player `+6208` / `+6280`.**
   That is still the biggest missing piece for exact intro/completion/death shot geometry.

2. **The real setter for `selected_level_record_persistent`.**
   The reads are now clear, but the upstream writer still is not.

3. **The exact meaning of `row_event_display + 0x18`.**
   It is no longer a floating `Game` flag, but its real gameplay meaning is still unresolved.

4. **Any untyped/raw consumer of `Player.post_follow_value_b`.**
   Typed BN xrefs came back write-only.

5. **A tighter `update_subgoldy` fall slice around `0x43cf25 .. 0x43cfe2`.**
   The broad threshold meaning is now clear, but the remaining question is how those gates interact with the later `progress_timer` branch and the `player + 0x2d8` flag.
