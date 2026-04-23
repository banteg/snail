/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: handle_subgoldy_collisions @ 0x444cf0 */

00444cf3        int32_t ebx
00444cf3        int32_t var_78 = ebx
00444cf4        int32_t ebp
00444cf4        int32_t var_7c = ebp
00444cf5        int32_t esi
00444cf5        int32_t var_80 = esi
00444cf8        int32_t edi
00444cf8        int32_t var_84 = edi
00444cf8        int32_t* esp_1 = &var_84
00444d1d        int16_t top
00444d1d        if (player->attachment_exit_pending == 0 && player->_pad_41c == 0 && player->control_override_active == 0)
00444d2d        int16_t x87control
00444d2d        if ((0x80 & player->movement_flags.b) == 0)
00444d33        int32_t i = 0
00444e11        while (i s< 0x17c0)
00444d40        void* eax_2 = &player->game->_pad_00[i]
00444d55        if (*(eax_2 + 0x357940) == 1 && *(eax_2 + 0x357954) == 1)
00444d67        esp_1[0xc] = fconvert.s(fconvert.t(*(eax_2 + 0x357928)) - fconvert.t(player->cached_camera_target_world.x))
00444d77        int32_t ecx = esp_1[0xc]
00444d7b        esp_1[0xd] = fconvert.s(fconvert.t(*(eax_2 + 0x35792c)) - fconvert.t(player->cached_camera_target_world.y))
00444d85        long double x87_r7_6 = fconvert.t(*(eax_2 + 0x357930)) - fconvert.t(player->cached_camera_target_world.z)
00444d8b        int32_t edx_1 = esp_1[0xd]
00444d8f        esp_1[0x12] = ecx
00444d93        esp_1[0x13] = edx_1
00444d97        esp_1[0xe] = fconvert.s(x87_r7_6)
00444d9b        long double temp8_1 = fconvert.t(1f)
00444d9b        x87_r7_6 - temp8_1
00444d9b        top = 0
00444da5        esp_1[0x14] = esp_1[0xe]
00444da9        int32_t eax_3
00444da9        eax_3.w = (x87_r7_6 < temp8_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_6, temp8_1) ? 1 : 0) << 0xa | (x87_r7_6 == temp8_1 ? 1 : 0) << 0xe
00444dae        if ((eax_3:1.b & 1) != 0)
00444db4        long double st0_1 = normalize_vector(&esp_1[0x12])
00444db9        long double temp13_1 = fconvert.t(0.980000019f)
00444db9        st0_1 - temp13_1
00444db9        top = 0
00444dc4        if ((((st0_1 < temp13_1 ? 1 : 0) << 8 | (is_unordered.t(st0_1, temp13_1) ? 1 : 0) << 0xa | (st0_1 == temp13_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00444dc6        long double x87_r7_8 = fconvert.t(player->damage_retrigger_timer)
00444dcc        long double temp17_1 = fconvert.t(0f)
00444dcc        x87_r7_8 - temp17_1
00444dcc        top = 0
00444dd7        if ((((x87_r7_8 < temp17_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_8, temp17_1) ? 1 : 0) << 0xa | (x87_r7_8 == temp17_1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
00444ddf        player->damage_retrigger_timer = player->damage_retrigger_step
00444de5        struct Game* game_3 = player->game
00444deb        *(esp_1 - 4) = 0
00444ded        *(esp_1 - 8) = 0x3e19999a
00444df8        *(&game_3->salt_pool[0].armed_substate + i) = 0
00444e00        x87control = apply_damage_gauge_delta(&player->damage_gauge)
00444e00        esp_1 -= 4
00444e05        i += 0x98
00444e1e        int32_t i_1 = 0
00444ece        while (i_1 s< 0xdc0)
00444e26        void* eax_6 = &player->game->_pad_00[i_1]
00444e2e        if (*(eax_6 + 0x356b80) == 1)
00444e40        esp_1[0xc] = fconvert.s(fconvert.t(*(eax_6 + 0x356b68)) - fconvert.t(player->cached_camera_target_world.x))
00444e50        int32_t ecx_4 = esp_1[0xc]
00444e54        esp_1[0xd] = fconvert.s(fconvert.t(*(eax_6 + 0x356b6c)) - fconvert.t(player->cached_camera_target_world.y))
00444e5e        long double x87_r7_14 = fconvert.t(*(eax_6 + 0x356b70)) - fconvert.t(player->cached_camera_target_world.z)
00444e64        int32_t edx_2 = esp_1[0xd]
00444e68        esp_1[6] = ecx_4
00444e6c        esp_1[7] = edx_2
00444e70        esp_1[0xe] = fconvert.s(x87_r7_14)
00444e74        long double temp7_1 = fconvert.t(1f)
00444e74        x87_r7_14 - temp7_1
00444e74        top = 0
00444e7e        esp_1[8] = esp_1[0xe]
00444e82        int32_t eax_7
00444e82        eax_7.w = (x87_r7_14 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_14, temp7_1) ? 1 : 0) << 0xa | (x87_r7_14 == temp7_1 ? 1 : 0) << 0xe
00444e87        if ((eax_7:1.b & 1) != 0)
00444e8d        long double st0_2 = normalize_vector(&esp_1[6])
00444e92        long double temp12_1 = fconvert.t(0.49000001f)
00444e92        st0_2 - temp12_1
00444e92        top = 0
00444e9d        if ((((st0_2 < temp12_1 ? 1 : 0) << 8 | (is_unordered.t(st0_2, temp12_1) ? 1 : 0) << 0xa | (st0_2 == temp12_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00444e9f        struct Game* game_1 = player->game
00444ea5        *(esp_1 - 4) = 0
00444ea7        *(esp_1 - 8) = 0x3ca3d70a
00444eac        *(&game_1->sub_lazer_pool[0].state + i_1) = 2
00444ebd        x87control = apply_damage_gauge_delta(&player->damage_gauge)
00444ebd        esp_1 -= 4
00444ec2        i_1 += 0xb0
00444eda        void* i_2 = player->game->__offset(0x359140).d
00444ee2        while (i_2 != 0)
00444eee        if (*(i_2 + 0x84) == 1)
00444efd        esp_1[0xc] = fconvert.s(fconvert.t(*(i_2 + 0x68)) - fconvert.t(player->cached_camera_target_world.x))
00444f0a        int32_t eax_9 = esp_1[0xc]
00444f0e        esp_1[0xd] = fconvert.s(fconvert.t(*(i_2 + 0x6c)) - fconvert.t(player->cached_camera_target_world.y))
00444f15        long double x87_r7_21 = fconvert.t(*(i_2 + 0x70)) - fconvert.t(player->cached_camera_target_world.z)
00444f1b        int32_t ecx_7 = esp_1[0xd]
00444f1f        esp_1[6] = eax_9
00444f23        esp_1[7] = ecx_7
00444f27        esp_1[0xe] = fconvert.s(x87_r7_21)
00444f2b        long double temp20_1 = fconvert.t(1f)
00444f2b        x87_r7_21 - temp20_1
00444f2b        top = 0
00444f35        esp_1[8] = esp_1[0xe]
00444f39        eax_9.w = (x87_r7_21 < temp20_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_21, temp20_1) ? 1 : 0) << 0xa | (x87_r7_21 == temp20_1 ? 1 : 0) << 0xe
00444f3e        if ((eax_9:1.b & 1) != 0)
00444f48        long double st0_3 = normalize_vector(&esp_1[6])
00444f4d        long double temp22_1 = fconvert.t(0.980000019f)
00444f4d        st0_3 - temp22_1
00444f4d        top = 0
00444f58        if ((((st0_3 < temp22_1 ? 1 : 0) << 8 | (is_unordered.t(st0_3, temp22_1) ? 1 : 0) << 0xa | (st0_3 == temp22_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00444f64        if ((player->movement_flags.b & 0x80) == 0)
00444f7c        player->velocity.x = fconvert.s(fconvert.t(player->velocity.x) - fconvert.t(esp_1[6]) * fconvert.t(player->velocity.z) * fconvert.t(0.180000007f))
00444f98        player->velocity.z = fconvert.s(fconvert.t(player->velocity.z) - fconvert.t(esp_1[8]) * fconvert.t(player->velocity.z) * fconvert.t(0.100000001f))
00444fa3        *(i_2 + 0x84) = 2
00444fa9        long double x87_r7_31 = fconvert.t(esp_1[6])
00444fad        long double temp24_1 = fconvert.t(0f)
00444fad        x87_r7_31 - temp24_1
00444fb8        if ((((x87_r7_31 < temp24_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_31, temp24_1) ? 1 : 0) << 0xa | (x87_r7_31 == temp24_1 ? 1 : 0) << 0xe):1.b & 1) == 0)
00444fc2        *(i_2 + 0x88) = 1
00444fba        *(i_2 + 0x88) = 2
00444fc8        *(esp_1 - 4) = 0
00444fca        *(esp_1 - 8) = 0
00444fce        add_subgoldy_score(player)
00444fd3        *(esp_1 - 4) = 0
00444fd5        *(esp_1 - 8) = 0x3d23d70a
00444fe0        int16_t x87control_1 = apply_damage_gauge_delta(&player->damage_gauge)
00444fea        esp_1[3] = next_math_random_value()
00444ff8        top = 0
00445004        *(esp_1 - 8) = 0x27 - __ftol(x87control_1, float.t(esp_1[3]) * fconvert.t(-6.10351562e-05f))
0044500a        x87control = play_sound_effect()
0044500a        esp_1 -= 4
0044500f        i_2 = *(i_2 + 0x80)
0044501d        int32_t i_3 = 0
0044524b        while (i_3 s< 0x760)
00445025        int32_t ecx_13 = *(i_3 + player->game + 0x356420)
00445036        if (ecx_13 == 1 || ecx_13 == 4)
0044503c        unimplemented  {fld st0, dword [eax+0x356408]}
00445042        unimplemented  {fsub st0, dword [esi+0x2964]}
00445048        esp_1[0xc] = fconvert.s(unimplemented  {fstp dword [esp+0x30], st0})
00445048        unimplemented  {fstp dword [esp+0x30], st0}
0044504c        unimplemented  {fld st0, dword [eax+0x35640c]}
00445052        unimplemented  {fsub st0, dword [esi+0x2968]}
00445058        esp_1[0xd] = fconvert.s(unimplemented  {fstp dword [esp+0x34], st0})
00445058        unimplemented  {fstp dword [esp+0x34], st0}
0044505c        unimplemented  {fld st0, dword [eax+0x356410]}
00445062        unimplemented  {fsub st0, dword [esi+0x296c]}
0044506c        int32_t ecx_14 = esp_1[0xd]
00445070        esp_1[6] = esp_1[0xc]
00445074        esp_1[7] = ecx_14
00445078        esp_1[0xe] = fconvert.s(unimplemented  {fst dword [esp+0x38], st0})
0044507c        long double temp21_1 = fconvert.t(2f)
0044507c        unimplemented  {fcomp st0, dword [0x4974a4]} f- temp21_1
0044507c        bool c0_9 = unimplemented  {fcomp st0, dword [0x4974a4]} f< temp21_1
0044507c        bool c2_9 = is_unordered.t(unimplemented  {fcomp st0, dword [0x4974a4]}, temp21_1)
0044507c        bool c3_9 = unimplemented  {fcomp st0, dword [0x4974a4]} f== temp21_1
0044507c        unimplemented  {fcomp st0, dword [0x4974a4]}
00445086        esp_1[8] = esp_1[0xe]
0044508a        int32_t eax_13
0044508a        eax_13.w = (c0_9 ? 1 : 0) << 8 | (c2_9 ? 1 : 0) << 0xa | (c3_9 ? 1 : 0) << 0xe | (top & 7) << 0xb
0044508f        if ((eax_13:1.b & 1) != 0)
00445099        long double st0_4 = normalize_vector(&esp_1[6])
00445099        unimplemented  {call 0x44cca0}
0044509e        esp_1[4] = fconvert.s(unimplemented  {fst dword [esp+0x10], st0})
004450a2        long double temp23_1 = fconvert.t(1.56750011f)
004450a2        unimplemented  {fcomp st0, dword [0x497694]} f- temp23_1
004450a2        bool c0_10 = unimplemented  {fcomp st0, dword [0x497694]} f< temp23_1
004450a2        bool c2_10 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497694]}, temp23_1)
004450a2        bool c3_10 = unimplemented  {fcomp st0, dword [0x497694]} f== temp23_1
004450a2        unimplemented  {fcomp st0, dword [0x497694]}
004450ad        if ((((c0_10 ? 1 : 0) << 8 | (c2_10 ? 1 : 0) << 0xa | (c3_10 ? 1 : 0) << 0xe | (top & 7) << 0xb):1.b & 1) != 0)
004450b9        if ((player->movement_flags.b & 0x80) != 0)
0044523a        x87control = kill_slug_hazard(&player->game->_pad_00[i_3 + 0x3563a0])
004450bf        int16_t eax_14
004450bf        eax_14.b = player->control_override_active
004450c7        if (eax_14.b != 0)
004451fe        *(esp_1 - 4) = 0
00445200        *(esp_1 - 8) = 0x3f800000
0044520b        unimplemented  {fld st0, dword [edx+0x38]}
0044520e        unimplemented  {fld st0, st0}
00445210        unimplemented  {fmul st0, st1}
00445212        unimplemented  {fmul st0, dword [0x4973bc]}
00445218        unimplemented  {fmul st0, dword [0x497690]}
0044521e        player->velocity.z = fconvert.s(unimplemented  {fstp dword [esi+0x418], st0})
0044521e        unimplemented  {fstp dword [esi+0x418], st0}
00445224        unimplemented  {fstp st0, st0}
00445224        unimplemented  {fstp st0, st0}
00445226        x87control = apply_damage_gauge_delta(&player->damage_gauge)
00445226        esp_1 -= 4
004450d3        player->control_override_active = 1
004450da        player->follow_state.active = 0
004450e1        esp_1[0xf] = 0
004450e9        unimplemented  {fld st0, dword [eax+0x38]}
004450ec        unimplemented  {fld st0, st0}
004450ee        unimplemented  {fmul st0, dword [0x497270]}
004450fe        player->velocity.x = esp_1[0xf]
00445104        esp_1[0x10] = fconvert.s(unimplemented  {fstp dword [esp+0x40], st0})
00445104        unimplemented  {fstp dword [esp+0x40], st0}
0044510c        unimplemented  {fmul st0, dword [0x4974b8]}
00445112        player->velocity.y = esp_1[0x10]
00445115        esp_1[0x11] = fconvert.s(unimplemented  {fstp dword [esp+0x44], st0})
00445115        unimplemented  {fstp dword [esp+0x44], st0}
0044511d        player->velocity.z = esp_1[0x11]
00445122        begin_post_follow_carryover(player)
0044512d        player->presentation.cutscene_ai.state = 0xa
00445137        player->game->_pad_00[i_3 + 0x356479] = 1
00445144        esp_1[5] = next_math_random_value()
00445148        unimplemented  {fild st0, dword [esp+0x14]}
0044514c        unimplemented  {fmul st0, dword [0x497628]}
00445152        int32_t eax_18 = __ftol(x87control, st0_4)
00445157        struct Game* game_4 = player->game
00445164        *(esp_1 - 4) = 0x22 - eax_18
0044516c        x87control = play_slug_voice(&game_4->_pad_00[i_3 + 0x3563a0])
00445171        unimplemented  {fld st0, dword [esp+0x10]}
00445175        unimplemented  {fmul st0, dword [0x497228]}
0044517b        player->presentation.wobble.lift_phase_step = 0f
00445185        *(esp_1 - 4) = 0x50
00445187        *(esp_1 - 8) = 0x5c
00445189        unimplemented  {fld st0, st0}
0044518b        unimplemented  {fmul st0, dword [esp+0x20]}
0044518f        esp_1[0x15] = fconvert.s(unimplemented  {fstp dword [esp+0x5c], st0})
0044518f        unimplemented  {fstp dword [esp+0x5c], st0}
00445193        unimplemented  {fld st0, dword [esp+0x24]}
00445197        unimplemented  {fmul st0, st1}
00445199        esp_1[0x16] = fconvert.s(unimplemented  {fstp dword [esp+0x60], st0})
00445199        unimplemented  {fstp dword [esp+0x60], st0}
0044519d        unimplemented  {fmul st0, dword [esp+0x28]}
004451a1        unimplemented  {fld st0, dword [esp+0x5c]}
004451a5        unimplemented  {fadd dword [esi+0x2964]}
004451ab        esp_1[0x12] = fconvert.s(unimplemented  {fstp dword [esp+0x50], st0})
004451ab        unimplemented  {fstp dword [esp+0x50], st0}
004451af        unimplemented  {fld st0, dword [esp+0x60]}
004451b3        unimplemented  {fadd dword [esi+0x2968]}
004451bd        esp_1[0x18] = esp_1[0x12]
004451c7        *(esp_1 - 0xc) = player->player_slot
004451c8        esp_1[0x13] = fconvert.s(unimplemented  {fstp dword [esp+0x58], st0})
004451c8        unimplemented  {fstp dword [esp+0x58], st0}
004451d0        unimplemented  {fadd dword [esi+0x296c]}
004451d6        esp_1[0x19] = esp_1[0x13]
004451de        *(esp_1 - 0x10) = &esp_1[0x18]
004451e5        esp_1[0x14] = fconvert.s(unimplemented  {fstp dword [esp+0x60], st0})
004451e5        unimplemented  {fstp dword [esp+0x60], st0}
004451ed        esp_1[0x1a] = esp_1[0x14]
004451f1        firework_shoot()
004451f1        top -= 1
0044523f        i_3 += 0xec
00445251        int32_t i_4 = 0
0044535a        while (i_4 s< 0x1b58)
00445265        if (*(&player->game->parcel_pool[0].state + i_4) == 1)
0044526b        unimplemented  {fld st0, dword [eax+0x125e490]}
00445271        unimplemented  {fsub st0, dword [esi+0x2964]}
00445277        esp_1[0x12] = fconvert.s(unimplemented  {fstp dword [esp+0x48], st0})
00445277        unimplemented  {fstp dword [esp+0x48], st0}
0044527b        unimplemented  {fld st0, dword [eax+0x125e494]}
00445281        unimplemented  {fsub st0, dword [esi+0x2968]}
00445287        int32_t edx_10 = esp_1[0x12]
0044528b        esp_1[0x13] = fconvert.s(unimplemented  {fstp dword [esp+0x4c], st0})
0044528b        unimplemented  {fstp dword [esp+0x4c], st0}
0044528f        unimplemented  {fld st0, dword [eax+0x125e498]}
00445295        unimplemented  {fsub st0, dword [esi+0x296c]}
0044529b        int32_t eax_22 = esp_1[0x13]
0044529f        esp_1[0x1b] = edx_10
004452a3        esp_1[0x1c] = eax_22
004452a7        esp_1[0x14] = fconvert.s(unimplemented  {fst dword [esp+0x50], st0})
004452ab        long double temp25_1 = fconvert.t(1f)
004452ab        unimplemented  {fcomp st0, dword [0x497220]} f- temp25_1
004452ab        bool c0_11 = unimplemented  {fcomp st0, dword [0x497220]} f< temp25_1
004452ab        bool c2_11 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497220]}, temp25_1)
004452ab        bool c3_11 = unimplemented  {fcomp st0, dword [0x497220]} f== temp25_1
004452ab        unimplemented  {fcomp st0, dword [0x497220]}
004452b5        esp_1[0x1d] = esp_1[0x14]
004452b9        eax_22.w = (c0_11 ? 1 : 0) << 8 | (c2_11 ? 1 : 0) << 0xa | (c3_11 ? 1 : 0) << 0xe | (top & 7) << 0xb
004452be        if ((eax_22:1.b & 1) != 0)
004452c8        normalize_vector(&esp_1[0x1b])
004452c8        unimplemented  {call 0x44cca0}
004452cd        long double temp26_1 = fconvert.t(1.24000001f)
004452cd        unimplemented  {fcomp st0, dword [0x49768c]} f- temp26_1
004452cd        bool c0_12 = unimplemented  {fcomp st0, dword [0x49768c]} f< temp26_1
004452cd        bool c2_12 = is_unordered.t(unimplemented  {fcomp st0, dword [0x49768c]}, temp26_1)
004452cd        bool c3_12 = unimplemented  {fcomp st0, dword [0x49768c]} f== temp26_1
004452cd        unimplemented  {fcomp st0, dword [0x49768c]}
004452d8        if ((((c0_12 ? 1 : 0) << 8 | (c2_12 ? 1 : 0) << 0xa | (c3_12 ? 1 : 0) << 0xe | (top & 7) << 0xb):1.b & 1) != 0)
004452da        *(esp_1 - 4) = 0
004452dc        *(esp_1 - 8) = 3
004452e0        add_subgoldy_score(player)
004452e5        *(esp_1 - 4) = 0xffffffff
004452e7        *(esp_1 - 8) = 1
004452e8        *(esp_1 - 0xc) = 0xa
004452ef        play_voice_manager(0x751498)
004452f4        *(esp_1 - 4) = 0x1b
004452fb        play_sound_effect()
00445306        *(&player->game->parcel_pool[0].state + i_4) = 4
00445317        struct Game* game = player->game
0044531d        int32_t ebx_2 = player->presentation.cutscene_ai._pad_59[3].d + 1
0044531e        player->presentation.cutscene_ai._pad_59[3] = ebx_2.b
0044531e        player->presentation.cutscene_ai._pad_59[4] = ebx_2:1.b
0044531e        player->presentation.cutscene_ai._pad_59[5] = ebx_2:2.b
0044531e        player->presentation.cutscene_ai._pad_59[6] = ebx_2:3.b
0044532b        if (game->level_mode == 0)
00445333        int32_t eax_24 = game->__offset(0x35bb94).d
00445339        *(esp_1 - 4) = game->__offset(0x1b01e0).d
0044533a        *(esp_1 - 8) = ebx_2
00445340        *(esp_1 - 0xc) = "%i/%i"
00445345        *(esp_1 - 0x10) = eax_24 + 0x2cc
00445346        sub_48b32c()
0044534e        i_4 += 0x8c
00445367        int32_t i_5 = 0
00445475        while (i_5 s< 0x3a0)
0044537b        if (*(i_5 + player->game + 0x356038) == 1)
00445381        unimplemented  {fld st0, dword [eax+0x356010]}
00445387        unimplemented  {fsub st0, dword [esi+0x2964]}
0044538d        esp_1[6] = fconvert.s(unimplemented  {fstp dword [esp+0x18], st0})
0044538d        unimplemented  {fstp dword [esp+0x18], st0}
00445391        unimplemented  {fld st0, dword [eax+0x356014]}
00445397        unimplemented  {fsub st0, dword [esi+0x2968]}
0044539d        int32_t edx_14 = esp_1[6]
004453a1        esp_1[7] = fconvert.s(unimplemented  {fstp dword [esp+0x1c], st0})
004453a1        unimplemented  {fstp dword [esp+0x1c], st0}
004453a5        unimplemented  {fld st0, dword [eax+0x356018]}
004453ab        unimplemented  {fsub st0, dword [esi+0x296c]}
004453b1        int32_t eax_26 = esp_1[7]
004453b5        esp_1[9] = edx_14
004453b9        esp_1[0xa] = eax_26
004453bd        esp_1[8] = fconvert.s(unimplemented  {fstp dword [esp+0x20], st0})
004453bd        unimplemented  {fstp dword [esp+0x20], st0}
004453c1        unimplemented  {fld st0, dword [esi+0x6c]}
004453c4        long double temp0_1 = fconvert.t(0.49000001f)
004453c4        unimplemented  {fcomp st0, dword [0x4973e8]} f- temp0_1
004453c4        bool c0_13 = unimplemented  {fcomp st0, dword [0x4973e8]} f< temp0_1
004453c4        bool c2_13 = is_unordered.t(unimplemented  {fcomp st0, dword [0x4973e8]}, temp0_1)
004453c4        bool c3_13 = unimplemented  {fcomp st0, dword [0x4973e8]} f== temp0_1
004453c4        unimplemented  {fcomp st0, dword [0x4973e8]}
004453ce        esp_1[0xb] = esp_1[8]
004453d2        eax_26.w = (c0_13 ? 1 : 0) << 8 | (c2_13 ? 1 : 0) << 0xa | (c3_13 ? 1 : 0) << 0xe | (top & 7) << 0xb
004453d7        if ((eax_26:1.b & 1) == 0)
004453dd        unimplemented  {fld st0, dword [esp+0x20]}
004453e1        long double temp1_1 = fconvert.t(1f)
004453e1        unimplemented  {fcomp st0, dword [0x497220]} f- temp1_1
004453e1        bool c0_14 = unimplemented  {fcomp st0, dword [0x497220]} f< temp1_1
004453e1        bool c2_14 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497220]}, temp1_1)
004453e1        bool c3_14 = unimplemented  {fcomp st0, dword [0x497220]} f== temp1_1
004453e1        unimplemented  {fcomp st0, dword [0x497220]}
004453e7        eax_26.w = (c0_14 ? 1 : 0) << 8 | (c2_14 ? 1 : 0) << 0xa | (c3_14 ? 1 : 0) << 0xe | (top & 7) << 0xb
004453ec        if ((eax_26:1.b & 1) != 0)
004453ee        unimplemented  {fld st0, dword [esp+0x1c]}
004453f2        long double temp3_1 = fconvert.t(0f)
004453f2        unimplemented  {fcomp st0, dword [0x497234]} f- temp3_1
004453f2        bool c0_15 = unimplemented  {fcomp st0, dword [0x497234]} f< temp3_1
004453f2        bool c2_15 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497234]}, temp3_1)
004453f2        bool c3_15 = unimplemented  {fcomp st0, dword [0x497234]} f== temp3_1
004453f2        unimplemented  {fcomp st0, dword [0x497234]}
004453f8        unimplemented  {fld st0, dword [esp+0x1c]}
004453fc        eax_26.w = (c0_15 ? 1 : 0) << 8 | (c2_15 ? 1 : 0) << 0xa | (c3_15 ? 1 : 0) << 0xe | ((top - 1) & 7) << 0xb
00445401        if ((eax_26:1.b & 1) != 0)
00445403        unimplemented  {fchs }
00445405        long double temp6_1 = fconvert.t(0.400000006f)
00445405        unimplemented  {fcomp st0, dword [0x4973e0]} f- temp6_1
00445405        bool c0_16 = unimplemented  {fcomp st0, dword [0x4973e0]} f< temp6_1
00445405        bool c2_16 = is_unordered.t(unimplemented  {fcomp st0, dword [0x4973e0]}, temp6_1)
00445405        bool c3_16 = unimplemented  {fcomp st0, dword [0x4973e0]} f== temp6_1
00445405        unimplemented  {fcomp st0, dword [0x4973e0]}
0044540b        eax_26.w = (c0_16 ? 1 : 0) << 8 | (c2_16 ? 1 : 0) << 0xa | (c3_16 ? 1 : 0) << 0xe | (top & 7) << 0xb
00445410        if ((eax_26:1.b & 1) != 0)
00445416        normalize_vector(&esp_1[9])
00445416        unimplemented  {call 0x44cca0}
0044541b        long double temp11_1 = fconvert.t(0.980000019f)
0044541b        unimplemented  {fcomp st0, dword [0x49756c]} f- temp11_1
0044541b        bool c0_17 = unimplemented  {fcomp st0, dword [0x49756c]} f< temp11_1
0044541b        bool c2_17 = is_unordered.t(unimplemented  {fcomp st0, dword [0x49756c]}, temp11_1)
0044541b        bool c3_17 = unimplemented  {fcomp st0, dword [0x49756c]} f== temp11_1
0044541b        unimplemented  {fcomp st0, dword [0x49756c]}
00445426        if ((((c0_17 ? 1 : 0) << 8 | (c2_17 ? 1 : 0) << 0xa | (c3_17 ? 1 : 0) << 0xe | (top & 7) << 0xb):1.b & 1) != 0)
00445428        *(esp_1 - 4) = 0xe
0044542f        play_sound_effect()
0044543a        *(i_5 + player->game + 0x356038) = 2
00445452        *(esp_1 - 4) = &player->game->_pad_00[i_5 + 0x356000]
00445455        health_collect_particles(player)
0044545a        *(esp_1 - 4) = 0
0044545c        *(esp_1 - 8) = 0xbf000000
00445467        apply_damage_gauge_delta(&player->damage_gauge)
00445467        esp_1 -= 4
0044546c        i_5 += 0x74
00445487        if (player->game->__offset(0x355e30).d == 1)
0044548d        unimplemented  {fld st0, dword [eax+0x355e18]}
00445493        unimplemented  {fsub st0, dword [esi+0x2964]}
00445499        esp_1[6] = fconvert.s(unimplemented  {fstp dword [esp+0x18], st0})
00445499        unimplemented  {fstp dword [esp+0x18], st0}
0044549d        unimplemented  {fld st0, dword [eax+0x355e1c]}
004454a3        unimplemented  {fsub st0, dword [esi+0x2968]}
004454a9        int32_t edx_16 = esp_1[6]
004454ad        esp_1[7] = fconvert.s(unimplemented  {fstp dword [esp+0x1c], st0})
004454ad        unimplemented  {fstp dword [esp+0x1c], st0}
004454b1        unimplemented  {fld st0, dword [eax+0x355e20]}
004454b7        unimplemented  {fsub st0, dword [esi+0x296c]}
004454bd        int32_t eax_30 = esp_1[7]
004454c1        esp_1[9] = edx_16
004454c5        esp_1[0xa] = eax_30
004454c9        esp_1[8] = fconvert.s(unimplemented  {fstp dword [esp+0x20], st0})
004454c9        unimplemented  {fstp dword [esp+0x20], st0}
004454cd        unimplemented  {fld st0, dword [esi+0x6c]}
004454d0        long double temp2_1 = fconvert.t(0.49000001f)
004454d0        unimplemented  {fcomp st0, dword [0x4973e8]} f- temp2_1
004454d0        bool c0_18 = unimplemented  {fcomp st0, dword [0x4973e8]} f< temp2_1
004454d0        bool c2_18 = is_unordered.t(unimplemented  {fcomp st0, dword [0x4973e8]}, temp2_1)
004454d0        bool c3_18 = unimplemented  {fcomp st0, dword [0x4973e8]} f== temp2_1
004454d0        unimplemented  {fcomp st0, dword [0x4973e8]}
004454da        esp_1[0xb] = esp_1[8]
004454de        eax_30.w = (c0_18 ? 1 : 0) << 8 | (c2_18 ? 1 : 0) << 0xa | (c3_18 ? 1 : 0) << 0xe | (top & 7) << 0xb
004454e3        if ((eax_30:1.b & 1) == 0)
004454e5        unimplemented  {fld st0, dword [esp+0x20]}
004454e9        long double temp5_1 = fconvert.t(1f)
004454e9        unimplemented  {fcomp st0, dword [0x497220]} f- temp5_1
004454e9        bool c0_19 = unimplemented  {fcomp st0, dword [0x497220]} f< temp5_1
004454e9        bool c2_19 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497220]}, temp5_1)
004454e9        bool c3_19 = unimplemented  {fcomp st0, dword [0x497220]} f== temp5_1
004454e9        unimplemented  {fcomp st0, dword [0x497220]}
004454ef        eax_30.w = (c0_19 ? 1 : 0) << 8 | (c2_19 ? 1 : 0) << 0xa | (c3_19 ? 1 : 0) << 0xe | (top & 7) << 0xb
004454f4        if ((eax_30:1.b & 1) != 0)
004454f6        unimplemented  {fld st0, dword [esp+0x1c]}
004454fa        long double temp10_1 = fconvert.t(0f)
004454fa        unimplemented  {fcomp st0, dword [0x497234]} f- temp10_1
004454fa        bool c0_20 = unimplemented  {fcomp st0, dword [0x497234]} f< temp10_1
004454fa        bool c2_20 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497234]}, temp10_1)
004454fa        bool c3_20 = unimplemented  {fcomp st0, dword [0x497234]} f== temp10_1
004454fa        unimplemented  {fcomp st0, dword [0x497234]}
00445500        unimplemented  {fld st0, dword [esp+0x1c]}
00445504        eax_30.w = (c0_20 ? 1 : 0) << 8 | (c2_20 ? 1 : 0) << 0xa | (c3_20 ? 1 : 0) << 0xe | ((top - 1) & 7) << 0xb
00445509        if ((eax_30:1.b & 1) != 0)
0044550b        unimplemented  {fchs }
0044550d        long double temp16_1 = fconvert.t(0.400000006f)
0044550d        unimplemented  {fcomp st0, dword [0x4973e0]} f- temp16_1
0044550d        bool c0_21 = unimplemented  {fcomp st0, dword [0x4973e0]} f< temp16_1
0044550d        bool c2_21 = is_unordered.t(unimplemented  {fcomp st0, dword [0x4973e0]}, temp16_1)
0044550d        bool c3_21 = unimplemented  {fcomp st0, dword [0x4973e0]} f== temp16_1
0044550d        unimplemented  {fcomp st0, dword [0x4973e0]}
00445513        eax_30.w = (c0_21 ? 1 : 0) << 8 | (c2_21 ? 1 : 0) << 0xa | (c3_21 ? 1 : 0) << 0xe | (top & 7) << 0xb
00445518        if ((eax_30:1.b & 1) != 0)
0044551e        normalize_vector(&esp_1[9])
0044551e        unimplemented  {call 0x44cca0}
00445523        long double temp19_1 = fconvert.t(0.980000019f)
00445523        unimplemented  {fcomp st0, dword [0x49756c]} f- temp19_1
00445523        bool c0_22 = unimplemented  {fcomp st0, dword [0x49756c]} f< temp19_1
00445523        bool c2_22 = is_unordered.t(unimplemented  {fcomp st0, dword [0x49756c]}, temp19_1)
00445523        bool c3_22 = unimplemented  {fcomp st0, dword [0x49756c]} f== temp19_1
00445523        unimplemented  {fcomp st0, dword [0x49756c]}
0044552e        if ((((c0_22 ? 1 : 0) << 8 | (c2_22 ? 1 : 0) << 0xa | (c3_22 ? 1 : 0) << 0xe | (top & 7) << 0xb):1.b & 1) != 0)
00445538        player->game->__offset(0x355e30).d = 2
0044554d        unimplemented  {fld st0, dword [eax+0x38]}
00445550        unimplemented  {fmul st0, dword [0x497228]}
00445556        player->velocity.z = fconvert.s(unimplemented  {fstp dword [esi+0x418], st0})
00445556        unimplemented  {fstp dword [esi+0x418], st0}
00445568        if (player->game->__offset(0x355e9c).d == 1)
0044556e        unimplemented  {fld st0, dword [eax+0x355e74]}
00445574        unimplemented  {fsub st0, dword [esi+0x2964]}
0044557a        esp_1[6] = fconvert.s(unimplemented  {fstp dword [esp+0x18], st0})
0044557a        unimplemented  {fstp dword [esp+0x18], st0}
0044557e        unimplemented  {fld st0, dword [eax+0x355e78]}
00445584        unimplemented  {fsub st0, dword [esi+0x2968]}
0044558a        int32_t ecx_44 = esp_1[6]
0044558e        esp_1[7] = fconvert.s(unimplemented  {fstp dword [esp+0x1c], st0})
0044558e        unimplemented  {fstp dword [esp+0x1c], st0}
00445592        unimplemented  {fld st0, dword [eax+0x355e7c]}
00445598        unimplemented  {fsub st0, dword [esi+0x296c]}
0044559e        int32_t edx_18 = esp_1[7]
004455a2        esp_1[9] = ecx_44
004455a6        esp_1[0xa] = edx_18
004455aa        esp_1[8] = fconvert.s(unimplemented  {fstp dword [esp+0x20], st0})
004455aa        unimplemented  {fstp dword [esp+0x20], st0}
004455ae        unimplemented  {fld st0, dword [esi+0x6c]}
004455b1        long double temp4_1 = fconvert.t(0.49000001f)
004455b1        unimplemented  {fcomp st0, dword [0x4973e8]} f- temp4_1
004455b1        bool c0_23 = unimplemented  {fcomp st0, dword [0x4973e8]} f< temp4_1
004455b1        bool c2_23 = is_unordered.t(unimplemented  {fcomp st0, dword [0x4973e8]}, temp4_1)
004455b1        bool c3_23 = unimplemented  {fcomp st0, dword [0x4973e8]} f== temp4_1
004455b1        unimplemented  {fcomp st0, dword [0x4973e8]}
004455bb        esp_1[0xb] = esp_1[8]
004455bf        int32_t eax_33
004455bf        eax_33.w = (c0_23 ? 1 : 0) << 8 | (c2_23 ? 1 : 0) << 0xa | (c3_23 ? 1 : 0) << 0xe | (top & 7) << 0xb
004455c4        if ((eax_33:1.b & 1) == 0)
004455c6        unimplemented  {fld st0, dword [esp+0x20]}
004455ca        long double temp9_1 = fconvert.t(1f)
004455ca        unimplemented  {fcomp st0, dword [0x497220]} f- temp9_1
004455ca        bool c0_24 = unimplemented  {fcomp st0, dword [0x497220]} f< temp9_1
004455ca        bool c2_24 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497220]}, temp9_1)
004455ca        bool c3_24 = unimplemented  {fcomp st0, dword [0x497220]} f== temp9_1
004455ca        unimplemented  {fcomp st0, dword [0x497220]}
004455d0        eax_33.w = (c0_24 ? 1 : 0) << 8 | (c2_24 ? 1 : 0) << 0xa | (c3_24 ? 1 : 0) << 0xe | (top & 7) << 0xb
004455d5        if ((eax_33:1.b & 1) != 0)
004455db        normalize_vector(&esp_1[9])
004455db        unimplemented  {call 0x44cca0}
004455e0        long double temp15_1 = fconvert.t(3f)
004455e0        unimplemented  {fcomp st0, dword [0x497218]} f- temp15_1
004455e0        bool c0_25 = unimplemented  {fcomp st0, dword [0x497218]} f< temp15_1
004455e0        bool c2_25 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497218]}, temp15_1)
004455e0        bool c3_25 = unimplemented  {fcomp st0, dword [0x497218]} f== temp15_1
004455e0        unimplemented  {fcomp st0, dword [0x497218]}
004455eb        if ((((c0_25 ? 1 : 0) << 8 | (c2_25 ? 1 : 0) << 0xa | (c3_25 ? 1 : 0) << 0xe | (top & 7) << 0xb):1.b & 1) != 0)
004455f3        player->game->__offset(0x355e9c).d = 2
00445603        arm_jetpack_gauge(&player->jetpack_gauge)
00445829        void* result
00445608        void* i_6 = nullptr
00445829        while (i_6 s< 0x3f0)
00445614        struct Game* game_5 = player->game
00445621        result = i_6 + game_5
00445627        if (*(i_6 + game_5 + 0x35b80c) == 1)
0044562d        unimplemented  {fld st0, dword [eax+0x35b7f4]}
00445633        unimplemented  {fsub st0, dword [esi+0x2964]}
00445639        esp_1[0x12] = fconvert.s(unimplemented  {fstp dword [esp+0x48], st0})
00445639        unimplemented  {fstp dword [esp+0x48], st0}
0044563d        unimplemented  {fld st0, dword [eax+0x35b7f8]}
00445643        unimplemented  {fsub st0, dword [esi+0x2968]}
00445649        esp_1[0x13] = fconvert.s(unimplemented  {fstp dword [esp+0x4c], st0})
00445649        unimplemented  {fstp dword [esp+0x4c], st0}
0044564d        unimplemented  {fld st0, dword [eax+0x35b7fc]}
00445653        unimplemented  {fsub st0, dword [esi+0x296c]}
0044565d        int32_t ecx_49 = esp_1[0x13]
00445661        esp_1[0x1e] = esp_1[0x12]
00445665        esp_1[0x1f] = ecx_49
00445669        esp_1[0x14] = fconvert.s(unimplemented  {fst dword [esp+0x50], st0})
0044566d        long double temp14_1 = fconvert.t(1f)
0044566d        unimplemented  {fcomp st0, dword [0x497220]} f- temp14_1
0044566d        bool c0_26 = unimplemented  {fcomp st0, dword [0x497220]} f< temp14_1
0044566d        bool c2_26 = is_unordered.t(unimplemented  {fcomp st0, dword [0x497220]}, temp14_1)
0044566d        bool c3_26 = unimplemented  {fcomp st0, dword [0x497220]} f== temp14_1
0044566d        unimplemented  {fcomp st0, dword [0x497220]}
00445677        esp_1[0x20] = esp_1[0x14]
0044567e        result.w = (c0_26 ? 1 : 0) << 8 | (c2_26 ? 1 : 0) << 0xa | (c3_26 ? 1 : 0) << 0xe | (top & 7) << 0xb
00445683        if ((result:1.b & 1) != 0)
0044568d        normalize_vector(&esp_1[0x1e])
0044568d        unimplemented  {call 0x44cca0}
00445692        long double temp18_1 = fconvert.t(0.980000019f)
00445692        unimplemented  {fcomp st0, dword [0x49756c]} f- temp18_1
00445692        bool c0_27 = unimplemented  {fcomp st0, dword [0x49756c]} f< temp18_1
00445692        bool c2_27 = is_unordered.t(unimplemented  {fcomp st0, dword [0x49756c]}, temp18_1)
00445692        bool c3_27 = unimplemented  {fcomp st0, dword [0x49756c]} f== temp18_1
00445692        unimplemented  {fcomp st0, dword [0x49756c]}
00445698        result.w = (c0_27 ? 1 : 0) << 8 | (c2_27 ? 1 : 0) << 0xa | (c3_27 ? 1 : 0) << 0xe | (top & 7) << 0xb
0044569d        if ((result:1.b & 1) != 0)
004456a9        *(i_6 + player->game + 0x35b80c) = 2
004456b4        struct Game* eax_35
004456b4        eax_35.b = player->completion_handoff_active.b
004456bc        if (eax_35.b == 0)
004456c4        int32_t eax_36 = *(i_6 + player->game + 0x35b814)
004456d2        if (eax_36 == 3 || eax_36 == 7)
004456e5        *(esp_1 - 4) = 0x2b
004456ec        player->velocity.z = -0.100000001f
004456f2        play_sound_effect()
004456d4        unimplemented  {fld st0, dword [ecx+0x38]}
004456d7        unimplemented  {fmul st0, dword [0x497228]}
004456dd        player->velocity.z = fconvert.s(unimplemented  {fstp dword [esi+0x418], st0})
004456dd        unimplemented  {fstp dword [esi+0x418], st0}
004456f7        struct Game* game_2 = player->game
004456fd        result = *(i_6 + game_2 + 0x35b814)
00445710        int32_t eax_39
00445710        if (result == 4 || result == 5)
004457ab        int32_t eax_40 = player->_pad_3f0[0x14].d
004457b4        if (eax_40 s< 0xa)
004457c0        if ((game_2->runtime_flags.b & 0x10) != 0 && game_2->level_mode != 3)
004457c3        player->_pad_3f0[0x14] = (eax_40 + 1).b
004457c3        player->_pad_3f0[0x15] = (eax_40 + 1):1.b
004457c3        player->_pad_3f0[0x16] = (eax_40 + 1):2.b
004457c3        player->_pad_3f0[0x17] = (eax_40 + 1):3.b
004457c9        *(esp_1 - 4) = 0xffffffff
004457cb        *(esp_1 - 8) = 1
004457cd        *(esp_1 - 0xc) = 5
004457d4        play_voice_manager(0x751498)
004457d9        int32_t movement_flag_selector_1 = player->movement_flag_selector
004457e2        if (movement_flag_selector_1 s< 8)
004457e5        player->movement_flag_selector = movement_flag_selector_1 + 1
004457ed        if (movement_flag_selector_1 == 8)
004457ef        player->movement_flag_selector = 7
004457fb        eax_39 = player->movement_flag_selector - 1
004457ff        if (eax_39 s<= 6)
004457ff        goto label_44580c
004457ff        goto label_445801
00445719        if (result == 8)
0044571b        int32_t movement_flag_selector = player->movement_flag_selector
00445724        if (movement_flag_selector s< 8)
00445727        player->movement_flag_selector = movement_flag_selector + 1
0044572f        if (movement_flag_selector == 8)
00445731        player->movement_flag_selector = 7
0044573d        eax_39 = player->movement_flag_selector - 1
00445741        if (eax_39 s<= 6)
00445741        goto label_44580c
00445801        label_445801:
00445801        eax_39 = 6
0044580c        label_44580c:
0044580c        *(esp_1 - 4) = eax_39 + 1
0044580d        play_sound_effect()
00445812        *(esp_1 - 4) = 0
00445814        *(esp_1 - 8) = 2
00445818        result = add_subgoldy_score(player)
0044574f        if (result == 1)
00445751        *(esp_1 - 4) = 0
00445753        *(esp_1 - 8) = 2
00445757        add_subgoldy_score(player)
0044575c        *(esp_1 - 4) = 1
00445763        result = play_sound_effect()
00445775        if (result == 2 || result == 6)
0044577b        *(esp_1 - 4) = 0
0044577d        *(esp_1 - 8) = 2
00445781        add_subgoldy_score(player)
00445786        *(esp_1 - 4) = 0x2a
0044578d        play_sound_effect()
00445798        player->nuke_effect_progress = player->nuke_effect_progress_step
004457a4        result = initialize_nuke(&player->nuke)
0044581d        i_6 += 0x1f8
0044582f        *esp_1
0044582f        esp_1[1]
00445830        esp_1[2]
00445831        esp_1[3]
00445836        return result
