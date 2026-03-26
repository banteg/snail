/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: sample_track_floor_height_at_position @ 0x43d4d0 */

0043d4d6        struct TrackRowCell* eax
0043d4d6        int16_t x87control
0043d4d6        eax, x87control = get_track_grid_cell_at_world_position(game, position)
0043d4db        uint8_t tile_id = eax->tile_id
0043d4f3        if (tile_id == 1 || tile_id == 0xf || tile_id == 0xe)
0043d592        return (fconvert.t(0f)).q
0043d524        if (tile_id == 2 || tile_id == 3 || tile_id == 4 || tile_id == 5 || tile_id == 6 || tile_id == 7 || tile_id == 0xb || tile_id == 0xc || tile_id == 0xd)
0043d57a        long double x87_r7_8 = float.t(__ftol(x87control, fconvert.t(position->z)))
0043d588        return ((fconvert.t(position->z) - x87_r7_8) * fconvert.t(0.400000006f)).q
0043d533        if (tile_id == 8 || tile_id == 9 || tile_id == 0xa)
0043d557        long double x87_r7_3 = float.t(__ftol(x87control, fconvert.t(position->z)))
0043d56b        return ((fconvert.t(position->z) - x87_r7_3) * fconvert.t(0.400000006f) + fconvert.t(0.5f)).q
0043d538        if (tile_id != 0x16)
0043d548        return (fconvert.t(-100f)).q
0043d53e        return (fconvert.t(eax->anchor_position.y)).q
