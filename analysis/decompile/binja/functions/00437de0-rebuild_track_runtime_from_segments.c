/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: rebuild_track_runtime_from_segments @ 0x437de0 */

00437dea        runtime->level_mode_arg = level_index
00437ded        set_subgame_features(runtime)
00437df4        build_track_colours()
00437dfb        populate_runtime_track_cells_from_segments(runtime)
00437e02        place_parcels_on_track(runtime)
00437e09        select_track_tile_edge_variants(runtime)
00437e10        promote_track_tiles_to_fringe_variants(runtime)
00437e17        harmonize_center_lane_floor_slide_variants(runtime)
00437e1e        merge_track_tile_runs(runtime)
00437e25        mark_track_warning_zones(runtime)
00437e2c        build_track_fringe_objects(runtime)
00437e42        struct tColour out
00437e42        struct tColour* eax = get_track_skirt_color(&g_game_base[0x74618], &out)
00437e53        float g = eax->g
00437e5c        float b = eax->b
00437e5f        float a = eax->a
00437e65        build_track_render_caches(&runtime->__offset(0x5c).d, eax->r)
00437e6e        return 0
