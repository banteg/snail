/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_high_score_screen @ 0x417260 */

00417260        int32_t* var_4 = arg1
0041726b        int32_t result
0041726b        if (arg1[4].b == 0)
0041738e        void* ecx_19 = arg1[8]
00417391        int32_t eax_14 = *(ecx_19 + 0x1a0)
00417399        if ((eax_14.b & 0x20) != 0)
0041739b        eax_14.b &= 0xdf
0041739d        *(ecx_19 + 0x1a0) = eax_14
004173a5        destroy_high_score_screen(arg1)
004173aa        int32_t eax_15 = arg1[2]
004173b0        if (eax_15 == 0)
004173be        arg1[2] = 1
004173b3        if (eax_15 == 1)
004173b5        arg1[2] = 0
004173ca        data_4df9c0 = arg1[2]
004173de        return initialize_high_score_screen(arg1, arg1[2], 0xffffffff)
004173df        void* ecx_24 = arg1[7]
004173e2        int32_t eax_20 = *(ecx_24 + 0x1a0)
004173ea        if ((eax_20.b & 0x20) != 0)
004173ec        eax_20.b &= 0xdf
004173f3        *(ecx_24 + 0x1a0) = eax_20
004173f9        int32_t eax_21 = arg1[1]
004173fe        if (eax_21 == 1)
00417408        *(data_4df904 + 0x1b8) = 0xa
00417417        *(data_4df904 + 0x30c) = 1
0041741d        destroy_high_score_screen(arg1)
00417426        return 0
00417429        if (eax_21 == 0)
00417431        *(data_4df904 + 0x1b8) = 4
0041743d        destroy_high_score_screen(arg1)
00417446        return 0
00417447        void* edx_12 = data_4df904
0041744d        int32_t ebp_1 = 0
0041744f        result = *(edx_12 + 0x6ffae4)
00417457        if (result s> 0)
00417464        int32_t edi_1 = 0
00417466        var_4 = &arg1[0x33]
00417478        if (*(*(edx_12 + 0x6ffae0) + edi_1) == 1)
00417482        void* ecx_31 = *var_4
00417486        if (ecx_31 != 0)
0041748c        int32_t eax_25 = *(ecx_31 + 0x1a0)
00417494        if ((eax_25.b & 0x20) != 0)
00417496        eax_25.b &= 0xdf
00417498        *(ecx_31 + 0x1a0) = eax_25
004174a4        *(data_4df904 + 0x1b8) = 0xa
004174b6        *(data_4df904 + 0x30c) = 1
004174bc        destroy_high_score_screen(arg1)
004174c1        void* eax_26 = data_4df904
004174ce        *(eax_26 + 0x1066bec) = *(eax_26 + 0x6ffae0) + edi_1
004174da        *(data_4df904 + 0x1066be8) = 1
004174e5        *(data_4df904 + 0x1066be9) = 1
004174f1        *(data_4df904 + 0x1066bf0) = 0x12
004174fb        void* eax_28 = data_4df904
00417509        *(eax_28 + 0x74658) = *(*(eax_28 + 0x1066bec) + 0x2c)
0041750f        edx_12 = data_4df904
00417519        ebp_1 += 1
0041751d        edi_1 += 0x1fac0
00417523        var_4 = &var_4[1]
00417527        result = *(edx_12 + 0x6ffae4)
0041752f        do while (ebp_1 s< result)
00417274        void* ecx = arg1[arg1[5] + 0x1f]
00417278        int32_t eax_2 = *(ecx + 0x1a0)
00417281        if ((eax_2:1.b & 0x40) != 0)
00417287        eax_2:1.b &= 0xbf
0041728a        *(ecx + 0x1a0) = eax_2
00417292        destroy_high_score_screen(arg1)
0041729c        kill_game_sprites()
004172a1        int32_t eax_3 = arg1[5]
004172d3        rstrcpy_checked_ascii(*(data_4df904 + 0x6ffae0) + eax_3 * 0x1fac0 + 0x54, arg1[eax_3 + 0x1f] + 0x2cc)
004172f1        rstrcpy_checked_ascii(data_4df904 + 0x1a4, arg1[arg1[5] + 0x1f] + 0x2cc)
00417309        rstrcpy_checked_ascii(&data_4df978, arg1[arg1[5] + 0x1f] + 0x2cc)
0041731c        return exit_high_score_screen()
0041731d        void* ecx_11 = arg1[0xa]
00417320        int32_t eax_10 = *(ecx_11 + 0x1a0)
00417328        if ((eax_10.b & 0x20) != 0)
0041732a        eax_10.b &= 0xdf
0041732c        *(ecx_11 + 0x1a0) = eax_10
00417335        void* eax_12 = arg1[arg1[5] + 0x1f]
00417339        *(eax_12 + 0x1a0) |= 0x8000000
00417343        void* ecx_12 = arg1[9]
00417346        result = *(ecx_12 + 0x1a0)
0041734e        if ((result.b & 0x20) != 0)
00417354        result.b &= 0xdf
00417356        *(ecx_12 + 0x1a0) = result
0041735e        destroy_high_score_screen(arg1)
00417368        kill_game_sprites()
0041737d        commit_high_score_entry_into_top_ten(data_4df904 + 0x6ffae0, arg1[5])
0041738d        return exit_high_score_screen()
0041753a        return result
