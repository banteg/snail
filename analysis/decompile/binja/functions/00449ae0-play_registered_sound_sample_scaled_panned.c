/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: play_registered_sound_sample_scaled_panned @ 0x449ae0 */

00449ae0        long double x87_r7 = fconvert.t(volume)
00449ae4        long double temp1 = fconvert.t(0f)
00449ae4        x87_r7 - temp1
00449aef        if ((((x87_r7 < temp1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7, temp1) ? 1 : 0) << 0xa | (x87_r7 == temp1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00449aef        return
00449af1        long double x87_r7_1 = fconvert.t(volume)
00449af5        long double temp2_1 = fconvert.t(1f)
00449af5        x87_r7_1 - temp2_1
00449b00        long double x87_r7_2
00449b00        long double temp3_1
00449b00        if ((((x87_r7_1 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp2_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp2_1 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
00449b02        x87_r7_2 = fconvert.t(volume)
00449b06        temp3_1 = fconvert.t(0f)
00449b06        x87_r7_2 - temp3_1
00449b11        if ((((x87_r7_1 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp2_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp2_1 ? 1 : 0) << 0xe):1.b & 0x41) != 0 && (((x87_r7_2 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp3_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp3_1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
00449b11        return
00449b19        int32_t pan_1
00449b19        int16_t x87control
00449b19        int16_t x87control_1
00449b19        pan_1, x87control_1 = ftol(x87control, fconvert.t(pan))
00449b25        int32_t frequency = ftol(x87control_1, fconvert.t(pitch))
00449b39        g_bass_sample_play_ex(g_registered_sound_sample_handles[sample_id], 0, frequency, 0xffffffff, pan_1, 0)
00449b3f        return
