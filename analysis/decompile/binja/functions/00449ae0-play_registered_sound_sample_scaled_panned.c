/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: play_registered_sound_sample_scaled_panned @ 0x449ae0 */

00449ae0        long double x87_r7 = fconvert.t(arg2)
00449ae4        long double temp1 = fconvert.t(0f)
00449ae4        x87_r7 - temp1
00449aea        int16_t result = (x87_r7 < temp1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7, temp1) ? 1 : 0) << 0xa | (x87_r7 == temp1 ? 1 : 0) << 0xe
00449aef        if ((result:1.b & 1) == 0)
00449af1        long double x87_r7_1 = fconvert.t(arg2)
00449af5        long double temp2_1 = fconvert.t(1f)
00449af5        x87_r7_1 - temp2_1
00449b00        if ((((x87_r7_1 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp2_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp2_1 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
00449b02        long double x87_r7_2 = fconvert.t(arg2)
00449b06        long double temp3_1 = fconvert.t(0f)
00449b06        x87_r7_2 - temp3_1
00449b0c        result = (x87_r7_2 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp3_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp3_1 ? 1 : 0) << 0xe
00449b11        if ((((x87_r7_1 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp2_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp2_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0 || (result:1.b & 0x40) == 0)
00449b19        int32_t pan
00449b19        int16_t x87control
00449b19        int16_t x87control_1
00449b19        pan, x87control_1 = ftol(x87control, fconvert.t(arg4))
00449b25        int32_t frequency = ftol(x87control_1, fconvert.t(arg3))
00449b39        return g_bass_sample_play_ex(g_registered_sound_sample_handles[arg1], 0, frequency, 0xffffffff, pan, 0)
00449b3f        return result
