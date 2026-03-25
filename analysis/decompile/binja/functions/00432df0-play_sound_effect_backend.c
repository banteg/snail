/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: play_sound_effect_backend @ 0x432df0 */

00432df7        if (arg1 == 0xffffffff)
00432df7        return 
00432df9        long double x87_r7_1 = fconvert.t(arg4)
00432dfd        long double temp0_1 = fconvert.t(0f)
00432dfd        x87_r7_1 - temp0_1
00432e08        if ((((x87_r7_1 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp0_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp0_1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
00432e0a        long double x87_r7_2 = fconvert.t(arg3)
00432e0e        long double temp1 = fconvert.t(-1f)
00432e0e        x87_r7_2 - temp1
00432e19        if ((((x87_r7_2 < temp1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp1) ? 1 : 0) << 0xa | (x87_r7_2 == temp1 ? 1 : 0) << 0xe):1.b & 0x40) == 0)
00432e44        int32_t var_8_1 = arg1
00432e4e        play_registered_sound_sample_backend(arg1, fconvert.s(fconvert.t(data_753c68) * fconvert.t(arg2)), arg3)
00432e53        return 
00432e25        int32_t var_4_1 = arg1
00432e2f        play_registered_sound_sample_scaled(arg1, fconvert.s(fconvert.t(data_753c68) * fconvert.t(arg2)))
00432e34        return 
00432e68        int32_t var_c_2 = arg1
00432e72        play_registered_sound_sample_scaled_panned(arg1, fconvert.s(fconvert.t(data_753c68) * fconvert.t(arg2)), -1f, arg4)
00432e77        return
