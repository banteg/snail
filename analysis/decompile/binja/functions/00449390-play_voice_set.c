/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: play_voice_set @ 0x449390 */

00449393        long double x87_r7 = fconvert.t(arg1[4])
00449396        long double temp1 = fconvert.t(0f)
00449396        x87_r7 - temp1
004493a1        if ((((x87_r7 < temp1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7, temp1) ? 1 : 0) << 0xa | (x87_r7 == temp1 ? 1 : 0) << 0xe):1.b & 0x40) == 0)
00449401        int16_t eax
00449401        eax.b = 0
00449404        return eax
004493a8        arg1[4] = arg1[5]
004493bc        int32_t eax_4
004493bc        if (arg2 != 0xffffffff)
004493f3        play_voice_backend(arg2, 1f, -1f, 0f)
004493ce        play_voice_backend(*(arg1[3] + (*(arg1[2] + (arg1[1] << 2)) << 2)), 1f, -1f, 0f)
004493d6        int32_t ecx_2 = *arg1
004493db        int32_t edx_4 = arg1[1] + 1
004493de        arg1[1] = edx_4
004493e3        if (edx_4 == ecx_2)
004493e5        arg1[1] = 0
004493ec        eax_4.b = 1
004493ef        return eax_4
004493fb        eax_4.b = 1
004493fe        return eax_4
