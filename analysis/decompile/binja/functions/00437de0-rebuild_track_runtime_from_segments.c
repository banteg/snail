/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: rebuild_track_runtime_from_segments @ 0x437de0 */

00437de7        int32_t esi
00437de7        int32_t var_14 = esi
00437dea        game->level_mode_arg = level_index
00437ded        set_subgame_features(game)
00437df4        build_track_colours()
00437dfb        populate_runtime_track_cells_from_segments(game)
00437e02        place_parcels_on_track(game)
00437e09        select_track_tile_edge_variants(game)
00437e10        promote_track_tiles_to_fringe_variants(game)
00437e17        harmonize_center_lane_floor_slide_variants(game)
00437e1e        merge_track_tile_runs(game)
00437e25        mark_track_warning_zones(game)
00437e2c        build_track_fringe_objects(game)
00437e42        float var_10
00437e42        float* eax = get_track_skirt_color(data_4df904 + 0x74618, &var_10)
00437e4e        float var_24 = *eax
00437e53        int32_t var_20 = eax[1]
00437e5c        int32_t var_1c = eax[2]
00437e5f        int32_t var_18_1 = eax[3]
00437e65        build_track_render_caches(&game->__offset(0x5c).d)
00437e6e        return 0
