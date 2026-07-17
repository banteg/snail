/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: play_voice_set @ 0x449390 */

00449393        long double x87_r7 = fconvert.t(set->cooldown)
00449396        long double temp1 = fconvert.t(0f)
00449396        x87_r7 - temp1
0044939c        int16_t eax = (x87_r7 < temp1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7, temp1) ? 1 : 0) << 0xa | (x87_r7 == temp1 ? 1 : 0) << 0xe
004493a1        if ((eax:1.b & 0x40) == 0)
00449401        eax.b = 0
00449404        return 0
004493a8        set->cooldown = set->cooldown_step
004493bc        if (sample_override != 0xffffffff)
004493f3        play_voice_backend(sample_override, 1f, -1f, 0f)
004493ce        play_voice_backend(set->bites[set->playlist[set->next_index]], 1f, -1f, 0f)
004493d6        uint32_t sample_count = set->sample_count
004493db        uint32_t edx_4 = set->next_index + 1
004493de        set->next_index = edx_4
004493e3        if (edx_4 == sample_count)
004493e5        set->next_index = 0
004493ec        uint32_t eax_5
004493ec        eax_5.b = 1
004493ef        return 1
004493fb        uint32_t eax_6
004493fb        eax_6.b = 1
004493fe        return 1
