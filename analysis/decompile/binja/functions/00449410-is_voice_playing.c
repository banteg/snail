/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: is_voice_playing @ 0x449410 */

00449416        int32_t i = 0
00449418        struct VoiceManager* manager_1 = manager
0044941c        int32_t j = 0
00449420        if (manager_1->sets[0].sample_count s> 0)
00449435        if (is_registered_sound_sample_playing(manager_1->sets[0].bites[j]) != 0)
0044945d        return manager->sets[i].bites[j]
00449439        j += 1
0044943c        do while (j s< manager_1->sets[0].sample_count)
0044943e        i += 1
0044943f        manager_1 = &manager_1->sets[1]
00449445        do while (i s< 0x10)
0044944e        return 0xffffffff
