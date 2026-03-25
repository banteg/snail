/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: set_snail_jetpack @ 0x445860 */

0044586b        int32_t ebx
0044586b        int32_t eax_5
0044586b        if (arg2 == 0)
00445877        ebx = 0
0044586e        if (eax_5 != 1)
0044587b        ebx = arg2
00445870        ebx = 4
0044587f        int32_t eax_2 = *(arg1 + 0x12e4)
00445885        arg2.b = 1
0044588c        if (eax_2 != ebx)
00445895        if (eax_2 == 4)
004458a3        set_weapon_animation(arg1 + 0x11e0, 1, 1, 8)
004458af        arg2.b = 0
004458b4        eax_2 = play_sound_effect(0x1a)
004458bb        if (ebx == 0)
00445909        eax_2 = set_weapon_animation(arg1 + 0x11e0, 0xffffffff, 0, 0xffffffff)
004458c0        if (ebx == 4)
004458d3        set_weapon_animation(arg1 + 0x11e0, 1, arg2.b, ebx)
004458e0        set_weapon_animation(arg1 + 0x11e0, 0, 0, 0xffffffff)
004458ec        int32_t eax_4 = play_sound_effect(0x10)
004458f2        *(arg1 + 0x12e4) = ebx
004458fa        return eax_4
0044590e        *(arg1 + 0x12e4) = ebx
00445916        return eax_2
