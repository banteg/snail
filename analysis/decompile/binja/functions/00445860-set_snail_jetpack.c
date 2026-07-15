/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: set_snail_jetpack @ 0x445860 */

0044586b        int32_t mode_flags
0044586b        int32_t eax_3
0044586b        if (state == 0)
00445877        mode_flags = 0
0044586e        if (eax_3 != 1)
0044587b        mode_flags = state
00445870        mode_flags = 4
0044587f        int32_t selected_state = snail->jetpack_channel.selected_state
00445885        state.b = 1
0044588c        if (selected_state == mode_flags)
0044588c        return
00445895        if (selected_state == 4)
004458a3        set_weapon_animation(&snail->jetpack_channel, 1, 1, 8)
004458af        state.b = 0
004458b4        play_sound_effect(0x1a)
004458bb        if (mode_flags == 0)
00445909        set_weapon_animation(&snail->jetpack_channel, 0xffffffff, 0, 0xffffffff)
004458c0        if (mode_flags == 4)
004458d3        set_weapon_animation(&snail->jetpack_channel, 1, state.b, mode_flags)
004458e0        set_weapon_animation(&snail->jetpack_channel, 0, 0, 0xffffffff)
004458ec        play_sound_effect(0x10)
004458f2        snail->jetpack_channel.selected_state = mode_flags
004458fa        return
0044590e        snail->jetpack_channel.selected_state = mode_flags
00445916        return
