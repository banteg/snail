/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: handle_subgoldy_collisions @ 0x444cf0 */

00444d1d        struct Vec3 vector
00444d1d        struct Vec3 vector_2
00444d1d        if (player->attachment_exit_pending == 0 && player->boost_one_tick == 0 && player->control_override_active == 0)
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
00444dae        if ((((x87_r7_6 < temp8_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_6, temp8_1) ? 1 : 0) << 0xa | (x87_r7_6 == temp8_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00444db4        long double st0_1 = normalize_vector(&vector_2)
00444db9        long double temp13_1 = fconvert.t(0.980000019f)
00444db9        st0_1 - temp13_1
00444dc4        if ((((st0_1 < temp13_1 ? 1 : 0) << 8 | (is_unordered.t(st0_1, temp13_1) ? 1 : 0) << 0xa | (st0_1 == temp13_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00444dc6        long double x87_r7_8 = fconvert.t(player->damage_retrigger_timer)
00444dcc        long double temp17_1 = fconvert.t(0f)
00444dcc        x87_r7_8 - temp17_1
00444dd7        if ((((x87_r7_8 < temp17_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_8, temp17_1) ? 1 : 0) << 0xa | (x87_r7_8 == temp17_1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
00444ddf        player->damage_retrigger_timer = player->damage_retrigger_step
00444df8        *(&player->game->salt_hazards.slots[0].velocity.z + i) = 0
00444e00        x87control = apply_damage_gauge_delta(&player->damage_gauge, 0.150000006f, 0)
00444e05        i += 0x98
00444e1e        int32_t i_1 = 0
00444ece        while (i_1 s< 0xdc0)
00444e26        void* eax_8 = player->game + i_1
00444e2e        if (*(eax_8 + 0x356b80) == 1)
00444e5e        long double x87_r7_14 = fconvert.t(*(eax_8 + 0x356b70)) - fconvert.t(player->cached_camera_target_world.z)
00444e68        vector.x = fconvert.s(fconvert.t(*(eax_8 + 0x356b68)) - fconvert.t(player->cached_camera_target_world.x))
00444e6c        vector.y = fconvert.s(fconvert.t(*(eax_8 + 0x356b6c)) - fconvert.t(player->cached_camera_target_world.y))
00444e74        long double temp7_1 = fconvert.t(1f)
00444e74        x87_r7_14 - temp7_1
00444e7e        vector.z = fconvert.s(x87_r7_14)
00444e87        if ((((x87_r7_14 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_14, temp7_1) ? 1 : 0) << 0xa | (x87_r7_14 == temp7_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00444e8d        long double st0_2 = normalize_vector(&vector)
00444e92        long double temp12_1 = fconvert.t(0.49000001f)
00444e92        st0_2 - temp12_1
00444e9d        if ((((st0_2 < temp12_1 ? 1 : 0) << 8 | (is_unordered.t(st0_2, temp12_1) ? 1 : 0) << 0xa | (st0_2 == temp12_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00444eac        *(&player->game->sub_lazers.slots[0].state + i_1) = 2
00444ebd        x87control = apply_damage_gauge_delta(&player->damage_gauge, 0.0199999996f, 0)
00444ec2        i_1 += 0xb0
00444eda        struct GarbageHazardSlot* i_2 = player->game->garbage_hazards.active_head
00444ee2        while (i_2 != 0)
00444eee        if (i_2->state == 1)
00444f15        long double x87_r7_21 = fconvert.t(i_2->world_position.z) - fconvert.t(player->cached_camera_target_world.z)
00444f1f        vector.x = fconvert.s(fconvert.t(i_2->world_position.x) - fconvert.t(player->cached_camera_target_world.x))
00444f23        vector.y = fconvert.s(fconvert.t(i_2->world_position.y) - fconvert.t(player->cached_camera_target_world.y))
00444f2b        long double temp20_1 = fconvert.t(1f)
00444f2b        x87_r7_21 - temp20_1
00444f35        vector.z = fconvert.s(x87_r7_21)
00444f3e        if ((((x87_r7_21 < temp20_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_21, temp20_1) ? 1 : 0) << 0xa | (x87_r7_21 == temp20_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00444f48        long double st0_3 = normalize_vector(&vector)
00444f4d        long double temp22_1 = fconvert.t(0.980000019f)
00444f4d        st0_3 - temp22_1
00444f58        if ((((st0_3 < temp22_1 ? 1 : 0) << 8 | (is_unordered.t(st0_3, temp22_1) ? 1 : 0) << 0xa | (st0_3 == temp22_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00444f64        if ((player->movement_flags.b & 0x80) == 0)
00444f7c        player->velocity.x = fconvert.s(fconvert.t(player->velocity.x) - fconvert.t(vector.x) * fconvert.t(player->velocity.z) * fconvert.t(0.180000007f))
00444f98        player->velocity.z = fconvert.s(fconvert.t(player->velocity.z) - fconvert.t(vector.z) * fconvert.t(player->velocity.z) * fconvert.t(0.100000001f))
00444fa3        i_2->state = 2
00444fa9        long double x87_r7_31 = fconvert.t(vector.x)
00444fad        long double temp24_1 = fconvert.t(0f)
00444fad        x87_r7_31 - temp24_1
00444fb8        if ((((x87_r7_31 < temp24_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_31, temp24_1) ? 1 : 0) << 0xa | (x87_r7_31 == temp24_1 ? 1 : 0) << 0xe):1.b & 1) == 0)
00444fc2        i_2->collision_side = 1
00444fba        i_2->collision_side = 2
00444fce        add_subgoldy_score(player, 0, 0)
0044500a        x87control = play_sound_effect(0x27 - ftol(apply_damage_gauge_delta(&player->damage_gauge, 0.0399999991f, 0), float.t(next_math_random_value()) * fconvert.t(-6.10351562e-05f)))
0044500f        i_2 = i_2->next_active
0044501d        void* i_3 = nullptr
0044524b        while (i_3 s< 0x760)
0044501f        struct SubgameRuntime* game_8 = player->game
00445025        int32_t ecx_14 = *(&game_8->slug_hazards.slots[0].state + i_3)
0044502c        void* eax_19 = i_3 + game_8
00445036        if (ecx_14 == 1 || ecx_14 == 4)
00445062        long double x87_r7_39 = fconvert.t(*(eax_19 + 0x356410)) - fconvert.t(player->cached_camera_target_world.z)
00445070        vector.x = fconvert.s(fconvert.t(*(eax_19 + 0x356408)) - fconvert.t(player->cached_camera_target_world.x))
00445074        vector.y = fconvert.s(fconvert.t(*(eax_19 + 0x35640c)) - fconvert.t(player->cached_camera_target_world.y))
0044507c        long double temp21_1 = fconvert.t(2f)
0044507c        x87_r7_39 - temp21_1
00445086        vector.z = fconvert.s(x87_r7_39)
0044508f        if ((((x87_r7_39 < temp21_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_39, temp21_1) ? 1 : 0) << 0xa | (x87_r7_39 == temp21_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00445099        long double st0_4 = normalize_vector(&vector)
004450a2        long double temp23_1 = fconvert.t(1.56750011f)
004450a2        st0_4 - temp23_1
004450a8        int16_t eax_23 = (st0_4 < temp23_1 ? 1 : 0) << 8 | (is_unordered.t(st0_4, temp23_1) ? 1 : 0) << 0xa | (st0_4 == temp23_1 ? 1 : 0) << 0xe
004450ad        if ((eax_23:1.b & 1) != 0)
004450b9        if ((player->movement_flags.b & 0x80) != 0)
0044523a        x87control = kill_slug_hazard(&player->game->slug_hazards + i_3)
004450bf        eax_23.b = player->control_override_active
004450c7        if (eax_23.b != 0)
0044520b        long double x87_r7_49 = fconvert.t(player->game->subgame_rate)
0044521e        player->velocity.z = fconvert.s(x87_r7_49 * x87_r7_49 * fconvert.t(0.00400000019f) * fconvert.t(-8f))
00445226        x87control = apply_damage_gauge_delta(&player->damage_gauge, 1f, 0)
004450cd        struct SubgameRuntime* game = player->game
004450d3        player->control_override_active = 1
004450da        player->follow_state.active = 0
004450e9        long double x87_r7_41 = fconvert.t(game->subgame_rate)
004450fe        player->velocity.x = 0
00445112        player->velocity.y = fconvert.s(x87_r7_41 * fconvert.t(0.200000003f))
0044511d        player->velocity.z = fconvert.s(x87_r7_41 * fconvert.t(-0.200000003f))
00445122        begin_post_follow_carryover(player)
0044512d        player->presentation.cutscene.state = CUT_SCENE_STATE_DEATH_PENDING
00445137        *(&player->game->slug_hazards.slots[0].player_encounter_latched + i_3) = 1
00445152        int32_t eax_27 = ftol(x87control, float.t(next_math_random_value()) * fconvert.t(-6.10351562e-05f))
0044516c        x87control = play_slug_voice(&player->game->slug_hazards + i_3, 0x22 - eax_27)
00445175        long double x87_r7_46 = fconvert.t(fconvert.s(st0_4)) * fconvert.t(0.5f)
0044517b        player->presentation.__offset(0x15c8).d = 0
004451ab        vector_2.x = fconvert.s(fconvert.t(fconvert.s(x87_r7_46 * fconvert.t(vector.x))) + fconvert.t(player->cached_camera_target_world.x))
004451bd        struct Vec3 position
004451bd        position.x = vector_2.x
004451c8        vector_2.y = fconvert.s(fconvert.t(fconvert.s(fconvert.t(vector.y) * x87_r7_46)) + fconvert.t(player->cached_camera_target_world.y))
004451d6        position.y = vector_2.y
004451e5        vector_2.z = fconvert.s(x87_r7_46 * fconvert.t(vector.z) + fconvert.t(player->cached_camera_target_world.z))
004451ed        position.z = vector_2.z
004451f1        firework_shoot(&player->firework, &position, player->player_slot, 0x5c, 0x50)
0044523f        i_3 += 0xec
00445251        void* i_4 = nullptr
0044535a        while (i_4 s< 0x1b58)
00445253        struct SubgameRuntime* game_4 = player->game
00445259        void* eax_31 = i_4 + game_4
00445265        if (*(&game_4->parcel_manager.slots[0].state + i_4) == 1)
00445277        vector_2.x = fconvert.s(fconvert.t(*(eax_31 + 0x125e490)) - fconvert.t(player->cached_camera_target_world.x))
0044528b        vector_2.y = fconvert.s(fconvert.t(*(eax_31 + 0x125e494)) - fconvert.t(player->cached_camera_target_world.y))
00445295        long double x87_r7_56 = fconvert.t(*(eax_31 + 0x125e498)) - fconvert.t(player->cached_camera_target_world.z)
0044529f        struct Vec3 vector_3
0044529f        vector_3.x = vector_2.x
004452a3        vector_3.y = vector_2.y
004452a7        vector_2.z = fconvert.s(x87_r7_56)
004452ab        long double temp25_1 = fconvert.t(1f)
004452ab        x87_r7_56 - temp25_1
004452b5        vector_3.z = vector_2.z
004452be        if ((((x87_r7_56 < temp25_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_56, temp25_1) ? 1 : 0) << 0xa | (x87_r7_56 == temp25_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
004452c8        long double st0_5 = normalize_vector(&vector_3)
004452cd        long double temp26_1 = fconvert.t(1.24000001f)
004452cd        st0_5 - temp26_1
004452d8        if ((((st0_5 < temp26_1 ? 1 : 0) << 8 | (is_unordered.t(st0_5, temp26_1) ? 1 : 0) << 0xa | (st0_5 == temp26_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
004452e0        add_subgoldy_score(player, 3, 0)
004452ef        play_voice_manager(0x751498, 0xa, 1, 0xffffffff)
004452fb        play_sound_effect(0x1b)
00445306        *(&player->game->parcel_manager.slots[0].state + i_4) = 4
00445317        struct SubgameRuntime* game_1 = player->game
0044531d        int32_t ebx_2 = player->parcels_collected + 1
0044531e        player->parcels_collected = ebx_2
0044532b        if (game_1->level_mode == 0)
00445339        int32_t parcel_count = game_1->level_definition.parcel_count
0044533a        int32_t var_8c_1 = ebx_2
00445346        sprintf(&game_1->lives_text_widget->text_buffer, "%i/%i")
0044534e        i_4 += 0x8c
00445475        struct Vec3 vector_1
00445367        void* i_5 = nullptr
00445475        while (i_5 s< 0x3a0)
00445369        struct SubgameRuntime* game_5 = player->game
0044536f        void* eax_38 = i_5 + game_5
0044537b        if (*(&game_5->health_pickups[0].state + i_5) == 1)
0044538d        vector.x = fconvert.s(fconvert.t(*(eax_38 + 0x356010)) - fconvert.t(player->cached_camera_target_world.x))
004453a1        vector.y = fconvert.s(fconvert.t(*(eax_38 + 0x356014)) - fconvert.t(player->cached_camera_target_world.y))
004453b5        vector_1.x = vector.x
004453b9        vector_1.y = vector.y
004453bd        vector.z = fconvert.s(fconvert.t(*(eax_38 + 0x356018)) - fconvert.t(player->cached_camera_target_world.z))
004453c1        long double x87_r7_64 = fconvert.t(player->body.transform.position.y)
004453c4        long double temp0_1 = fconvert.t(0.49000001f)
004453c4        x87_r7_64 - temp0_1
004453ce        vector_1.z = vector.z
004453d7        if ((((x87_r7_64 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_64, temp0_1) ? 1 : 0) << 0xa | (x87_r7_64 == temp0_1 ? 1 : 0) << 0xe):1.b & 1) == 0)
004453dd        long double x87_r7_65 = fconvert.t(vector.z)
004453e1        long double temp1_1 = fconvert.t(1f)
004453e1        x87_r7_65 - temp1_1
004453ec        if ((((x87_r7_65 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_65, temp1_1) ? 1 : 0) << 0xa | (x87_r7_65 == temp1_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
004453ee        long double x87_r7_66 = fconvert.t(vector.y)
004453f2        long double temp3_1 = fconvert.t(0f)
004453f2        x87_r7_66 - temp3_1
004453f8        long double x87_r7_67 = fconvert.t(vector.y)
00445401        if ((((x87_r7_66 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_66, temp3_1) ? 1 : 0) << 0xa | (x87_r7_66 == temp3_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) != 0)
00445403        x87_r7_67 = fneg(x87_r7_67)
00445405        long double temp6_1 = fconvert.t(0.400000006f)
00445405        x87_r7_67 - temp6_1
00445410        if ((((x87_r7_67 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_67, temp6_1) ? 1 : 0) << 0xa | (x87_r7_67 == temp6_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00445416        long double st0_6 = normalize_vector(&vector_1)
0044541b        long double temp11_1 = fconvert.t(0.980000019f)
0044541b        st0_6 - temp11_1
00445426        if ((((st0_6 < temp11_1 ? 1 : 0) << 8 | (is_unordered.t(st0_6, temp11_1) ? 1 : 0) << 0xa | (st0_6 == temp11_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
0044542f        play_sound_effect(0xe)
0044543a        *(&player->game->health_pickups[0].state + i_5) = 2
00445455        health_collect_particles(player, &player->game->health_pickups + i_5)
00445467        apply_damage_gauge_delta(&player->damage_gauge, -0.5f, 0)
0044546c        i_5 += 0x74
0044547b        struct SubgameRuntime* game_2 = player->game
00445487        if (game_2->speedup_pickup.state == TRACK_PICKUP_STATE_ACTIVE)
00445499        vector.x = fconvert.s(fconvert.t(game_2->speedup_pickup.world_position.x) - fconvert.t(player->cached_camera_target_world.x))
004454ad        vector.y = fconvert.s(fconvert.t(game_2->speedup_pickup.world_position.y) - fconvert.t(player->cached_camera_target_world.y))
004454c1        vector_1.x = vector.x
004454c5        vector_1.y = vector.y
004454c9        vector.z = fconvert.s(fconvert.t(game_2->speedup_pickup.world_position.z) - fconvert.t(player->cached_camera_target_world.z))
004454cd        long double x87_r7_75 = fconvert.t(player->body.transform.position.y)
004454d0        long double temp2_1 = fconvert.t(0.49000001f)
004454d0        x87_r7_75 - temp2_1
004454da        vector_1.z = vector.z
004454e3        if ((((x87_r7_75 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_75, temp2_1) ? 1 : 0) << 0xa | (x87_r7_75 == temp2_1 ? 1 : 0) << 0xe):1.b & 1) == 0)
004454e5        long double x87_r7_76 = fconvert.t(vector.z)
004454e9        long double temp5_1 = fconvert.t(1f)
004454e9        x87_r7_76 - temp5_1
004454f4        if ((((x87_r7_76 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_76, temp5_1) ? 1 : 0) << 0xa | (x87_r7_76 == temp5_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
004454f6        long double x87_r7_77 = fconvert.t(vector.y)
004454fa        long double temp10_1 = fconvert.t(0f)
004454fa        x87_r7_77 - temp10_1
00445500        long double x87_r7_78 = fconvert.t(vector.y)
00445509        if ((((x87_r7_77 < temp10_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_77, temp10_1) ? 1 : 0) << 0xa | (x87_r7_77 == temp10_1 ? 1 : 0) << 0xe | 0x3800):1.b & 1) != 0)
0044550b        x87_r7_78 = fneg(x87_r7_78)
0044550d        long double temp16_1 = fconvert.t(0.400000006f)
0044550d        x87_r7_78 - temp16_1
00445518        if ((((x87_r7_78 < temp16_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_78, temp16_1) ? 1 : 0) << 0xa | (x87_r7_78 == temp16_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
0044551e        long double st0_7 = normalize_vector(&vector_1)
00445523        long double temp19_1 = fconvert.t(0.980000019f)
00445523        st0_7 - temp19_1
0044552e        if ((((st0_7 < temp19_1 ? 1 : 0) << 8 | (is_unordered.t(st0_7, temp19_1) ? 1 : 0) << 0xa | (st0_7 == temp19_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00445538        player->game->speedup_pickup.state = TRACK_PICKUP_STATE_TEARDOWN_PENDING
00445556        player->velocity.z = fconvert.s(fconvert.t(player->game->subgame_rate) * fconvert.t(0.5f))
0044555c        struct SubgameRuntime* game_3 = player->game
00445568        if (game_3->jetpack_pickup.state == TRACK_PICKUP_STATE_ACTIVE)
0044557a        vector.x = fconvert.s(fconvert.t(game_3->jetpack_pickup.world_position.x) - fconvert.t(player->cached_camera_target_world.x))
0044558e        vector.y = fconvert.s(fconvert.t(game_3->jetpack_pickup.world_position.y) - fconvert.t(player->cached_camera_target_world.y))
004455a2        vector_1.x = vector.x
004455a6        vector_1.y = vector.y
004455aa        vector.z = fconvert.s(fconvert.t(game_3->jetpack_pickup.world_position.z) - fconvert.t(player->cached_camera_target_world.z))
004455ae        long double x87_r7_88 = fconvert.t(player->body.transform.position.y)
004455b1        long double temp4_1 = fconvert.t(0.49000001f)
004455b1        x87_r7_88 - temp4_1
004455bb        vector_1.z = vector.z
004455c4        if ((((x87_r7_88 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_88, temp4_1) ? 1 : 0) << 0xa | (x87_r7_88 == temp4_1 ? 1 : 0) << 0xe):1.b & 1) == 0)
004455c6        long double x87_r7_89 = fconvert.t(vector.z)
004455ca        long double temp9_1 = fconvert.t(1f)
004455ca        x87_r7_89 - temp9_1
004455d5        if ((((x87_r7_89 < temp9_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_89, temp9_1) ? 1 : 0) << 0xa | (x87_r7_89 == temp9_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
004455db        long double st0_8 = normalize_vector(&vector_1)
004455e0        long double temp15_1 = fconvert.t(3f)
004455e0        st0_8 - temp15_1
004455eb        if ((((st0_8 < temp15_1 ? 1 : 0) << 8 | (is_unordered.t(st0_8, temp15_1) ? 1 : 0) << 0xa | (st0_8 == temp15_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
004455f3        player->game->jetpack_pickup.state = TRACK_PICKUP_STATE_TEARDOWN_PENDING
00445603        arm_jetpack_gauge(&player->sub_hover)
00445829        void* x
00445608        void* i_6 = nullptr
00445829        while (i_6 s< 0x3f0)
00445614        struct SubgameRuntime* game_9 = player->game
00445621        x = i_6 + game_9
00445627        if (*(&game_9->ring_effects.slots[0].state + i_6) == 1)
00445639        vector_2.x = fconvert.s(fconvert.t(*(x + 0x35b7f4)) - fconvert.t(player->cached_camera_target_world.x))
00445649        vector_2.y = fconvert.s(fconvert.t(*(x + 0x35b7f8)) - fconvert.t(player->cached_camera_target_world.y))
00445653        long double x87_r7_96 = fconvert.t(*(x + 0x35b7fc)) - fconvert.t(player->cached_camera_target_world.z)
00445659        x = vector_2.x
00445661        struct Vec3 vector_4
00445661        vector_4.x = x
00445665        vector_4.y = vector_2.y
00445669        vector_2.z = fconvert.s(x87_r7_96)
0044566d        long double temp14_1 = fconvert.t(1f)
0044566d        x87_r7_96 - temp14_1
00445677        vector_4.z = vector_2.z
0044567e        x.w = (x87_r7_96 < temp14_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_96, temp14_1) ? 1 : 0) << 0xa | (x87_r7_96 == temp14_1 ? 1 : 0) << 0xe
00445683        if ((x:1.b & 1) != 0)
0044568d        long double st0_9
0044568d        st0_9, x = normalize_vector(&vector_4)
00445692        long double temp18_1 = fconvert.t(0.980000019f)
00445692        st0_9 - temp18_1
00445698        x.w = (st0_9 < temp18_1 ? 1 : 0) << 8 | (is_unordered.t(st0_9, temp18_1) ? 1 : 0) << 0xa | (st0_9 == temp18_1 ? 1 : 0) << 0xe
0044569d        if ((x:1.b & 1) != 0)
004456a9        *(&player->game->ring_effects.slots[0].state + i_6) = 2
004456bc        if (player->completion_handoff_active == 0)
004456be        struct SubgameRuntime* game_6 = player->game
004456c4        int32_t eax_55 = *(&game_6->ring_effects.slots[0].kind + i_6)
004456d2        if (eax_55 == 3 || eax_55 == 7)
004456ec        player->velocity.z = -0.100000001f
004456f2        play_sound_effect(0x2b)
004456dd        player->velocity.z = fconvert.s(fconvert.t(game_6->subgame_rate) * fconvert.t(0.5f))
004456f7        struct SubgameRuntime* game_7 = player->game
004456fd        x = *(&game_7->ring_effects.slots[0].kind + i_6)
00445710        int32_t eax_58
00445710        if (x == 4 || x == 5)
004457ab        int32_t lives = player->lives
004457b4        if (lives s< 0xa)
004457c0        if ((game_7->runtime_flags.b & 0x10) != 0 && game_7->level_mode != 3)
004457c3        player->lives = lives + 1
004457d4        play_voice_manager(0x751498, 5, 1, 0xffffffff)
004457d9        int32_t movement_flag_selector_1 = player->movement_flag_selector
004457e2        if (movement_flag_selector_1 s< 8)
004457e5        player->movement_flag_selector = movement_flag_selector_1 + 1
004457ed        if (movement_flag_selector_1 == 8)
004457ef        player->movement_flag_selector = 7
004457fb        eax_58 = player->movement_flag_selector - 1
004457ff        if (eax_58 s> 6)
004457ff        goto label_445801
0044580d        play_sound_effect(eax_58 + 1)
00445818        x = add_subgoldy_score(player, 2, 0)
00445719        if (x == 8)
0044571b        int32_t movement_flag_selector = player->movement_flag_selector
00445724        if (movement_flag_selector s< 8)
00445727        player->movement_flag_selector = movement_flag_selector + 1
0044572f        if (movement_flag_selector == 8)
00445731        player->movement_flag_selector = 7
0044573d        eax_58 = player->movement_flag_selector - 1
00445741        if (eax_58 s<= 6)
0044580d        play_sound_effect(eax_58 + 1)
00445818        x = add_subgoldy_score(player, 2, 0)
00445801        label_445801:
0044580d        play_sound_effect(6 + 1)
00445818        x = add_subgoldy_score(player, 2, 0)
0044574f        if (x == 1)
00445757        add_subgoldy_score(player, 2, 0)
00445763        x = play_sound_effect(1)
00445775        if (x == 2 || x == 6)
00445781        add_subgoldy_score(player, 2, 0)
0044578d        play_sound_effect(0x2a)
00445798        player->nuke_effect_progress = player->nuke_effect_progress_step
004457a4        x = initialize_nuke(&player->nuke)
0044581d        i_6 += 0x1f8
00445836        return x
