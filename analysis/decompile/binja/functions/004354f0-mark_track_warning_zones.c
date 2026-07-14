/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: mark_track_warning_zones @ 0x4354f0 */

004354f7        int32_t i = 0
004354fc        int32_t i_1 = 0
00435500        if (game->runtime_row_count - 1 s<= 0)
00435500        return
00435509        uint8_t* eax_2 = &game->runtime_cells[0][0].tile_id
0043550f        uint8_t* edx_1 = eax_2
00435511        int32_t j = 0
00435513        uint8_t* var_8_1 = edx_1
00435517        uint8_t eax_3 = (edx_1 - 0x3bfb04)->:0x3bfb04.b
00435557        if (eax_3 == 2 || eax_3 == 3 || eax_3 == 4 || eax_3 == 5 || eax_3 == 6 || eax_3 == 7 || eax_3 == 8 || eax_3 == 9 || eax_3 == 0xa || eax_3 == 0xb || eax_3 == 0xc || eax_3 == 0xd || eax_3 == 0xe || eax_3 == 0x17 || eax_3 == 0x19 || eax_3 == 0x21)
00435559        int32_t edi_1 = j + (i << 3)
0043555d        int32_t var_c_1 = 6
004355b5        bool cond:1_1
00435565        int32_t k = 0xffffffff
004355a6        while (k s< 1)
00435572        if (i s>= 0 && i s< game->runtime_row_count - 1)
00435574        int32_t eax_4 = k + j
0043557e        if (eax_4 s>= 0 && eax_4 s< 8)
0043558c        int32_t eax_7 = (edi_1 + k) * 0x15
004355a0        (&game->runtime_cells[0][0].lane_and_flags)[eax_7] |= 0x18
004355a2        k += 1
004355ac        i -= 1
004355ad        edi_1 -= 8
004355b0        cond:1_1 = var_c_1 != 1
004355b1        var_c_1 -= 1
004355b5        do while (cond:1_1)
004355b7        edx_1 = var_8_1
004355bb        i = i_1
004355bf        j += 1
004355c0        edx_1 = &edx_1[0x54]
004355c6        var_8_1 = edx_1
004355ca        do while (j s< 8)
004355d0        eax_2 = edx_1
004355d5        i += 1
004355d9        i_1 = i
004355dd        do while (i s< game->runtime_row_count - 1)
004355ea        return
