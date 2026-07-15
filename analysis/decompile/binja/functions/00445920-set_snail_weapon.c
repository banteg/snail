/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: set_snail_weapon @ 0x445920 */

00445920        struct Snail* snail_1 = snail
0044592b        char ecx = 0
00445933        int32_t movement_flags_1
00445933        int32_t movement_flags_2
00445933        if (movement_flags - 1 u> 0xbf)
0044599c        movement_flags_2 = movement_flags
004459a0        movement_flags_1 = movement_flags
00445935        int32_t edx_1 = 0
00445937        edx_1.b = *(movement_flags + &set_snail_weapon_movement_jump_table[6]:3)
0044593d        switch (edx_1)
00445944        case 0
00445944        movement_flags_2 = 0
00445946        movement_flags_1 = 0
00445948        snail_1 = 1
00445952        case 1
00445952        movement_flags_2 = 1
00445957        snail_1 = nullptr
0044595f        movement_flags_1 = 1
00445963        case 2
00445963        movement_flags_1 = 1
00445968        movement_flags_2 = 1
0044596a        snail_1 = 1
00445970        case 3
00445970        movement_flags_2 = 0
00445972        movement_flags_1 = 2
00445977        snail_1 = nullptr
0044598b        case 4
0044598b        movement_flags_2 = 2
00445990        snail_1 = nullptr
00445998        movement_flags_1 = 2
0044597d        case 5
0044597d        movement_flags_2 = 0
0044597f        movement_flags_1 = 0
00445981        snail_1 = 3
0044599c        case 6
0044599c        movement_flags_2 = movement_flags
004459a0        movement_flags_1 = movement_flags
004459a4        int32_t selected_state = snail->weapon_channels[0].selected_state
004459aa        movement_flags.b = 1
004459b1        if (selected_state != movement_flags_2)
004459b8        if (selected_state == 1)
004459c5        int32_t var_18_2 = 8
004459c7        int32_t var_1c_2 = 1
004459d1        set_weapon_animation(&snail->weapon_channels, 1, 1, 8)
004459d6        movement_flags.b = 0
004459bb        if (selected_state == 2)
004459bd        int32_t var_18_1 = 8
004459bf        int32_t var_1c_1 = 1
004459d1        set_weapon_animation(&snail->weapon_channels, 4, 1, 8)
004459d6        movement_flags.b = 0
004459e0        if (movement_flags_2 == 0)
00445a28        int32_t var_18_5 = 0xffffffff
00445a2a        int32_t var_1c_7 = 0
00445a34        set_weapon_animation(&snail->weapon_channels, 0xffffffff, 0, 0xffffffff)
004459e3        if (movement_flags_2 == 1)
00445a19        set_weapon_animation(&snail->weapon_channels, 1, movement_flags.b, 4)
00445a1e        int32_t var_18_4 = 0xffffffff
00445a20        int32_t var_1c_6 = 0
00445a34        set_weapon_animation(&snail->weapon_channels, 0, 0, 0xffffffff)
004459e6        if (movement_flags_2 == 2)
004459f9        set_weapon_animation(&snail->weapon_channels, 4, movement_flags.b, 4)
004459fe        int32_t var_18_3 = 0xffffffff
00445a00        int32_t var_1c_4 = 0
00445a34        set_weapon_animation(&snail->weapon_channels, 3, 0, 0xffffffff)
00445a39        snail->weapon_channels[0].selected_state = movement_flags_2
00445a3f        ecx = 1
00445a41        int32_t selected_state_1 = snail->weapon_channels[1].selected_state
00445a47        movement_flags.b = 1
00445a4e        if (selected_state_1 != movement_flags_1)
00445a55        if (selected_state_1 == 1)
00445a62        int32_t var_18_7 = 8
00445a64        int32_t var_1c_9 = 1
00445a6e        set_weapon_animation(&snail->weapon_channels[1], 1, 1, 8)
00445a73        movement_flags.b = 0
00445a58        if (selected_state_1 == 2)
00445a5a        int32_t var_18_6 = 8
00445a5c        int32_t var_1c_8 = 1
00445a6e        set_weapon_animation(&snail->weapon_channels[1], 4, 1, 8)
00445a73        movement_flags.b = 0
00445a7d        if (movement_flags_1 == 0)
00445ac5        int32_t var_18_10 = 0xffffffff
00445ac7        int32_t var_1c_14 = 0
00445ad1        set_weapon_animation(&snail->weapon_channels[1], 0xffffffff, 0, 0xffffffff)
00445a80        if (movement_flags_1 == 1)
00445ab6        set_weapon_animation(&snail->weapon_channels[1], 1, movement_flags.b, 4)
00445abb        int32_t var_18_9 = 0xffffffff
00445abd        int32_t var_1c_13 = 0
00445ad1        set_weapon_animation(&snail->weapon_channels[1], 0, 0, 0xffffffff)
00445a83        if (movement_flags_1 == 2)
00445a96        set_weapon_animation(&snail->weapon_channels[1], 4, movement_flags.b, 4)
00445a9b        int32_t var_18_8 = 0xffffffff
00445a9d        int32_t var_1c_11 = 0
00445ad1        set_weapon_animation(&snail->weapon_channels[1], 3, 0, 0xffffffff)
00445ad6        snail->weapon_channels[1].selected_state = movement_flags_1
00445adc        ecx = 1
00445ade        int32_t selected_state_2 = snail->weapon_channels[2].selected_state
00445ae4        int32_t snail_2 = snail_1
00445aea        movement_flags.b = 1
00445aef        if (selected_state_2 == snail_2)
00445bd9        if (ecx != 0)
00445be2        play_sound_effect(0x19)
00445bec        return
00445af6        if (selected_state_2 == 1)
00445b05        int32_t var_18_12 = 8
00445b07        int32_t var_1c_16 = 1
00445b11        set_weapon_animation(&snail->weapon_channels[2], 1, 1, 8)
00445b16        movement_flags.b = 0
00445afb        if (selected_state_2 == 3)
00445afd        int32_t var_18_11 = 8
00445aff        int32_t var_1c_15 = 1
00445b11        set_weapon_animation(&snail->weapon_channels[2], 4, 1, 8)
00445b16        movement_flags.b = 0
00445b20        if (snail_2 == 0)
00445bb8        set_weapon_animation(&snail->weapon_channels[2], 0xffffffff, 0, 0xffffffff)
00445b27        if (snail_2 == 1)
00445b80        set_weapon_animation(&snail->weapon_channels[2], 1, movement_flags.b, 4)
00445b8d        set_weapon_animation(&snail->weapon_channels[2], 0, 0, 0xffffffff)
00445b99        snail->weapon_channels[2].selected_state = snail_2
00445b9f        play_sound_effect(0x19)
00445ba9        return
00445b2c        if (snail_2 == 3)
00445b43        set_weapon_animation(&snail->weapon_channels[2], 4, movement_flags.b, 4)
00445b50        set_weapon_animation(&snail->weapon_channels[2], 3, 0, 0xffffffff)
00445b5c        snail->weapon_channels[2].selected_state = snail_2
00445b62        play_sound_effect(0x19)
00445b6c        return
00445bc4        snail->weapon_channels[2].selected_state = snail_2
00445bca        play_sound_effect(0x19)
00445bd4        return
