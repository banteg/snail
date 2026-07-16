/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: play_registered_sound_sample_backend @ 0x449a80 */

00449a80        long double x87_r7 = fconvert.t(arg2)
00449a84        long double temp1 = fconvert.t(0f)
00449a84        x87_r7 - temp1
00449a8a        int16_t result = (x87_r7 < temp1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7, temp1) ? 1 : 0) << 0xa | (x87_r7 == temp1 ? 1 : 0) << 0xe
00449a8f        if ((result:1.b & 1) == 0)
00449a91        long double x87_r7_1 = fconvert.t(arg2)
00449a95        long double temp2_1 = fconvert.t(1f)
00449a95        x87_r7_1 - temp2_1
00449aa0        if ((((x87_r7_1 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp2_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp2_1 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
00449aa2        long double x87_r7_2 = fconvert.t(arg2)
00449aa6        long double temp3_1 = fconvert.t(0f)
00449aa6        x87_r7_2 - temp3_1
00449aac        result = (x87_r7_2 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp3_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp3_1 ? 1 : 0) << 0xe
00449ab1        if ((((x87_r7_1 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp2_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp2_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0 || (result:1.b & 0x40) == 0)
00449abd        int16_t x87control
00449abd        int32_t frequency = ftol(x87control, fconvert.t(arg3))
00449ad1        return g_bass_sample_play_ex(g_registered_sound_sample_handles[arg1], 0, frequency, 0xffffffff, 0x65, 0)
00449ad7        return result
