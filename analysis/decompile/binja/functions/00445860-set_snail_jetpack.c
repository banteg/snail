/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: set_snail_jetpack @ 0x445860 */

0044586b        int32_t initial_frame
0044586b        int32_t eax_5
0044586b        if (arg2 == 0)
00445877        initial_frame = 0
0044586e        if (eax_5 != 1)
0044587b        initial_frame = arg2
00445870        initial_frame = 4
0044587f        int32_t eax_2 = *(arg1 + 0x12e4)
00445885        arg2.b = 1
0044588c        if (eax_2 != initial_frame)
00445895        if (eax_2 == 4)
004458a3        set_weapon_animation(arg1 + 0x11e0, 1, 1, 8)
004458af        arg2.b = 0
004458b4        eax_2 = play_sound_effect(0x1a)
004458bb        if (initial_frame == 0)
00445909        eax_2 = set_weapon_animation(arg1 + 0x11e0, 0xffffffff, 0, 0xffffffff)
004458c0        if (initial_frame == 4)
004458d3        set_weapon_animation(arg1 + 0x11e0, 1, arg2.b, initial_frame)
004458e0        set_weapon_animation(arg1 + 0x11e0, 0, 0, 0xffffffff)
004458ec        int32_t eax_4 = play_sound_effect(0x10)
004458f2        *(arg1 + 0x12e4) = initial_frame
004458fa        return eax_4
0044590e        *(arg1 + 0x12e4) = initial_frame
00445916        return eax_2
