/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: play_registered_sound_sample_scaled @ 0x4499a0 */

004499a0        long double x87_r7 = fconvert.t(volume)
004499a4        long double temp1 = fconvert.t(0f)
004499a4        x87_r7 - temp1
004499af        if ((((x87_r7 < temp1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7, temp1) ? 1 : 0) << 0xa | (x87_r7 == temp1 ? 1 : 0) << 0xe):1.b & 1) != 0)
004499af        return
004499b1        long double x87_r7_1 = fconvert.t(volume)
004499b5        long double temp2_1 = fconvert.t(1f)
004499b5        x87_r7_1 - temp2_1
004499c0        int32_t volume_1
004499c0        int16_t x87control
004499c0        if ((((x87_r7_1 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp2_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp2_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
004499eb        volume_1 = ftol(x87control, fconvert.t(1f) * fconvert.t(100f))
00449a01        g_bass_sample_play_ex(g_registered_sound_sample_handles[sample_id], 0, 0xffffffff, volume_1, 0, 0xffffffff)
00449a01        return
004499cc        long double x87_r7_2 = fconvert.t(volume)
004499d0        long double temp3_1 = fconvert.t(0f)
004499d0        x87_r7_2 - temp3_1
004499db        if ((((x87_r7_2 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp3_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp3_1 ? 1 : 0) << 0xe):1.b & 0x40) == 0)
004499eb        volume_1 = ftol(x87control, fconvert.t(volume) * fconvert.t(100f))
00449a01        g_bass_sample_play_ex(g_registered_sound_sample_handles[sample_id], 0, 0xffffffff, volume_1, 0, 0xffffffff)
00449a07        return
