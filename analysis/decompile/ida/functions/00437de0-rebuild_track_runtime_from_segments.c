/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: rebuild_track_runtime_from_segments @ 0x437de0 */
/* selector: rebuild_track_runtime_from_segments */

// Exact authored void `cRSubGame::GenerateLevel(int)`: stores the level argument, applies mode features and colours, calls `BuildLevel()` to populate runtime rows, then places parcels and runs the normalization, warning, fringe, and render-cache passes. Windows and Android `StartLevel(int)` discard its incidental final callee result.
void __thiscall rebuild_track_runtime_from_segments(SubgameRuntime *game, int32_t level_index)
{
  tColour out; // [esp+4h] [ebp-10h] BYREF
  tColour v4; // 0:^0.16

  game->level_mode_arg = level_index;
  set_subgame_features(game);
  build_track_colours(game);
  populate_runtime_track_cells_from_segments(game);
  place_parcels_on_track(game);
  select_track_tile_edge_variants(game);
  promote_track_tiles_to_fringe_variants(game);
  harmonize_center_lane_floor_slide_variants(game);
  merge_track_tile_runs(game);
  mark_track_warning_zones(game);
  build_track_fringe_objects(game);
  v4 = *get_track_skirt_color(&g_game_base->subgame, &out);
  build_track_render_caches(&game->segment_cache, v4);
}
