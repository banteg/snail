Bundle 15 now closes the cutscene-anchor writer question too and narrows the remaining unresolved offsets further.

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

* **The gameplay parcel runtime is now typed cleanly, and the old `+0x125e430` placement is rejected.**
  The live slot array is `game + 0x125e480`, not `+0x125e430`.
  `initialize_runtime_pools_and_path_template_bank` seeds it with `initialize_track_parcel_runtime`, `build_subgame_level` clears it through `initialize_track_parcel_slots`, `spawn_track_parcel` allocates from it through `allocate_track_parcel_slot`, and the old `update_jetpack_visual` body at `0x4431d0` is now correctly `update_track_parcel`.
  That also settles one earlier split: these embedded slots are the actual Windows runtime behind `cRSubGame::AddParcel`, not a separate parcel-manager family.

* **The earlier `cRParcel::AI -> 0x43f520` guess is wrong.**
  `0x43f520` is only a tiny phase helper called from `update_slug_hazard_ai`.
  The real Windows parcel AI is `update_track_parcel` at `0x4431d0`, which runs the bobbing pickup, mailbox homing, and final delivery arc before calling `register_parcel_delivery(&parcel->game->row_event_display)`.

* **The player-side completion handoff is now typed, not just inferred from offsets.**
  `player + 0x440 / +0x444 / +0x448 / +0x44e` are now:
  - `completion_handoff_active`
  - `completion_handoff_timer`
  - `completion_handoff_timer_step`
  - `completion_handoff_voice_gate`
  `update_subgoldy` arms that block when the player reaches the course-end threshold, uses it to clamp the fixed completion lane, fires the one-shot voice at `2.0` seconds, and routes into fade plus `complete_subgame` after `5.0` seconds.

* **The old `game + 0x12727f0` byte is now narrowed to one unresolved controller gate.**
  It lives inside `row_event_display + 0x18`, not beside it as a separate ownership flag.
  `update_subgoldy` still consumes it with current-cell flag `0x40`, and `update_row_event_display` clears it during the `state == 3` leg, but the exact gameplay name is still not clean enough to freeze.
  The new narrow read is: it can fast-forward `completion_handoff_timer` to `5.1`, which is enough to skip the normal handoff delay and fall straight into the completion fade path.

* **`Player.post_follow_value_b` still has no recovered consumer.**
  Typed BN xrefs still show only the known writes in `initialize_subgoldy_fall_state`.
  The full HLIL reexport did not add any new player-side read.

* **The player cutscene anchors at `+6208` / `+6280` are no longer writer-less.**
  `build_snail_hotspots` seeds a `19`-entry local hotspot bank at `player + 0x16cc`, and `update_snail_skin` writes the world-space bank at `player + 0x17b0`.
  That makes `+0x1840` / `+0x1888` `snail_hotspots_world[12]` (`CameraSkidStop`) and `snail_hotspots_world[18]` (`CameraIntroTalk`), with hotspot `17` (`CameraSlugDeath`) also present in the authored table but still without a recovered runtime read.
  `update_cutscene` uses `CameraIntroTalk` as the repeated snapshot target and the `CameraSkidStop -> CameraIntroTalk` lerp as the state-`5` completion blend.
  The exact gameplay roles of the two source matrices, and the reason later cutscene legs keep reusing the authored `CameraIntroTalk` hotspot, are still not clean enough to freeze.

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
4. `game + 0x125e480` is the real gameplay parcel-slot array, and `0x443160 / 0x443190 / 0x4431d0` are the slot reset, allocator, and parcel-AI path behind `cRSubGame::AddParcel`.
5. `player + 0x440 / +0x444 / +0x448 / +0x44e` is the completion-handoff controller that owns the `2s` voice and `5s` fade/`complete_subgame` transition.
6. The old `player + 6208 / +6280` mystery is the live transformed snail-hotspot bank, not a pair of isolated cutscene-only fields.
7. The nearby `0x4471xx` helper cluster is a collision ring effect system, not part of the fall gate.
8. The `-6 / -7` thresholds are in-fall attachment-exit gates, not death-resolution timing.

## Remaining best targets

1. **The real setter for `selected_level_record_persistent`.**
   The reads are now clear, but the upstream writer still is not.

2. **The exact meaning of `row_event_display + 0x18`.**
   It is no longer a floating `Game` flag, and it now narrows to a completion-handoff fast-forward gate, but its real gameplay name is still unresolved.

3. **Any untyped/raw consumer of `Player.post_follow_value_b`.**
   Typed BN xrefs came back write-only.

4. **A tighter `update_subgoldy` fall slice around `0x43cf25 .. 0x43cfe2`.**
   The broad threshold meaning is now clear, but the remaining question is how those gates interact with the later `progress_timer` branch and the `player + 0x2d8` flag.

5. **The exact gameplay roles of the two cutscene-hotspot matrices, and why later cutscene legs keep reusing the authored `CameraIntroTalk` hotspot.**
   The writer path and the hotspot names are now clear, but the higher-level camera semantics are still not clean enough to freeze.
