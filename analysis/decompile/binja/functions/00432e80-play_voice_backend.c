/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: play_voice_backend @ 0x432e80 */

00432e87        if (arg1 == 0xffffffff)
00432e87        return 
00432e89        long double x87_r7_1 = fconvert.t(arg4)
00432e8d        long double temp0_1 = fconvert.t(0f)
00432e8d        x87_r7_1 - temp0_1
00432e98        if ((((x87_r7_1 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp0_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp0_1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
00432e9a        long double x87_r7_2 = fconvert.t(arg3)
00432e9e        long double temp1 = fconvert.t(-1f)
00432e9e        x87_r7_2 - temp1
00432ea9        if ((((x87_r7_2 < temp1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp1) ? 1 : 0) << 0xa | (x87_r7_2 == temp1 ? 1 : 0) << 0xe):1.b & 0x40) == 0)
00432ed4        int32_t var_8_1 = arg1
00432ede        play_registered_sound_sample_backend(arg1, fconvert.s(fconvert.t(data_753c6c) * fconvert.t(arg2)), arg3)
00432ee3        return 
00432eb5        int32_t var_4_1 = arg1
00432ebf        play_registered_sound_sample_scaled(arg1, fconvert.s(fconvert.t(data_753c6c) * fconvert.t(arg2)))
00432ec4        return 
00432ef8        int32_t var_c_2 = arg1
00432f02        play_registered_sound_sample_scaled_panned(arg1, fconvert.s(fconvert.t(data_753c6c) * fconvert.t(arg2)), -1f, arg4)
00432f07        return
