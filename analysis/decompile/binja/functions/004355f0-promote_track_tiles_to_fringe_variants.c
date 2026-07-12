/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: promote_track_tiles_to_fringe_variants @ 0x4355f0 */

004355fa        int32_t i = game->runtime_row_count - 1
004355fb        int32_t i_1 = 0
00435605        if (i s> 0)
0043560f        void* __offset(Game, 0x3bfaec) esi_1 = &game->__offset(0x3bfaec).d
0043561a        int32_t j_1 = 8
004356c4        int32_t j
0043562b        (esi_1 - 0x3bfaec)->__offset(0x3bfb08).d &= 0xffffffdf
00435635        if (is_sub_loc_empty(esi_1 + 0x27c) != 0)
0043563b        int32_t eax_2 = data_4df904
00435640        int32_t k = 0
0043567e        while (k s< 0x1c0)
00435642        int32_t ecx_1 = (esi_1 - 0x3bfaec)->__offset(0x3bfaec).d
00435656        if (ecx_1 == *(k + eax_2 + 0x447b4) || ecx_1 == *(k + eax_2 + 0x44b34))
00435663        set_bod_object(esi_1 - 0x24, *(k + eax_2 + 0x44974))
0043566d        (esi_1 - 0x3bfaec)->__offset(0x3bfb08).d |= 0x20
00435670        eax_2 = data_4df904
00435675        k += 0x38
00435680        int32_t k_1 = 0
004356be        while (k_1 s< 0xe0)
00435682        int32_t ecx_4 = (esi_1 - 0x3bfaec)->__offset(0x3bfaec).d
00435696        if (ecx_4 == *(k_1 + eax_2 + 0x4423c) || ecx_4 == *(k_1 + eax_2 + 0x443fc))
004356a3        set_bod_object(esi_1 - 0x24, *(k_1 + eax_2 + 0x4431c))
004356ad        (esi_1 - 0x3bfaec)->__offset(0x3bfb08).d |= 0x20
004356b0        eax_2 = data_4df904
004356b5        k_1 += 0x38
004356c0        esi_1 += 0x54
004356c3        j = j_1
004356c3        j_1 -= 1
004356c4        do while (j != 1)
004356d2        i = i_1 + 1
004356d6        i_1 = i
004356dd        do while (i s< game->runtime_row_count - 1)
004356ea        return i
