/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: play_sound_effect_backend @ 0x432df0 */

00432df7        if (sample_id == 0xffffffff)
00432df7        return
00432df9        long double x87_r7_1 = fconvert.t(pan)
00432dfd        long double temp0_1 = fconvert.t(0f)
00432dfd        x87_r7_1 - temp0_1
00432e08        if ((((x87_r7_1 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp0_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp0_1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
00432e0a        long double x87_r7_2 = fconvert.t(pitch)
00432e0e        long double temp1 = fconvert.t(-1f)
00432e0e        x87_r7_2 - temp1
00432e19        if ((((x87_r7_2 < temp1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp1) ? 1 : 0) << 0xa | (x87_r7_2 == temp1 ? 1 : 0) << 0xe):1.b & 0x40) == 0)
00432e44        int32_t sample_id_2 = sample_id
00432e4e        play_registered_sound_sample_backend(&g_audio_backend, sample_id, fconvert.s(fconvert.t(g_audio_backend_sfx_normalization_scale) * fconvert.t(gain)), pitch)
00432e53        return
00432e25        int32_t sample_id_3 = sample_id
00432e2f        play_registered_sound_sample_scaled(&g_audio_backend, sample_id, fconvert.s(fconvert.t(g_audio_backend_sfx_normalization_scale) * fconvert.t(gain)))
00432e34        return
00432e68        int32_t sample_id_1 = sample_id
00432e72        play_registered_sound_sample_scaled_panned(&g_audio_backend, sample_id, fconvert.s(fconvert.t(g_audio_backend_sfx_normalization_scale) * fconvert.t(gain)), -1f, pan)
00432e77        return
