# Path System Overview

This section captures the current static understanding of the `SEGMENTS` path system and the segment-to-track runtime pipeline inside the gameplay executable. The preferred analysis target is [`SnailMail_unwrapped.exe`](../../artifacts/bin/SnailMail_unwrapped.exe); the original shipped equivalent is [`SnailMail.RWG`](../../artifacts/bin/SnailMail.RWG).

Primary sources used for these notes:

- the Binary Ninja database in [`SnailMail_unwrapped.exe.bndb`](../../artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb)
- the tracked symbol manifest in `analysis/symbols/gameplay-functions.json`
- the historical rename source in [`SnailMail.RWG.bndb`](../../artifacts/binary_ninja/SnailMail.RWG.bndb)
- the exported HLIL snapshot in [`SnailMail.RWG.bndb_hlil.txt`](../../artifacts/binary_ninja/SnailMail.RWG.bndb_hlil.txt)
- the IDA decompile dump in [`SnailMail.RWG.c`](../../artifacts/ida/SnailMail.RWG.c)
- Ghidra as a second-opinion decompiler for ambiguous functions

## Current Function Map

High-confidence renamed functions in the tracked manifest and the current Binary Ninja database:

- `find_segment_path_index_by_name` at `0x429ae0`
- `initialize_garbage_hazard` at `0x408550`
- `initialize_path_template_record_pair` at `0x4085c0`
- `mirror_path_template_pair_x` at `0x421dc0`
- `load_segment_definitions` at `0x448160`
- `load_level_definitions` at `0x448900`
- `load_level_definition_file` at `0x447480`
- `copy_segment_definition_to_level_slot` at `0x447300`
- `begin_track_attachment_follow_state` at `0x420c40`
- `update_track_attachment_follow_state` at `0x420cb0`
- `try_enter_track_attachment_from_swept_motion` at `0x42c770`
- `is_point_inside_track_attachment` at `0x42ca90`
- `build_track_fringe_objects` at `0x434be0`
- `build_track_render_caches` at `0x433220`
- `normalize_segment_glyph_for_track_flags` at `0x437270`
- `rebuild_track_runtime_from_segments` at `0x437de0`
- `build_subgame_level` at `0x437eb0`
- `complete_subgame` at `0x438700`
- `add_subgoldy_score` at `0x4402c0`
- `select_level_track_texture_set` at `0x410730`
- `update_subgame` at `0x438b90`
- `initialize_jetpack_gauge` at `0x43a930`
- `update_jetpack_gauge` at `0x43a390`
- `advance_timer_counters` at `0x441b90`
- `update_damage_gauge` at `0x440fd0`
- `apply_damage_gauge_delta` at `0x4413f0`
- `set_backdrop_progress_fraction` at `0x410c30`
- `set_matrix_identity` at `0x44d250`
- `initialize_subgoldy` at `0x43a9c0`
- `show_subgoldy_lives` at `0x43af10`
- `destroy_garbage_hazard` at `0x43f130`
- `update_garbage_hazard` at `0x43f200`
- `spawn_track_garbage_hazard` at `0x43da80`
- `update_subgoldy` at `0x43b120`
- `initialize_subgoldy_fall_state` at `0x43af60`
- `update_subgoldy_resurrect` at `0x441fd0`
- `initialize_subgoldy_death` at `0x446e30`
- `place_parcels_on_track` at `0x4438e0`
- `place_challenge_parcels_on_track` at `0x444240`
- `project_position_onto_track_attachment` at `0x4444b0`
- `handle_subgoldy_collisions` at `0x444cf0`
- `get_track_grid_cell_at_world_position` at `0x43d410`
- `get_track_cell_row_index` at `0x447040`
- `sample_track_floor_height_at_position` at `0x43d4d0`

## Split Pages

The old path-system page has been broken into focused notes:

- [Path templates](path-templates.md): hardcoded `Path=` names, slot layout, and constructor families
- [Track runtime](track-runtime.md): segment metadata layout, normalized runtime flags, glyph dispatch, ring handling, and render passes
- [Attachment follow state](attachment-follow.md): how `P/p` rows install attachment corridors and how the player enters the follow state

## Current Practical Read

The current high-confidence model is:

- `Path=<name>` resolves through a hardcoded name table in the executable
- `P/p` rows consume those indices and install hardcoded sampled path-template objects onto runtime cells
- the generated runtime track is not the raw text grid; it is a normalized structure with additional gameplay and render passes
- `populate_runtime_track_cells_from_segments` also seeds Goldy's visible life stock to `3` at `subgame + 0x3bfaa4` before `initialize_subgoldy` runs
- the placed parcel manager at `game + 0x125e430` is separate from the live garbage-object family rooted at `game + 0x359144`
- the player update can transition from ordinary floor-following into a dedicated attachment-follow state backed by those path-template objects
- contact damage and jetpack countdown are separate controllers in Windows: the live collision deltas feed `apply_damage_gauge_delta` and `update_damage_gauge` at player `+0x3c4`, while `initialize_jetpack_gauge` and `update_jetpack_gauge` own the independent jetpack warning or auto-shutoff logic at player `+0x2750`

The remaining unknowns are mostly about exact constructor semantics, special cases like `WARP`, and the last details of attachment entry or exit behavior.

## March 8 Runtime Capture

The latest Windows Frida capture is now local at [`artifacts/frida/snailmail-trace-20260308-160644-15084.ndjson`](../../artifacts/frida/snailmail-trace-20260308-160644-15084.ndjson), with the corresponding rollup at [`artifacts/frida/snailmail-trace-20260308-160644-15084.summary.json`](../../artifacts/frida/snailmail-trace-20260308-160644-15084.summary.json).

This run covered:

- five postal-mode levels
- replay playback after those runs
- one challenge-mode level

High-confidence dynamic facts from that capture:

- `attachment_probe` hit runtime tile types `29` and `30`
- `attachment_begin` only fired on runtime tile type `30`
- slug spawns remained pinned to runtime tile type `18`
- garbage spawns were dominated by runtime tile types `1` and `33`, with one observed `21`
- one replay-time `level_start` finally exposed a live active-level pointer and `selected_track_id = 4`

Current best Windows mode mapping, combining that capture with `load_frontend_level_by_mode_and_index` and the `initialize_subgame` front-end switch:

- `0` is the arcade or postal family
- `1` is challenge
- `4` is the time-trial family
- `7` is tutorial
- replay is not its own `level_mode`; it rides the separate `replay_active` or `replay_track` path

That leaves `2` and `3` unresolved as front-end or replay-adjacent helper modes, but it is enough to reject the earlier `4 == replay` read.
