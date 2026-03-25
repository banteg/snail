/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_options_menu @ 0x41af60 */

0041af6c        data_4df91c = *(arg1[7] + 0x17c)
0041af7b        data_4df918 = *(arg1[6] + 0x17c)
0041af80        int32_t eax_1
0041af80        eax_1.b = data_4df920
0041af87        char* var_c
0041af87        char* var_8
0041af87        if (eax_1.b == 0)
0041af9d        var_8 = "Full-screen Off"
0041afa8        var_c = arg1[5] + 0x2cc
0041af8c        var_8 = "Full-screen On"
0041af97        var_c = arg1[5] + 0x2cc
0041afa9        sub_44e5b0(var_c, var_8)
0041afae        void* ecx_3 = arg1[5]
0041afb4        int32_t eax_2 = *(ecx_3 + 0x1a0)
0041afbc        if ((eax_2.b & 0x20) != 0)
0041afbe        eax_2.b &= 0xdf
0041afc0        *(ecx_3 + 0x1a0) = eax_2
0041afc6        eax_2.b = data_4df920
0041afcd        if (eax_2.b == 0)
0041afe4        set_fullscreen_mode(1)
0041afec        data_4df920 = 1
0041afd1        set_fullscreen_mode(0)
0041afd9        data_4df920 = 0
0041aff3        void* ecx_4 = arg1[6]
0041aff6        int32_t eax_3 = *(ecx_4 + 0x1a0)
0041affe        if ((eax_3.b & 0x20) != 0)
0041b000        eax_3.b &= 0xdf
0041b002        *(ecx_4 + 0x1a0) = eax_3
0041b008        void* ecx_5 = arg1[4]
0041b00b        int32_t eax_4 = *(ecx_5 + 0x1a0)
0041b013        if ((eax_4.b & 0x20) != 0)
0041b015        eax_4.b &= 0xdf
0041b017        *(ecx_5 + 0x1a0) = eax_4
0041b01f        destroy_options_menu(arg1)
0041b029        *(data_4df904 + 0x568) = 0
0041b038        *(data_4df904 + 0x1b8) = *arg1
0041b040        apply_audio_config_volumes()
0041b045        long double x87_r7 = fconvert.t(arg1[8])
0041b048        long double temp0 = fconvert.t(data_4df918)
0041b048        x87_r7 - temp0
0041b04e        int32_t result
0041b04e        result.w = (x87_r7 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r7, temp0) ? 1 : 0) << 0xa | (x87_r7 == temp0 ? 1 : 0) << 0xe
0041b053        if ((result:1.b & 0x40) == 0)
0041b05c        play_sound_effect(8)
0041b061        result = data_4df918
0041b066        arg1[8] = result
0041b06a        return result
