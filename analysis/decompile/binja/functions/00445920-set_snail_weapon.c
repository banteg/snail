/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: set_snail_weapon @ 0x445920 */

00445920        void* const var_4 = arg1
00445928        void* esi = arg1
0044592b        arg1.b = 0
00445933        int32_t ebp
00445933        int32_t edi
00445933        if (arg2 - 1 u> 0xbf)
0044599c        edi = arg2
004459a0        ebp = arg2
00445937        int32_t edx_1
00445937        edx_1.b = *(arg2 + &jump_table_445bf0[6]:3)
0044593d        switch (edx_1)
00445944        case 0
00445944        edi = 0
00445946        ebp = 0
00445948        var_4 = 1
00445952        case 1
00445952        edi = 1
00445957        var_4 = nullptr
0044595f        ebp = 1
00445963        case 2
00445963        ebp = 1
00445968        edi = 1
0044596a        var_4 = 1
00445970        case 3
00445970        edi = 0
00445972        ebp = 2
00445977        var_4 = nullptr
0044598b        case 4
0044598b        edi = 2
00445990        var_4 = nullptr
00445998        ebp = 2
0044597d        case 5
0044597d        edi = 0
0044597f        ebp = 0
00445981        var_4 = 3
0044599c        case 6
0044599c        edi = arg2
004459a0        ebp = arg2
004459a4        int32_t eax_2 = *(esi + 0x750)
004459aa        arg2.b = 1
004459b1        if (eax_2 != edi)
004459b8        if (eax_2 == 1)
004459c5        int32_t var_18_2 = 8
004459c7        int32_t var_1c_2 = 1
004459d1        set_weapon_animation(esi + 0x64c, 1, 1, 8)
004459d6        arg2.b = 0
004459bb        if (eax_2 == 2)
004459bd        int32_t var_18_1 = 8
004459bf        int32_t var_1c_1 = 1
004459d1        set_weapon_animation(esi + 0x64c, 4, 1, 8)
004459d6        arg2.b = 0
004459e0        if (edi == 0)
00445a28        int32_t var_18_5 = 0xffffffff
00445a2a        int32_t var_1c_7 = 0
00445a34        set_weapon_animation(esi + 0x64c, 0xffffffff, 0, 0xffffffff)
004459e3        if (edi == 1)
00445a19        set_weapon_animation(esi + 0x64c, 1, arg2.b, 4)
00445a1e        int32_t var_18_4 = 0xffffffff
00445a20        int32_t var_1c_6 = 0
00445a34        set_weapon_animation(esi + 0x64c, 0, 0, 0xffffffff)
004459e6        if (edi == 2)
004459f9        set_weapon_animation(esi + 0x64c, 4, arg2.b, 4)
004459fe        int32_t var_18_3 = 0xffffffff
00445a00        int32_t var_1c_4 = 0
00445a34        set_weapon_animation(esi + 0x64c, 3, 0, 0xffffffff)
00445a39        *(esi + 0x750) = edi
00445a3f        arg1.b = 1
00445a41        int32_t eax_10 = *(esi + 0xb2c)
00445a47        arg2.b = 1
00445a4e        if (eax_10 != ebp)
00445a55        if (eax_10 == 1)
00445a62        int32_t var_18_7 = 8
00445a64        int32_t var_1c_9 = 1
00445a6e        set_weapon_animation(esi + 0xa28, 1, 1, 8)
00445a73        arg2.b = 0
00445a58        if (eax_10 == 2)
00445a5a        int32_t var_18_6 = 8
00445a5c        int32_t var_1c_8 = 1
00445a6e        set_weapon_animation(esi + 0xa28, 4, 1, 8)
00445a73        arg2.b = 0
00445a7d        if (ebp == 0)
00445ac5        int32_t var_18_10 = 0xffffffff
00445ac7        int32_t var_1c_14 = 0
00445ad1        set_weapon_animation(esi + 0xa28, 0xffffffff, 0, 0xffffffff)
00445a80        if (ebp == 1)
00445ab6        set_weapon_animation(esi + 0xa28, 1, arg2.b, 4)
00445abb        int32_t var_18_9 = 0xffffffff
00445abd        int32_t var_1c_13 = 0
00445ad1        set_weapon_animation(esi + 0xa28, 0, 0, 0xffffffff)
00445a83        if (ebp == 2)
00445a96        set_weapon_animation(esi + 0xa28, 4, arg2.b, 4)
00445a9b        int32_t var_18_8 = 0xffffffff
00445a9d        int32_t var_1c_11 = 0
00445ad1        set_weapon_animation(esi + 0xa28, 3, 0, 0xffffffff)
00445ad6        *(esi + 0xb2c) = ebp
00445adc        arg1.b = 1
00445ade        int32_t result = *(esi + 0xf08)
00445aea        arg2.b = 1
00445aef        if (result == var_4)
00445bd9        if (arg1.b == 0)
00445bec        return result
00445be2        return play_sound_effect(0x19)
00445af6        if (result == 1)
00445b05        int32_t var_18_12 = 8
00445b07        int32_t var_1c_16 = 1
00445b11        set_weapon_animation(esi + 0xe04, 1, 1, 8)
00445b16        arg2.b = 0
00445afb        if (result == 3)
00445afd        int32_t var_18_11 = 8
00445aff        int32_t var_1c_15 = 1
00445b11        set_weapon_animation(esi + 0xe04, 4, 1, 8)
00445b16        arg2.b = 0
00445b20        if (var_4 == 0)
00445bb8        set_weapon_animation(esi + 0xe04, 0xffffffff, 0, 0xffffffff)
00445b27        if (var_4 == 1)
00445b80        set_weapon_animation(esi + 0xe04, 1, arg2.b, 4)
00445b8d        set_weapon_animation(esi + 0xe04, 0, 0, 0xffffffff)
00445b99        *(esi + 0xf08) = var_4
00445ba9        return play_sound_effect(0x19)
00445b2c        if (var_4 == 3)
00445b43        set_weapon_animation(esi + 0xe04, 4, arg2.b, 4)
00445b50        set_weapon_animation(esi + 0xe04, 3, 0, 0xffffffff)
00445b5c        *(esi + 0xf08) = var_4
00445b6c        return play_sound_effect(0x19)
00445bc4        *(esi + 0xf08) = var_4
00445bd4        return play_sound_effect(0x19)
