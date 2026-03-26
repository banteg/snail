/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: handle_subgoldy_collisions @ 0x444cf0 */

00444d1d        struct Vec3 vector
00444d1d        struct Vec3 vector_2
00444d1d        if (player->attachment_exit_pending == 0 && player->_pad_41c == 0 && player->control_override_active == 0)
00444d2d        int16_t x87control
00444d2d        if ((0x80 & player->movement_flags.b) == 0)
00444d33        int32_t i = 0
00444e11        while (i s< 0x17c0)
00444d40        void* eax_2 = player->game + i
00444d55        if (*(eax_2 + 0x357940) == 1 && *(eax_2 + 0x357954) == 1)
00444d85        long double x87_r7_6 = fconvert.t(*(eax_2 + 0x357930)) - fconvert.t(player->cached_camera_target_world.z)
00444d8f        vector_2.x = fconvert.s(fconvert.t(*(eax_2 + 0x357928)) - fconvert.t(player->cached_camera_target_world.x))
00444d93        vector_2.y = fconvert.s(fconvert.t(*(eax_2 + 0x35792c)) - fconvert.t(player->cached_camera_target_world.y))
00444d9b        long double temp8_1 = fconvert.t(1f)
00444d9b        x87_r7_6 - temp8_1
00444da5        vector_2.z = fconvert.s(x87_r7_6)
00444da9        float eax_3
00444da9        eax_3.w = (x87_r7_6 < temp8_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_6, temp8_1) ? 1 : 0) << 0xa | (x87_r7_6 == temp8_1 ? 1 : 0) << 0xe
00444dae        if ((eax_3:1.b & 1) != 0)
00444db4        long double st0_1 = normalize_vector(&vector_2)
00444db9        long double temp13_1 = fconvert.t(0.980000019f)
00444db9        st0_1 - temp13_1
00444dc4        if ((((st0_1 < temp13_1 ? 1 : 0) << 8 | (is_unordered.t(st0_1, temp13_1) ? 1 : 0) << 0xa | (st0_1 == temp13_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00444dc6        long double x87_r7_8 = fconvert.t(player->damage_retrigger_timer)
00444dcc        long double temp17_1 = fconvert.t(0f)
00444dcc        x87_r7_8 - temp17_1
00444dd7        if ((((x87_r7_8 < temp17_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_8, temp17_1) ? 1 : 0) << 0xa | (x87_r7_8 == temp17_1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
00444ddf        player->damage_retrigger_timer = player->damage_retrigger_step
00444df8        *(i + player->game + 0x357954) = 0
00444e00        x87control = apply_damage_gauge_delta(&player->damage_gauge, 0.150000006f, 0)
00444e05        i += 0x98
00444e1e        int32_t i_1 = 0
00444ece        while (i_1 s< 0xdc0)
00444e26        void* eax_6 = player->game + i_1
00444e2e        if (*(eax_6 + 0x356b80) == 1)
00444e5e        long double x87_r7_14 = fconvert.t(*(eax_6 + 0x356b70)) - fconvert.t(player->cached_camera_target_world.z)
00444e68        vector.x = fconvert.s(fconvert.t(*(eax_6 + 0x356b68)) - fconvert.t(player->cached_camera_target_world.x))
00444e6c        vector.y = fconvert.s(fconvert.t(*(eax_6 + 0x356b6c)) - fconvert.t(player->cached_camera_target_world.y))
00444e74        long double temp7_1 = fconvert.t(1f)
00444e74        x87_r7_14 - temp7_1
00444e7e        vector.z = fconvert.s(x87_r7_14)
00444e82        float eax_7
00444e82        eax_7.w = (x87_r7_14 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_14, temp7_1) ? 1 : 0) << 0xa | (x87_r7_14 == temp7_1 ? 1 : 0) << 0xe
00444e87        if ((eax_7:1.b & 1) != 0)
00444e8d        long double st0_2 = normalize_vector(&vector)
00444e92        long double temp12_1 = fconvert.t(0.49000001f)
00444e92        st0_2 - temp12_1
00444e9d        if ((((st0_2 < temp12_1 ? 1 : 0) << 8 | (is_unordered.t(st0_2, temp12_1) ? 1 : 0) << 0xa | (st0_2 == temp12_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00444eac        *(i_1 + player->game + 0x356b80) = 2
00444ebd        x87control = apply_damage_gauge_delta(&player->damage_gauge, 0.0199999996f, 0)
00444ec2        i_1 += 0xb0
00444eda        void* i_2 = player->game->__offset(0x359140).d
00444ee2        while (i_2 != 0)
00444eee        if (*(i_2 + 0x84) == 1)
00444f15        long double x87_r7_21 = fconvert.t(*(i_2 + 0x70)) - fconvert.t(player->cached_camera_target_world.z)
00444f1f        vector.x = fconvert.s(fconvert.t(*(i_2 + 0x68)) - fconvert.t(player->cached_camera_target_world.x))
00444f23        vector.y = fconvert.s(fconvert.t(*(i_2 + 0x6c)) - fconvert.t(player->cached_camera_target_world.y))
00444f2b        long double temp20_1 = fconvert.t(1f)
00444f2b        x87_r7_21 - temp20_1
00444f35        vector.z = fconvert.s(x87_r7_21)
00444f39        float eax_9
00444f39        eax_9.w = (x87_r7_21 < temp20_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_21, temp20_1) ? 1 : 0) << 0xa | (x87_r7_21 == temp20_1 ? 1 : 0) << 0xe
00444f3e        if ((eax_9:1.b & 1) != 0)
00444f48        long double st0_3 = normalize_vector(&vector)
00444f4d        long double temp22_1 = fconvert.t(0.980000019f)
00444f4d        st0_3 - temp22_1
00444f58        if ((((st0_3 < temp22_1 ? 1 : 0) << 8 | (is_unordered.t(st0_3, temp22_1) ? 1 : 0) << 0xa | (st0_3 == temp22_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00444f64        if ((player->movement_flags.b & 0x80) == 0)
00444f7c        player->velocity.x = fconvert.s(fconvert.t(player->velocity.x) - fconvert.t(vector.x) * fconvert.t(player->velocity.z) * fconvert.t(0.180000007f))
00444f98        player->velocity.z = fconvert.s(fconvert.t(player->velocity.z) - fconvert.t(vector.z) * fconvert.t(player->velocity.z) * fconvert.t(0.100000001f))
00444fa3        *(i_2 + 0x84) = 2
00444fa9        long double x87_r7_31 = fconvert.t(vector.x)
00444fad        long double temp24_1 = fconvert.t(0f)
00444fad        x87_r7_31 - temp24_1
00444fb8        if ((((x87_r7_31 < temp24_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_31, temp24_1) ? 1 : 0) << 0xa | (x87_r7_31 == temp24_1 ? 1 : 0) << 0xe):1.b & 1) == 0)
00444fc2        *(i_2 + 0x88) = 1
00444fba        *(i_2 + 0x88) = 2
00444fce        add_subgoldy_score(player, 0, 0)
0044500a        x87control = play_sound_effect(0x27 - __ftol(apply_damage_gauge_delta(&player->damage_gauge, 0.0399999991f, 0), float.t(next_math_random_value()) * fconvert.t(-6.10351562e-05f)))
0044500f        i_2 = *(i_2 + 0x80)
0044501d        void* i_3 = nullptr
0044524b        while (i_3 s< 0x760)
0044501f        struct Game* game_9 = player->game
00445025        int32_t ecx_14 = *(i_3 + game_9 + 0x356420)
0044502c        void* eax_13 = i_3 + game_9
00445036        if (ecx_14 == 1 || ecx_14 == 4)
00445062        long double x87_r7_39 = fconvert.t(*(eax_13 + 0x356410)) - fconvert.t(player->cached_camera_target_world.z)
00445070        vector.x = fconvert.s(fconvert.t(*(eax_13 + 0x356408)) - fconvert.t(player->cached_camera_target_world.x))
00445074        vector.y = fconvert.s(fconvert.t(*(eax_13 + 0x35640c)) - fconvert.t(player->cached_camera_target_world.y))
0044507c        long double temp21_1 = fconvert.t(2f)
0044507c        x87_r7_39 - temp21_1
00445086        vector.z = fconvert.s(x87_r7_39)
0044508a        float eax_14
0044508a        eax_14.w = (x87_r7_39 < temp21_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_39, temp21_1) ? 1 : 0) << 0xa | (x87_r7_39 == temp21_1 ? 1 : 0) << 0xe
0044508f        if ((eax_14:1.b & 1) != 0)
00445099        long double st0_4 = normalize_vector(&vector)
004450a2        long double temp23_1 = fconvert.t(1.56750011f)
004450a2        st0_4 - temp23_1
004450ad        if ((((st0_4 < temp23_1 ? 1 : 0) << 8 | (is_unordered.t(st0_4, temp23_1) ? 1 : 0) << 0xa | (st0_4 == temp23_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
004450b9        if ((player->movement_flags.b & 0x80) != 0)
0044523a        x87control = kill_slug_hazard(i_3 + player->game + 0x3563a0)
004450bf        int16_t eax_15
004450bf        eax_15.b = player->control_override_active
004450c7        if (eax_15.b != 0)
0044520b        long double x87_r7_49 = fconvert.t(player->game->__offset(0x38).d)
0044521e        player->velocity.z = fconvert.s(x87_r7_49 * x87_r7_49 * fconvert.t(0.00400000019f) * fconvert.t(-8f))
00445226        x87control = apply_damage_gauge_delta(&player->damage_gauge, 1f, 0)
004450cd        struct Game* game = player->game
004450d3        player->control_override_active = 1
004450da        player->follow_state.active = 0
004450e9        long double x87_r7_41 = fconvert.t(game->__offset(0x38).d)
004450fe        player->velocity.x = 0
00445112        player->velocity.y = fconvert.s(x87_r7_41 * fconvert.t(0.200000003f))
0044511d        player->velocity.z = fconvert.s(x87_r7_41 * fconvert.t(-0.200000003f))
00445122        begin_post_follow_carryover(player)
00445127        struct Game* game_1 = player->game
0044512d        player->_pad_29ac[0x193c] = 0xa
0044512d        player->_pad_29ac[0x193d] = 0
0044512d        player->_pad_29ac[0x193e] = 0
0044512d        player->_pad_29ac[0x193f] = 0
00445137        *(i_3 + game_1 + 0x356479) = 1
00445152        int32_t eax_18 = __ftol(x87control, float.t(next_math_random_value()) * fconvert.t(-6.10351562e-05f))
0044516c        x87control = play_slug_voice(i_3 + player->game + 0x3563a0, 0x22 - eax_18)
00445175        long double x87_r7_46 = fconvert.t(fconvert.s(st0_4)) * fconvert.t(0.5f)
0044517b        player->_pad_29ac[0x15a0] = 0
0044517b        player->_pad_29ac[0x15a1] = 0
0044517b        player->_pad_29ac[0x15a2] = 0
0044517b        player->_pad_29ac[0x15a3] = 0
0044519d        long double x87_r7_47 = x87_r7_46 * fconvert.t(vector.z)
004451ab        vector_2.x = fconvert.s(fconvert.t(fconvert.s(x87_r7_46 * fconvert.t(vector.x))) + fconvert.t(player->cached_camera_target_world.x))
004451b3        long double x87_r6_10 = fconvert.t(fconvert.s(fconvert.t(vector.y) * x87_r7_46)) + fconvert.t(player->cached_camera_target_world.y)
004451bd        float x = vector_2.x
004451c8        vector_2.y = fconvert.s(x87_r6_10)
004451d6        float y = vector_2.y
004451e5        vector_2.z = fconvert.s(x87_r7_47 + fconvert.t(player->cached_camera_target_world.z))
004451ed        float z = vector_2.z
004451f1        firework_shoot(&x, player->player_slot, 1.28919459e-43f, 1.12103877e-43f)
0044523f        i_3 += 0xec
00445251        void* i_4 = nullptr
0044535a        while (i_4 s< 0x1b58)
00445253        struct Game* game_5 = player->game
00445259        void* eax_22 = i_4 + game_5
00445265        if (*(i_4 + game_5 + 0x125e4b8) == 1)
00445277        vector_2.x = fconvert.s(fconvert.t(*(eax_22 + 0x125e490)) - fconvert.t(player->cached_camera_target_world.x))
0044528b        vector_2.y = fconvert.s(fconvert.t(*(eax_22 + 0x125e494)) - fconvert.t(player->cached_camera_target_world.y))
00445295        long double x87_r7_56 = fconvert.t(*(eax_22 + 0x125e498)) - fconvert.t(player->cached_camera_target_world.z)
0044529f        struct Vec3 vector_3
0044529f        vector_3.x = vector_2.x
004452a3        vector_3.y = vector_2.y
004452a7        vector_2.z = fconvert.s(x87_r7_56)
004452ab        long double temp25_1 = fconvert.t(1f)
004452ab        x87_r7_56 - temp25_1
004452b5        vector_3.z = vector_2.z
004452b9        float eax_23
004452b9        eax_23.w = (x87_r7_56 < temp25_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_56, temp25_1) ? 1 : 0) << 0xa | (x87_r7_56 == temp25_1 ? 1 : 0) << 0xe
004452be        if ((eax_23:1.b & 1) != 0)
004452c8        long double st0_5 = normalize_vector(&vector_3)
004452cd        long double temp26_1 = fconvert.t(1.24000001f)
004452cd        st0_5 - temp26_1
004452d8        if ((((st0_5 < temp26_1 ? 1 : 0) << 8 | (is_unordered.t(st0_5, temp26_1) ? 1 : 0) << 0xa | (st0_5 == temp26_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
004452e0        add_subgoldy_score(player, 3, 0)
004452ef        play_voice_manager(0x751498, 0xa, 1, 0xffffffff)
004452fb        play_sound_effect(0x1b)
00445306        *(i_4 + player->game + 0x125e4b8) = 4
00445317        struct Game* game_2 = player->game
0044531d        int32_t ebx_2 = player->_pad_29ac[0x198c].d + 1
0044531e        player->_pad_29ac[0x198c] = ebx_2.b
0044531e        player->_pad_29ac[0x198d] = ebx_2:1.b
0044531e        player->_pad_29ac[0x198e] = ebx_2:2.b
0044531e        player->_pad_29ac[0x198f] = ebx_2:3.b
0044532b        if (game_2->__offset(0x40).d == 0)
00445339        int32_t var_88_3 = game_2->__offset(0x1b01e0).d
0044533a        int32_t var_8c_1 = ebx_2
00445346        sub_48b32c(game_2->__offset(0x35bb94).d + 0x2cc, "%i/%i")
0044534e        i_4 += 0x8c
00445475        struct Vec3 vector_1
00445367        void* i_5 = nullptr
00445475        while (i_5 s< 0x3a0)
00445369        struct Game* game_6 = player->game
0044536f        void* eax_27 = i_5 + game_6
0044537b        if (*(i_5 + game_6 + 0x356038) == 1)
0044538d        vector.x = fconvert.s(fconvert.t(*(eax_27 + 0x356010)) - fconvert.t(player->cached_camera_target_world.x))
004453a1        vector.y = fconvert.s(fconvert.t(*(eax_27 + 0x356014)) - fconvert.t(player->cached_camera_target_world.y))
004453b5        vector_1.x = vector.x
004453b9        vector_1.y = vector.y
004453bd        vector.z = fconvert.s(fconvert.t(*(eax_27 + 0x356018)) - fconvert.t(player->cached_camera_target_world.z))
004453c1        long double x87_r7_64 = fconvert.t(player->position.y)
004453c4        long double temp0_1 = fconvert.t(0.49000001f)
004453c4        x87_r7_64 - temp0_1
004453ce        vector_1.z = vector.z
004453d2        float eax_28
004453d2        eax_28.w = (x87_r7_64 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_64, temp0_1) ? 1 : 0) << 0xa | (x87_r7_64 == temp0_1 ? 1 : 0) << 0xe
004453d7        if ((eax_28:1.b & 1) == 0)
004453dd        long double x87_r7_65 = fconvert.t(vector.z)
004453e1        long double temp1_1 = fconvert.t(1f)
004453e1        x87_r7_65 - temp1_1
004453e7        eax_28.w = (x87_r7_65 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_65, temp1_1) ? 1 : 0) << 0xa | (x87_r7_65 == temp1_1 ? 1 : 0) << 0xe
004453ec        if ((eax_28:1.b & 1) != 0)
004453ee        long double x87_r7_66 = fconvert.t(vector.y)
004453f2        long double temp3_1 = fconvert.t(0f)
004453f2        x87_r7_66 - temp3_1
004453f8        long double x87_r7_67 = fconvert.t(vector.y)
004453fc        eax_28.w = (x87_r7_66 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_66, temp3_1) ? 1 : 0) << 0xa | (x87_r7_66 == temp3_1 ? 1 : 0) << 0xe | 0x3800
00445401        if ((eax_28:1.b & 1) != 0)
00445403        x87_r7_67 = fneg(x87_r7_67)
00445405        long double temp6_1 = fconvert.t(0.400000006f)
00445405        x87_r7_67 - temp6_1
0044540b        eax_28.w = (x87_r7_67 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_67, temp6_1) ? 1 : 0) << 0xa | (x87_r7_67 == temp6_1 ? 1 : 0) << 0xe
00445410        if ((eax_28:1.b & 1) != 0)
00445416        long double st0_6 = normalize_vector(&vector_1)
0044541b        long double temp11_1 = fconvert.t(0.980000019f)
0044541b        st0_6 - temp11_1
00445426        if ((((st0_6 < temp11_1 ? 1 : 0) << 8 | (is_unordered.t(st0_6, temp11_1) ? 1 : 0) << 0xa | (st0_6 == temp11_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
0044542f        play_sound_effect(0xe)
0044543a        *(i_5 + player->game + 0x356038) = 2
00445455        health_collect_particles(player, i_5 + player->game + 0x356000)
00445467        apply_damage_gauge_delta(&player->damage_gauge, -0.5f, 0)
0044546c        i_5 += 0x74
0044547b        struct Game* game_3 = player->game
00445487        if (game_3->__offset(0x355e30).d == 1)
00445499        vector.x = fconvert.s(fconvert.t(game_3->__offset(0x355e18).d) - fconvert.t(player->cached_camera_target_world.x))
004454ad        vector.y = fconvert.s(fconvert.t(game_3->__offset(0x355e1c).d) - fconvert.t(player->cached_camera_target_world.y))
004454c1        vector_1.x = vector.x
004454c5        vector_1.y = vector.y
004454c9        vector.z = fconvert.s(fconvert.t(game_3->__offset(0x355e20).d) - fconvert.t(player->cached_camera_target_world.z))
004454cd        long double x87_r7_75 = fconvert.t(player->position.y)
004454d0        long double temp2_1 = fconvert.t(0.49000001f)
004454d0        x87_r7_75 - temp2_1
004454da        vector_1.z = vector.z
004454de        float eax_31
004454de        eax_31.w = (x87_r7_75 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_75, temp2_1) ? 1 : 0) << 0xa | (x87_r7_75 == temp2_1 ? 1 : 0) << 0xe
004454e3        if ((eax_31:1.b & 1) == 0)
004454e5        long double x87_r7_76 = fconvert.t(vector.z)
004454e9        long double temp5_1 = fconvert.t(1f)
004454e9        x87_r7_76 - temp5_1
004454ef        eax_31.w = (x87_r7_76 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_76, temp5_1) ? 1 : 0) << 0xa | (x87_r7_76 == temp5_1 ? 1 : 0) << 0xe
004454f4        if ((eax_31:1.b & 1) != 0)
004454f6        long double x87_r7_77 = fconvert.t(vector.y)
004454fa        long double temp10_1 = fconvert.t(0f)
004454fa        x87_r7_77 - temp10_1
00445500        long double x87_r7_78 = fconvert.t(vector.y)
00445504        eax_31.w = (x87_r7_77 < temp10_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_77, temp10_1) ? 1 : 0) << 0xa | (x87_r7_77 == temp10_1 ? 1 : 0) << 0xe | 0x3800
00445509        if ((eax_31:1.b & 1) != 0)
0044550b        x87_r7_78 = fneg(x87_r7_78)
0044550d        long double temp16_1 = fconvert.t(0.400000006f)
0044550d        x87_r7_78 - temp16_1
00445513        eax_31.w = (x87_r7_78 < temp16_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_78, temp16_1) ? 1 : 0) << 0xa | (x87_r7_78 == temp16_1 ? 1 : 0) << 0xe
00445518        if ((eax_31:1.b & 1) != 0)
0044551e        long double st0_7 = normalize_vector(&vector_1)
00445523        long double temp19_1 = fconvert.t(0.980000019f)
00445523        st0_7 - temp19_1
0044552e        if ((((st0_7 < temp19_1 ? 1 : 0) << 8 | (is_unordered.t(st0_7, temp19_1) ? 1 : 0) << 0xa | (st0_7 == temp19_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00445538        player->game->__offset(0x355e30).d = 2
00445556        player->velocity.z = fconvert.s(fconvert.t(player->game->__offset(0x38).d) * fconvert.t(0.5f))
0044555c        struct Game* game_4 = player->game
00445568        if (game_4->__offset(0x355e9c).d == 1)
0044557a        vector.x = fconvert.s(fconvert.t(game_4->__offset(0x355e74).d) - fconvert.t(player->cached_camera_target_world.x))
0044558e        vector.y = fconvert.s(fconvert.t(game_4->__offset(0x355e78).d) - fconvert.t(player->cached_camera_target_world.y))
004455a2        vector_1.x = vector.x
004455a6        vector_1.y = vector.y
004455aa        vector.z = fconvert.s(fconvert.t(game_4->__offset(0x355e7c).d) - fconvert.t(player->cached_camera_target_world.z))
004455ae        long double x87_r7_88 = fconvert.t(player->position.y)
004455b1        long double temp4_1 = fconvert.t(0.49000001f)
004455b1        x87_r7_88 - temp4_1
004455bb        vector_1.z = vector.z
004455bf        float eax_34
004455bf        eax_34.w = (x87_r7_88 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_88, temp4_1) ? 1 : 0) << 0xa | (x87_r7_88 == temp4_1 ? 1 : 0) << 0xe
004455c4        if ((eax_34:1.b & 1) == 0)
004455c6        long double x87_r7_89 = fconvert.t(vector.z)
004455ca        long double temp9_1 = fconvert.t(1f)
004455ca        x87_r7_89 - temp9_1
004455d0        eax_34.w = (x87_r7_89 < temp9_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_89, temp9_1) ? 1 : 0) << 0xa | (x87_r7_89 == temp9_1 ? 1 : 0) << 0xe
004455d5        if ((eax_34:1.b & 1) != 0)
004455db        long double st0_8 = normalize_vector(&vector_1)
004455e0        long double temp15_1 = fconvert.t(3f)
004455e0        st0_8 - temp15_1
004455eb        if ((((st0_8 < temp15_1 ? 1 : 0) << 8 | (is_unordered.t(st0_8, temp15_1) ? 1 : 0) << 0xa | (st0_8 == temp15_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
004455f3        player->game->__offset(0x355e9c).d = 2
00445603        arm_jetpack_gauge(&player->jetpack_gauge)
00445608        void* i_6 = nullptr
00445829        while (i_6 s< 0x3f0)
00445614        struct Game* game_10 = player->game
00445621        void* eax_36 = i_6 + game_10
00445627        if (*(i_6 + game_10 + 0x35b80c) == 1)
00445639        vector_2.x = fconvert.s(fconvert.t(*(eax_36 + 0x35b7f4)) - fconvert.t(player->cached_camera_target_world.x))
00445649        vector_2.y = fconvert.s(fconvert.t(*(eax_36 + 0x35b7f8)) - fconvert.t(player->cached_camera_target_world.y))
00445653        long double x87_r7_96 = fconvert.t(*(eax_36 + 0x35b7fc)) - fconvert.t(player->cached_camera_target_world.z)
00445661        struct Vec3 vector_4
00445661        vector_4.x = vector_2.x
00445665        vector_4.y = vector_2.y
00445669        vector_2.z = fconvert.s(x87_r7_96)
0044566d        long double temp14_1 = fconvert.t(1f)
0044566d        x87_r7_96 - temp14_1
00445677        vector_4.z = vector_2.z
0044567e        float eax_37
0044567e        eax_37.w = (x87_r7_96 < temp14_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_96, temp14_1) ? 1 : 0) << 0xa | (x87_r7_96 == temp14_1 ? 1 : 0) << 0xe
00445683        if ((eax_37:1.b & 1) != 0)
0044568d        long double st0_9 = normalize_vector(&vector_4)
00445692        long double temp18_1 = fconvert.t(0.980000019f)
00445692        st0_9 - temp18_1
0044569d        if ((((st0_9 < temp18_1 ? 1 : 0) << 8 | (is_unordered.t(st0_9, temp18_1) ? 1 : 0) << 0xa | (st0_9 == temp18_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
004456a9        *(i_6 + player->game + 0x35b80c) = 2
004456b4        struct Game* eax_39
004456b4        eax_39.b = player->completion_handoff_active.b
004456bc        if (eax_39.b == 0)
004456be        struct Game* game_7 = player->game
004456c4        int32_t eax_40 = *(i_6 + game_7 + 0x35b814)
004456d2        if (eax_40 == 3 || eax_40 == 7)
004456ec        player->velocity.z = -0.100000001f
004456f2        play_sound_effect(0x2b)
004456dd        player->velocity.z = fconvert.s(fconvert.t(game_7->__offset(0x38).d) * fconvert.t(0.5f))
004456f7        struct Game* game_8 = player->game
004456fd        int32_t eax_41 = *(i_6 + game_8 + 0x35b814)
00445710        int32_t eax_44
00445710        if (eax_41 == 4 || eax_41 == 5)
004457ab        int32_t eax_45 = player->_pad_3f0[0x14].d
004457b4        if (eax_45 s< 0xa)
004457c0        if ((game_8->__offset(0x4c).b & 0x10) != 0 && game_8->__offset(0x40).d != 3)
004457c3        player->_pad_3f0[0x14] = (eax_45 + 1).b
004457c3        player->_pad_3f0[0x15] = (eax_45 + 1):1.b
004457c3        player->_pad_3f0[0x16] = (eax_45 + 1):2.b
004457c3        player->_pad_3f0[0x17] = (eax_45 + 1):3.b
004457d4        play_voice_manager(0x751498, 5, 1, 0xffffffff)
004457d9        int32_t movement_flag_selector_1 = player->movement_flag_selector
004457e2        if (movement_flag_selector_1 s< 8)
004457e5        player->movement_flag_selector = movement_flag_selector_1 + 1
004457ed        if (movement_flag_selector_1 == 8)
004457ef        player->movement_flag_selector = 7
004457fb        eax_44 = player->movement_flag_selector - 1
004457ff        if (eax_44 s> 6)
004457ff        goto label_445801
0044580d        play_sound_effect(eax_44 + 1)
00445818        add_subgoldy_score(player, 2, 0)
00445719        if (eax_41 == 8)
0044571b        int32_t movement_flag_selector = player->movement_flag_selector
00445724        if (movement_flag_selector s< 8)
00445727        player->movement_flag_selector = movement_flag_selector + 1
0044572f        if (movement_flag_selector == 8)
00445731        player->movement_flag_selector = 7
0044573d        eax_44 = player->movement_flag_selector - 1
00445741        if (eax_44 s<= 6)
0044580d        play_sound_effect(eax_44 + 1)
00445818        add_subgoldy_score(player, 2, 0)
00445801        label_445801:
0044580d        play_sound_effect(6 + 1)
00445818        add_subgoldy_score(player, 2, 0)
0044574f        if (eax_41 == 1)
00445757        add_subgoldy_score(player, 2, 0)
00445763        play_sound_effect(1)
00445775        if (eax_41 == 2 || eax_41 == 6)
00445781        add_subgoldy_score(player, 2, 0)
0044578d        play_sound_effect(0x2a)
00445792        int32_t ecx_53 = player->_pad_340[0x38].d
00445798        player->_pad_340[0x34] = ecx_53.b
00445798        player->_pad_340[0x35] = ecx_53:1.b
00445798        player->_pad_340[0x36] = ecx_53:2.b
00445798        player->_pad_340[0x37] = ecx_53:3.b
004457a4        initialize_nuke(&player->nuke)
0044581d        i_6 += 0x1f8
00445836        return
