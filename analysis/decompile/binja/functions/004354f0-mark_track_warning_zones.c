/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: mark_track_warning_zones @ 0x4354f0 */

004354f7        int32_t i = 0
004354fc        int32_t i_1 = 0
00435500        if (game->runtime_row_count - 1 s<= 0)
00435500        return
00435509        struct TrackRowCellTileByteView* row_tile_cursor = &game->runtime_cells[0][0].tile_id
0043550f        struct TrackRowCellTileByteView* cell_tile_cursor = row_tile_cursor
00435511        int32_t j = 0
00435513        struct TrackRowCellTileByteView* saved_cell_tile_cursor = cell_tile_cursor
00435517        enum SubLocTileId tile_id = cell_tile_cursor->tile_id
00435557        if (tile_id == SUBLOC_TILE_RAMP_LEFT_BRACE || tile_id == SUBLOC_TILE_RAMP_GREATER || tile_id == SUBLOC_TILE_RAMP_RIGHT_BRACE || tile_id == SUBLOC_TILE_RAMP_LEFT_BRACKET || tile_id == SUBLOC_TILE_RAMP_LESS || tile_id == SUBLOC_TILE_RAMP_RIGHT_BRACKET || tile_id == SUBLOC_TILE_RAMP_LEFT_BRACE_RAISED || tile_id == SUBLOC_TILE_RAMP_GREATER_RAISED || tile_id == SUBLOC_TILE_RAMP_RIGHT_BRACE_RAISED || tile_id == SUBLOC_TILE_RAMP_LEFT_BRACE_BACKPATCH || tile_id == SUBLOC_TILE_RAMP_GREATER_BACKPATCH || tile_id == SUBLOC_TILE_RAMP_RIGHT_BRACE_BACKPATCH || tile_id == SUBLOC_TILE_WALL2 || tile_id == SUBLOC_TILE_HEALTH_PICKUP || tile_id == SUBLOC_TILE_JETPACK_PICKUP || tile_id == SUBLOC_TILE_GARBAGE_HAZARD)
00435559        int32_t edi_1 = j + (i << 3)
0043555d        int32_t var_c_1 = 6
004355b5        bool cond:1_1
00435565        int32_t k = 0xffffffff
004355a6        while (k s< 1)
00435572        if (i s>= 0 && i s< game->runtime_row_count - 1)
00435574        int32_t eax_2 = k + j
0043557e        if (eax_2 s>= 0 && eax_2 s< 8)
0043558c        int32_t eax_5 = (edi_1 + k) * 0x15
004355a0        (&game->runtime_cells[0][0].lane_and_flags)[eax_5] |= 0x18
004355a2        k += 1
004355ac        i -= 1
004355ad        edi_1 -= 8
004355b0        cond:1_1 = var_c_1 != 1
004355b1        var_c_1 -= 1
004355b5        do while (cond:1_1)
004355b7        cell_tile_cursor = saved_cell_tile_cursor
004355bb        i = i_1
004355bf        j += 1
004355c0        cell_tile_cursor = &cell_tile_cursor[1]
004355c6        saved_cell_tile_cursor = cell_tile_cursor
004355ca        do while (j s< 8)
004355d0        row_tile_cursor = cell_tile_cursor
004355d5        i += 1
004355d9        i_1 = i
004355dd        do while (i s< game->runtime_row_count - 1)
004355ea        return
