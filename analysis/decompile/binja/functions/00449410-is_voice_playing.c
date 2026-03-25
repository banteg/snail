/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: is_voice_playing @ 0x449410 */

00449416        int32_t i = 0
00449418        int32_t* edi = arg1
0044941c        int32_t j = 0
00449420        if (*edi s> 0)
00449435        if (is_registered_sound_sample_playing(*(edi[3] + (j << 2))) != 0)
0044945d        return *(arg1[i * 6 + 3] + (j << 2))
00449439        j += 1
0044943c        do while (j s< *edi)
0044943e        i += 1
0044943f        edi = &edi[6]
00449445        do while (i s< 0x10)
0044944e        return 0xffffffff
