# update_track_render_cache_rows @ 0x433b30

Initial relationship-first scratch for the track-render-cache row activator called
only by `update_subgame` after the forward runtime-row scan.

Evidence:

- Native `update_subgame` calls this helper with `game + 0x5c`, the same
  `SegmentCache` base used by `rebuild_track_runtime_from_segments`
  and `remove_track_render_cache_bods`.
- The function compares `g_game_base + 0x42fdec + 46.0f` against manager
  `+0xa7f0`, then advances `+0xa7f0` by `24.0f` and increments `+0xa7f4`.
  The old BN-only names `scratch_max_vertices` / `scratch_max_indices` were
  therefore wrong; these are now `next_cache_row_z` and
  `next_cache_row_index`.
- The repeated slot blocks link `BodBase` nodes into sentinel-style active
  lists at `g_game_base + 0x3ca1b4` for Floor/Slide/Warn/Ramp and
  `g_game_base + 0x3ca17c` for Fringe, reporting `"List ADDafter"` if the
  slot is already live.
- The exact source shape reloads the main active list for each slot block and
  uses short-lived `TrackRenderCacheSlot*` / `Vector3*` views. Keeping the main
  active list across the four non-fringe slots pushed the live mask into `ebp`;
  reloading it per block keeps native `ebx = 0x200` and `edi = 0`.

Match status:

- 2026-06-18: 100.00%, 227/227 instructions, 27 masked operands all resolved.
- 2026-07-11: promoted the exact 0xa7f8-byte receiver to the authored
  `SegmentCache` / cRSegmentCache owner. The method remains exact at 227/227
  with all 27 operands clean.
