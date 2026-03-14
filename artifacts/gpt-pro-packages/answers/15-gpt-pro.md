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

* **`Player.post_follow_value_b` still has no recovered consumer.**
  Typed BN xrefs still show only the known writes in `initialize_subgoldy_fall_state`.
  The full HLIL reexport did not add any new player-side read.

* **The player cutscene anchors at `+6208` / `+6280` are still writer-less.**
  The refreshed full HLIL export still reduces to the same `update_cutscene` reads already known from bundle 14.
  No new writer surfaced.

* **`play_movement_state_sound` did not unlock the `-6 / -7` thresholds.**
  It still has only two callsites, both in `update_subgoldy`.
  The remaining threshold question stays inside the `update_subgoldy` fall slice, not in another nearby helper.

## Net

Bundle 15 confirms three things more firmly:

1. Failure handoff still lives in the player cutscene/death selector.
2. The `0xff25d0 / 0xff25d1 / 0xff25d4` cluster is a selected-level-record override path, not tutorial-only ownership.
3. The nearby `0x4471xx` helper cluster is a collision ring effect system, not part of the fall gate.

## Remaining best targets

1. **Writers for player `+6208` / `+6280`.**
   That is still the biggest missing piece for exact intro/completion/death shot geometry.

2. **The real setter for `selected_level_record_persistent`.**
   The reads are now clear, but the upstream writer still is not.

3. **Any untyped/raw consumer of `Player.post_follow_value_b`.**
   Typed BN xrefs came back write-only.

4. **A tighter `update_subgoldy` fall slice around `0x43ce75 .. 0x43cffc`.**
   That is still the likeliest place to settle what the `-6 / -7` thresholds actually gate.
