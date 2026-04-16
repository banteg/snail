/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: play_voice_manager @ 0x4492d0 */

004492df        if (mode == 0 || mode == 1)
00449336        int32_t eax_5
00449336        if (is_voice_playing(manager) != 0xffffffff)
00449339        eax_5.b = 0
0044933c        return eax_5
00449342        if (mode == 1)
00449344        long double x87_r7_1 = fconvert.t(manager->global_progress)
0044934a        long double temp1_1 = fconvert.t(manager->global_frequency_seconds)
0044934a        x87_r7_1 - temp1_1
00449350        eax_5.w = (x87_r7_1 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp1_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp1_1 ? 1 : 0) << 0xe
00449355        if ((eax_5:1.b & 1) != 0)
00449358        eax_5.b = 0
0044935b        return eax_5
004492e4        if (mode == 2)
004492e6        int32_t eax_1 = is_voice_playing(manager)
004492ee        if (eax_1 != 0xffffffff)
004492f6        stop_registered_sound_sample(eax_1)
0044930a        int32_t eax_4 = play_voice_set(&manager->sets[set_id], sample_override)
0044931b        if (eax_4.b == 1 && (mode == 1 || mode == 2))
0044931d        manager->global_progress = 0f
00449329        return eax_4
