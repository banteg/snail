# Selected Replay Record Typing - 2026-03-26

Scope:
- determine whether `game + 0xff25d4` points at the compact on-disk record or the expanded in-memory high-score entry
- recover only the gameplay-facing slice needed by `update_subgoldy`, `initialize_subgame`, `update_subgame`, `set_subgame_features`, and `populate_runtime_track_cells_from_segments`

Outcome:
- `game + 0xff25d4` is the expanded in-memory selected replay/high-score entry, not the compact `0x88 + 5*n` on-disk record
- the compact serialize/deserialize helpers close the safe gameplay slice of that expanded entry

Safe expanded-entry slice:
- `record + 0x28`: `replay_level_index`
- `record + 0x2c`: `replay_mode_id`
- `record + 0x38`: `runtime_build_flags`
- `record + 0x48`: `replay_speed_scalar`
- `record + 0x4c`: `challenge_speed_value`
- `record + 0x50`: `challenge_difficulty_value`
- `record + 0x54`: `name[0x14]`
- `record + 0x68`: `runtime_build_seed`
- `record + 0x6c`: `replay_sample_count`
- `record + 0x70 + i*6`: `replay_samples[i].lateral_x`
- `record + 0x72 + i*6`: `replay_samples[i].secondary_lane_raw`
- `record + 0x74 + i*6`: `replay_samples[i].flags`

Evidence:
- [serialize_compact_high_score_record](/Users/banteg/dev/banteg/snail-mail/analysis/decompile/binja/functions/00440170-serialize_compact_high_score_record.c)
- [deserialize_compact_high_score_record](/Users/banteg/dev/banteg/snail-mail/analysis/decompile/ida/functions/00440020-deserialize_compact_high_score_record.c)
- [initialize_subgame](/Users/banteg/dev/banteg/snail-mail/analysis/decompile/binja/functions/004374b0-initialize_subgame.c)
- [update_subgame](/Users/banteg/dev/banteg/snail-mail/analysis/decompile/binja/functions/00438b90-update_subgame.c)
- [set_subgame_features](/Users/banteg/dev/banteg/snail-mail/analysis/decompile/binja/functions/00435df0-set_subgame_features.c)
- [populate_runtime_track_cells_from_segments](/Users/banteg/dev/banteg/snail-mail/analysis/decompile/binja/functions/00435eb0-populate_runtime_track_cells_from_segments.c)
- [update_subgoldy](/Users/banteg/dev/banteg/snail-mail/analysis/decompile/binja/functions/0043b120-update_subgoldy.c)

Notes:
- the persistent/transient bridge split stays on the separate control fields:
  - `selected_level_record_active`
  - `selected_level_record_persistent`
  - `selected_level_record_saved_return_owner`
- do not treat `selected_level_record_source` in Zig as a native synonym for the saved-return lane; it remains a port-side launch classifier
