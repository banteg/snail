/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: get_track_grid_cell_at_world_position @ 0x43d410 */

0043d421        int32_t eax
0043d421        int16_t x87control
0043d421        int16_t x87control_1
0043d421        eax, x87control_1 = ftol(x87control, fconvert.t(position->x) + fconvert.t(4f))
0043d429        int32_t esi = eax
0043d42b        int32_t eax_1 = ftol(x87control_1, fconvert.t(position->z))
0043d432        if (esi s< 0)
0043d434        esi = 0
0043d43b        if (esi s> 7)
0043d43d        esi = 7
0043d444        if (eax_1 s< 0)
0043d446        eax_1 = 0
0043d44f        if (eax_1 s> 0xc7f)
0043d451        eax_1 = 0xc7f
0043d46f        return &game->runtime_cells[0][esi + (eax_1 << 3)]
