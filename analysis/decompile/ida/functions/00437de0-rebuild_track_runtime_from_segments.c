/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: rebuild_track_runtime_from_segments @ 0x437de0 */
/* selector: rebuild_track_runtime_from_segments */

// Normalizes the generated runtime grid, copies authored metadata into runtime cells, and runs the post-build render passes.
int32_t __thiscall rebuild_track_runtime_from_segments(Game *game, int32_t level_index)
{
  int v4[4]; // [esp+4h] [ebp-10h] BYREF

  game->level_mode_arg = level_index;
  set_subgame_features((int)game);
  build_track_colours();
  populate_runtime_track_cells_from_segments(game);
  place_parcels_on_track(game);
  select_track_tile_edge_variants(game);
  promote_track_tiles_to_fringe_variants(game);
  harmonize_center_lane_floor_slide_variants(game);
  merge_track_tile_runs(game);
  mark_track_warning_zones(game);
  build_track_fringe_objects(game);
  get_track_skirt_color((int *)MEMORY[0x4DF904] + 119174, v4);
  return build_track_render_caches((TrackRenderCacheManager *)game->_pad_5c);
}

