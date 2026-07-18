/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: normalize_segment_glyph_for_track_flags @ 0x437270 */

0043728d        if (row s<= runtime->completion_row_start && sx.d(glyph) - 0x20 u<= 0x5d)
00437293        int32_t ebx_1 = 0
00437295        ebx_1.b = *(sx.d(glyph) + &normalize_segment_glyph_for_track_flags_jump_table[5])
0043729b        uint16_t runtime_flags_5
0043729b        switch (ebx_1)
004372a2        case 0
004372a2        uint16_t runtime_flags = (runtime->runtime_flags).w
004372a8        if ((runtime_flags:1.b & 4) == 0)
004372ad        return 0x2c
004372b3        if ((runtime_flags.b & 1) == 0)
004372bc        return 0x2e
00437400        case 1
00437400        uint16_t runtime_flags_4 = (runtime->runtime_flags).w
00437406        if ((runtime_flags_4:1.b & 8) == 0)
0043740a        char eax = runtime_flags_4.b & 0x40
0043740c        char temp2_1 = eax
0043740c        eax = neg.b(eax)
00437412        return (sbb.b(eax, eax, temp2_1 != 0) & 0x31) + 0x2e
004373f8        case 2
004373f8        if (((runtime->runtime_flags).w:1.b & 0x40) == 0)
004373fd        return 0x2e
004372c5        case 3
004372c5        if (((runtime->runtime_flags).w:1.b & 2) == 0)
004372ce        return 0x2e
00437384        case 4
00437384        uint32_t runtime_flags_1 = runtime->runtime_flags
0043738a        if ((runtime_flags_1:1.b & 1) == 0)
00437393        if ((runtime_flags_1.b & 1) == 0)
00437398        return 0x2e
0043739b        int32_t ecx_1 = runtime_flags_1 & 0x400
004373a2        char ecx_2 = (neg.d(ecx_1)).b
004373ae        return (sbb.b(ecx_2, ecx_2, ecx_1 != 0) & 0xf4) + 0x2c
0043733e        case 5
0043733e        uint16_t runtime_flags_7 = (runtime->runtime_flags).w
00437344        if ((runtime_flags_7:1.b & 2) == 0)
00437349        return 0x2e
0043734f        if ((runtime_flags_7.b & 0x20) == 0)
00437354        return 0x3c
0043735c        if (runtime->track_mirror_enabled != 0)
00437365        return 0x5b
00437314        case 6
00437314        runtime_flags_5 = (runtime->runtime_flags).w
0043731a        if ((runtime_flags_5:1.b & 2) == 0)
0043731f        return 0x2e
00437325        if ((runtime_flags_5.b & 0x20) == 0)
0043732a        return 0x3c
0043731a        goto label_437330
00437378        case 7
00437378        if ((runtime->runtime_flags.b & 0x40) == 0 && edge_row == 0)
00437381        return 0x2e
004373da        case 8
004373da        uint8_t runtime_flags_3 = (runtime->runtime_flags).b
004373e0        if ((runtime_flags_3 & 4) == 0)
004373e5        uint8_t eax_2 = runtime_flags_3 & 0x40
004373e7        uint8_t temp1 = eax_2
004373e7        eax_2 = neg.b(eax_2)
004373ef        return (sbb.b(eax_2, eax_2, temp1 != 0) & 0x31) + 0x2e
004372ea        case 9
004372ea        uint16_t runtime_flags_6 = (runtime->runtime_flags).w
004372f0        if ((runtime_flags_6:1.b & 2) == 0)
004372f5        return 0x2e
004372fb        if ((runtime_flags_6.b & 0x20) == 0)
00437300        return 0x3e
00437308        if (runtime->track_mirror_enabled != 0)
00437311        return 0x7d
004373b1        case 0xa
004373b1        uint32_t runtime_flags_2 = runtime->runtime_flags
004373b7        if ((runtime_flags_2:1.b & 1) == 0)
004373bc        if ((runtime_flags_2.b & 1) == 0)
004373c1        return 0x20
004373c4        int32_t ecx_4 = runtime_flags_2 & 0x400
004373cb        char ecx_5 = (neg.d(ecx_4)).b
004373d7        return (sbb.b(ecx_5, ecx_5, ecx_4 != 0) & 0x11) + 0x2c
004372d1        case 0xb
004372d1        runtime_flags_5 = (runtime->runtime_flags).w
004372d7        if ((runtime_flags_5:1.b & 2) == 0)
004372dc        return 0x2e
004372e2        if ((runtime_flags_5.b & 0x20) == 0)
004372e7        return 0x3e
00437330        label_437330:
00437332        if (runtime->track_mirror_enabled != 0)
0043733b        return 0x7b
00437415        return glyph
