/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: get_track_runtime_cell_at_world_z @ 0x43d480 */

0043d48a        int16_t x87control
0043d48a        int32_t eax = __ftol(x87control, fconvert.t(position->z))
0043d491        if (eax s< 0)
0043d4a6        return &game->__offset(0x5ccac8).d
0043d4ae        if (eax s> 0xc7f)
0043d4b0        eax = 0xc7f
0043d4c6        return &game->_pad_00[eax * 0xf4 + 0x5ccac8]
