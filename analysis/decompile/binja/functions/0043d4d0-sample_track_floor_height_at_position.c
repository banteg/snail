/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: sample_track_floor_height_at_position @ 0x43d4d0 */

0043d4d6        struct TrackRowCell* eax
0043d4d6        int16_t x87control
0043d4d6        eax, x87control = get_track_grid_cell_at_world_position(game, position)
0043d4db        char ecx = eax->__offset(0x3c).b
0043d4f3        if (ecx == 1 || ecx == 0xf || ecx == 0xe)
0043d592        return (fconvert.t(0f)).q
0043d524        if (ecx == 2 || ecx == 3 || ecx == 4 || ecx == 5 || ecx == 6 || ecx == 7 || ecx == 0xb || ecx == 0xc || ecx == 0xd)
0043d57a        long double x87_r7_8 = float.t(__ftol(x87control, fconvert.t(position->z)))
0043d588        return ((fconvert.t(position->z) - x87_r7_8) * fconvert.t(0.400000006f)).q
0043d533        if (ecx == 8 || ecx == 9 || ecx == 0xa)
0043d557        long double x87_r7_3 = float.t(__ftol(x87control, fconvert.t(position->z)))
0043d56b        return ((fconvert.t(position->z) - x87_r7_3) * fconvert.t(0.400000006f) + fconvert.t(0.5f)).q
0043d538        if (ecx != 0x16)
0043d548        return (fconvert.t(-100f)).q
0043d53e        return (fconvert.t(eax->__offset(0x14).d)).q
