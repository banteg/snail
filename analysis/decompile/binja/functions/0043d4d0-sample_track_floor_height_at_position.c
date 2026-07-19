/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: sample_track_floor_height_at_position @ 0x43d4d0 */

0043d4d6        struct TrackRowCell* eax
0043d4d6        int16_t x87control
0043d4d6        eax, x87control = get_track_grid_cell_at_world_position(game, position)
0043d4db        enum SubLocTileId tile_id = eax->tile_id
0043d4f3        if (tile_id == SUBLOC_TILE_FLOOR_DOT || tile_id == SUBLOC_TILE_SLIDE_UNDERSCORE || tile_id == SUBLOC_TILE_WALL2)
0043d592        return (fconvert.t(0f)).q
0043d524        if (tile_id == SUBLOC_TILE_RAMP_LEFT_BRACE || tile_id == SUBLOC_TILE_RAMP_GREATER || tile_id == SUBLOC_TILE_RAMP_RIGHT_BRACE || tile_id == SUBLOC_TILE_RAMP_LEFT_BRACKET || tile_id == SUBLOC_TILE_RAMP_LESS || tile_id == SUBLOC_TILE_RAMP_RIGHT_BRACKET || tile_id == SUBLOC_TILE_RAMP_LEFT_BRACE_BACKPATCH || tile_id == SUBLOC_TILE_RAMP_GREATER_BACKPATCH || tile_id == SUBLOC_TILE_RAMP_RIGHT_BRACE_BACKPATCH)
0043d57a        long double x87_r7_8 = float.t(ftol(x87control, fconvert.t(position->z)))
0043d588        return ((fconvert.t(position->z) - x87_r7_8) * fconvert.t(0.400000006f)).q
0043d533        if (tile_id == SUBLOC_TILE_RAMP_LEFT_BRACE_RAISED || tile_id == SUBLOC_TILE_RAMP_GREATER_RAISED || tile_id == SUBLOC_TILE_RAMP_RIGHT_BRACE_RAISED)
0043d557        long double x87_r7_3 = float.t(ftol(x87control, fconvert.t(position->z)))
0043d56b        return ((fconvert.t(position->z) - x87_r7_3) * fconvert.t(0.400000006f) + fconvert.t(0.5f)).q
0043d538        if (tile_id != SUBLOC_TILE_TRAMPOLINE)
0043d548        return (fconvert.t(-100f)).q
0043d53e        return (fconvert.t(eax->anchor_position.y)).q
