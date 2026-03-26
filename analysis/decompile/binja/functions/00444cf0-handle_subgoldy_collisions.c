/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: handle_subgoldy_collisions @ 0x444cf0 */

00444d1d        struct Vec3 vector
00444d1d        struct Vec3 vector_2
00444d1d        if (player->__offset(0x41d).b == 0 && player->__offset(0x41c).b == 0 && player->__offset(0x2d8).b == 0)
00444d2d        int16_t x87control
00444d2d        if ((0x80 & player->__offset(0x338).b) == 0)
00444d33        int32_t i = 0
00444e11        while (i s< 0x17c0)
00444d40        void* eax_2 = player->__offset(0x408).d + i
00444d55        if (*(eax_2 + 0x357940) == 1 && *(eax_2 + 0x357954) == 1)
00444d85        long double x87_r7_6 = fconvert.t(*(eax_2 + 0x357930)) - fconvert.t(player->__offset(0x296c).d)
00444d8f        vector_2.x = fconvert.s(fconvert.t(*(eax_2 + 0x357928)) - fconvert.t(player->__offset(0x2964).d))
00444d93        vector_2.y = fconvert.s(fconvert.t(*(eax_2 + 0x35792c)) - fconvert.t(player->__offset(0x2968).d))
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
00444dc6        long double x87_r7_8 = fconvert.t(player->__offset(0x1d4).d)
00444dcc        long double temp17_1 = fconvert.t(0f)
00444dcc        x87_r7_8 - temp17_1
00444dd7        if ((((x87_r7_8 < temp17_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_8, temp17_1) ? 1 : 0) << 0xa | (x87_r7_8 == temp17_1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
00444ddf        player->__offset(0x1d4).d = player->__offset(0x1d8).d
00444df8        *(i + player->__offset(0x408).d + 0x357954) = 0
00444e00        x87control = apply_damage_gauge_delta(player + 0x3c4, 0.150000006f, 0)
00444e05        i += 0x98
00444e1e        int32_t i_1 = 0
00444ece        while (i_1 s< 0xdc0)
00444e26        void* eax_6 = player->__offset(0x408).d + i_1
00444e2e        if (*(eax_6 + 0x356b80) == 1)
00444e5e        long double x87_r7_14 = fconvert.t(*(eax_6 + 0x356b70)) - fconvert.t(player->__offset(0x296c).d)
00444e68        vector.x = fconvert.s(fconvert.t(*(eax_6 + 0x356b68)) - fconvert.t(player->__offset(0x2964).d))
00444e6c        vector.y = fconvert.s(fconvert.t(*(eax_6 + 0x356b6c)) - fconvert.t(player->__offset(0x2968).d))
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
00444eac        *(i_1 + player->__offset(0x408).d + 0x356b80) = 2
00444ebd        x87control = apply_damage_gauge_delta(player + 0x3c4, 0.0199999996f, 0)
00444ec2        i_1 += 0xb0
00444eda        void* i_2 = *(player->__offset(0x408).d + 0x359140)
00444ee2        while (i_2 != 0)
00444eee        if (*(i_2 + 0x84) == 1)
00444f15        long double x87_r7_21 = fconvert.t(*(i_2 + 0x70)) - fconvert.t(player->__offset(0x296c).d)
00444f1f        vector.x = fconvert.s(fconvert.t(*(i_2 + 0x68)) - fconvert.t(player->__offset(0x2964).d))
00444f23        vector.y = fconvert.s(fconvert.t(*(i_2 + 0x6c)) - fconvert.t(player->__offset(0x2968).d))
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
00444f64        if ((player->__offset(0x338).b & 0x80) == 0)
00444f7c        player->__offset(0x410).d = fconvert.s(fconvert.t(player->__offset(0x410).d) - fconvert.t(vector.x) * fconvert.t(player->__offset(0x418).d) * fconvert.t(0.180000007f))
00444f98        player->__offset(0x418).d = fconvert.s(fconvert.t(player->__offset(0x418).d) - fconvert.t(vector.z) * fconvert.t(player->__offset(0x418).d) * fconvert.t(0.100000001f))
00444fa3        *(i_2 + 0x84) = 2
00444fa9        long double x87_r7_31 = fconvert.t(vector.x)
00444fad        long double temp24_1 = fconvert.t(0f)
00444fad        x87_r7_31 - temp24_1
00444fb8        if ((((x87_r7_31 < temp24_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_31, temp24_1) ? 1 : 0) << 0xa | (x87_r7_31 == temp24_1 ? 1 : 0) << 0xe):1.b & 1) == 0)
00444fc2        *(i_2 + 0x88) = 1
00444fba        *(i_2 + 0x88) = 2
00444fce        add_subgoldy_score(player, 0, 0)
0044500a        x87control = play_sound_effect(0x27 - __ftol(apply_damage_gauge_delta(player + 0x3c4, 0.0399999991f, 0), float.t(next_math_random_value()) * fconvert.t(-6.10351562e-05f)))
0044500f        i_2 = *(i_2 + 0x80)
0044501d        void* i_3 = nullptr
0044524b        while (i_3 s< 0x760)
0044501f        int32_t edx_6 = player->__offset(0x408).d
00445025        int32_t ecx_14 = *(i_3 + edx_6 + 0x356420)
0044502c        void* eax_13 = i_3 + edx_6
00445036        if (ecx_14 == 1 || ecx_14 == 4)
00445062        long double x87_r7_39 = fconvert.t(*(eax_13 + 0x356410)) - fconvert.t(player->__offset(0x296c).d)
00445070        vector.x = fconvert.s(fconvert.t(*(eax_13 + 0x356408)) - fconvert.t(player->__offset(0x2964).d))
00445074        vector.y = fconvert.s(fconvert.t(*(eax_13 + 0x35640c)) - fconvert.t(player->__offset(0x2968).d))
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
004450b9        if ((player->__offset(0x338).b & 0x80) != 0)
0044523a        x87control = kill_slug_hazard(i_3 + player->__offset(0x408).d + 0x3563a0)
004450bf        int16_t eax_15
004450bf        eax_15.b = player->__offset(0x2d8).b
004450c7        if (eax_15.b != 0)
0044520b        long double x87_r7_49 = fconvert.t(*(player->__offset(0x408).d + 0x38))
0044521e        player->__offset(0x418).d = fconvert.s(x87_r7_49 * x87_r7_49 * fconvert.t(0.00400000019f) * fconvert.t(-8f))
00445226        x87control = apply_damage_gauge_delta(player + 0x3c4, 1f, 0)
004450cd        void* eax_16 = player->__offset(0x408).d
004450d3        player->__offset(0x2d8).b = 1
004450da        player->__offset(0x384).b = 0
004450e9        long double x87_r7_41 = fconvert.t(*(eax_16 + 0x38))
004450fe        player->__offset(0x410).d = 0
00445112        player->__offset(0x414).d = fconvert.s(x87_r7_41 * fconvert.t(0.200000003f))
0044511d        player->__offset(0x418).d = fconvert.s(x87_r7_41 * fconvert.t(-0.200000003f))
00445122        begin_post_follow_carryover(player)
00445127        int32_t eax_18 = player->__offset(0x408).d
0044512d        player->__offset(0x42e8).d = 0xa
00445137        *(i_3 + eax_18 + 0x356479) = 1
00445152        int32_t eax_20 = __ftol(x87control, float.t(next_math_random_value()) * fconvert.t(-6.10351562e-05f))
0044516c        x87control = play_slug_voice(i_3 + player->__offset(0x408).d + 0x3563a0, 0x22 - eax_20)
00445175        long double x87_r7_46 = fconvert.t(fconvert.s(st0_4)) * fconvert.t(0.5f)
0044517b        player->__offset(0x3f4c).d = 0
0044519d        long double x87_r7_47 = x87_r7_46 * fconvert.t(vector.z)
004451ab        vector_2.x = fconvert.s(fconvert.t(fconvert.s(x87_r7_46 * fconvert.t(vector.x))) + fconvert.t(player->__offset(0x2964).d))
004451b3        long double x87_r6_10 = fconvert.t(fconvert.s(fconvert.t(vector.y) * x87_r7_46)) + fconvert.t(player->__offset(0x2968).d)
004451bd        float x = vector_2.x
004451c8        vector_2.y = fconvert.s(x87_r6_10)
004451d6        float y = vector_2.y
004451e5        vector_2.z = fconvert.s(x87_r7_47 + fconvert.t(player->__offset(0x296c).d))
004451ed        float z = vector_2.z
004451f1        firework_shoot(&x, player->__offset(0x380).d, 1.28919459e-43f, 1.12103877e-43f)
0044523f        i_3 += 0xec
00445251        void* i_4 = nullptr
0044535a        while (i_4 s< 0x1b58)
00445253        int32_t ecx_25 = player->__offset(0x408).d
00445259        void* eax_24 = i_4 + ecx_25
00445265        if (*(i_4 + ecx_25 + 0x125e4b8) == 1)
00445277        vector_2.x = fconvert.s(fconvert.t(*(eax_24 + 0x125e490)) - fconvert.t(player->__offset(0x2964).d))
0044528b        vector_2.y = fconvert.s(fconvert.t(*(eax_24 + 0x125e494)) - fconvert.t(player->__offset(0x2968).d))
00445295        long double x87_r7_56 = fconvert.t(*(eax_24 + 0x125e498)) - fconvert.t(player->__offset(0x296c).d)
0044529f        struct Vec3 vector_3
0044529f        vector_3.x = vector_2.x
004452a3        vector_3.y = vector_2.y
004452a7        vector_2.z = fconvert.s(x87_r7_56)
004452ab        long double temp25_1 = fconvert.t(1f)
004452ab        x87_r7_56 - temp25_1
004452b5        vector_3.z = vector_2.z
004452b9        float eax_25
004452b9        eax_25.w = (x87_r7_56 < temp25_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_56, temp25_1) ? 1 : 0) << 0xa | (x87_r7_56 == temp25_1 ? 1 : 0) << 0xe
004452be        if ((eax_25:1.b & 1) != 0)
004452c8        long double st0_5 = normalize_vector(&vector_3)
004452cd        long double temp26_1 = fconvert.t(1.24000001f)
004452cd        st0_5 - temp26_1
004452d8        if ((((st0_5 < temp26_1 ? 1 : 0) << 8 | (is_unordered.t(st0_5, temp26_1) ? 1 : 0) << 0xa | (st0_5 == temp26_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
004452e0        add_subgoldy_score(player, 3, 0)
004452ef        play_voice_manager(0x751498, 0xa, 1, 0xffffffff)
004452fb        play_sound_effect(0x1b)
00445306        *(i_4 + player->__offset(0x408).d + 0x125e4b8) = 4
00445317        void* eax_27 = player->__offset(0x408).d
0044531d        int32_t ebx_2 = player->__offset(0x4338).d + 1
0044531e        player->__offset(0x4338).d = ebx_2
0044532b        if (*(eax_27 + 0x40) == 0)
00445339        int32_t var_88_3 = *(eax_27 + 0x1b01e0)
0044533a        int32_t var_8c_1 = ebx_2
00445346        sub_48b32c(*(eax_27 + 0x35bb94) + 0x2cc, "%i/%i")
0044534e        i_4 += 0x8c
00445475        struct Vec3 vector_1
00445367        void* i_5 = nullptr
00445475        while (i_5 s< 0x3a0)
00445369        int32_t ecx_32 = player->__offset(0x408).d
0044536f        void* eax_30 = i_5 + ecx_32
0044537b        if (*(i_5 + ecx_32 + 0x356038) == 1)
0044538d        vector.x = fconvert.s(fconvert.t(*(eax_30 + 0x356010)) - fconvert.t(player->__offset(0x2964).d))
004453a1        vector.y = fconvert.s(fconvert.t(*(eax_30 + 0x356014)) - fconvert.t(player->__offset(0x2968).d))
004453b5        vector_1.x = vector.x
004453b9        vector_1.y = vector.y
004453bd        vector.z = fconvert.s(fconvert.t(*(eax_30 + 0x356018)) - fconvert.t(player->__offset(0x296c).d))
004453c1        long double x87_r7_64 = fconvert.t(player->__offset(0x6c).d)
004453c4        long double temp0_1 = fconvert.t(0.49000001f)
004453c4        x87_r7_64 - temp0_1
004453ce        vector_1.z = vector.z
004453d2        float eax_31
004453d2        eax_31.w = (x87_r7_64 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_64, temp0_1) ? 1 : 0) << 0xa | (x87_r7_64 == temp0_1 ? 1 : 0) << 0xe
004453d7        if ((eax_31:1.b & 1) == 0)
004453dd        long double x87_r7_65 = fconvert.t(vector.z)
004453e1        long double temp1_1 = fconvert.t(1f)
004453e1        x87_r7_65 - temp1_1
004453e7        eax_31.w = (x87_r7_65 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_65, temp1_1) ? 1 : 0) << 0xa | (x87_r7_65 == temp1_1 ? 1 : 0) << 0xe
004453ec        if ((eax_31:1.b & 1) != 0)
004453ee        long double x87_r7_66 = fconvert.t(vector.y)
004453f2        long double temp3_1 = fconvert.t(0f)
004453f2        x87_r7_66 - temp3_1
004453f8        long double x87_r7_67 = fconvert.t(vector.y)
004453fc        eax_31.w = (x87_r7_66 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_66, temp3_1) ? 1 : 0) << 0xa | (x87_r7_66 == temp3_1 ? 1 : 0) << 0xe | 0x3800
00445401        if ((eax_31:1.b & 1) != 0)
00445403        x87_r7_67 = fneg(x87_r7_67)
00445405        long double temp6_1 = fconvert.t(0.400000006f)
00445405        x87_r7_67 - temp6_1
0044540b        eax_31.w = (x87_r7_67 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_67, temp6_1) ? 1 : 0) << 0xa | (x87_r7_67 == temp6_1 ? 1 : 0) << 0xe
00445410        if ((eax_31:1.b & 1) != 0)
00445416        long double st0_6 = normalize_vector(&vector_1)
0044541b        long double temp11_1 = fconvert.t(0.980000019f)
0044541b        st0_6 - temp11_1
00445426        if ((((st0_6 < temp11_1 ? 1 : 0) << 8 | (is_unordered.t(st0_6, temp11_1) ? 1 : 0) << 0xa | (st0_6 == temp11_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
0044542f        play_sound_effect(0xe)
0044543a        *(i_5 + player->__offset(0x408).d + 0x356038) = 2
00445455        health_collect_particles(player, i_5 + player->__offset(0x408).d + 0x356000)
00445467        apply_damage_gauge_delta(player + 0x3c4, -0.5f, 0)
0044546c        i_5 += 0x74
0044547b        void* eax_34 = player->__offset(0x408).d
00445487        if (*(eax_34 + 0x355e30) == 1)
00445499        vector.x = fconvert.s(fconvert.t(*(eax_34 + 0x355e18)) - fconvert.t(player->__offset(0x2964).d))
004454ad        vector.y = fconvert.s(fconvert.t(*(eax_34 + 0x355e1c)) - fconvert.t(player->__offset(0x2968).d))
004454c1        vector_1.x = vector.x
004454c5        vector_1.y = vector.y
004454c9        vector.z = fconvert.s(fconvert.t(*(eax_34 + 0x355e20)) - fconvert.t(player->__offset(0x296c).d))
004454cd        long double x87_r7_75 = fconvert.t(player->__offset(0x6c).d)
004454d0        long double temp2_1 = fconvert.t(0.49000001f)
004454d0        x87_r7_75 - temp2_1
004454da        vector_1.z = vector.z
004454de        float eax_35
004454de        eax_35.w = (x87_r7_75 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_75, temp2_1) ? 1 : 0) << 0xa | (x87_r7_75 == temp2_1 ? 1 : 0) << 0xe
004454e3        if ((eax_35:1.b & 1) == 0)
004454e5        long double x87_r7_76 = fconvert.t(vector.z)
004454e9        long double temp5_1 = fconvert.t(1f)
004454e9        x87_r7_76 - temp5_1
004454ef        eax_35.w = (x87_r7_76 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_76, temp5_1) ? 1 : 0) << 0xa | (x87_r7_76 == temp5_1 ? 1 : 0) << 0xe
004454f4        if ((eax_35:1.b & 1) != 0)
004454f6        long double x87_r7_77 = fconvert.t(vector.y)
004454fa        long double temp10_1 = fconvert.t(0f)
004454fa        x87_r7_77 - temp10_1
00445500        long double x87_r7_78 = fconvert.t(vector.y)
00445504        eax_35.w = (x87_r7_77 < temp10_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_77, temp10_1) ? 1 : 0) << 0xa | (x87_r7_77 == temp10_1 ? 1 : 0) << 0xe | 0x3800
00445509        if ((eax_35:1.b & 1) != 0)
0044550b        x87_r7_78 = fneg(x87_r7_78)
0044550d        long double temp16_1 = fconvert.t(0.400000006f)
0044550d        x87_r7_78 - temp16_1
00445513        eax_35.w = (x87_r7_78 < temp16_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_78, temp16_1) ? 1 : 0) << 0xa | (x87_r7_78 == temp16_1 ? 1 : 0) << 0xe
00445518        if ((eax_35:1.b & 1) != 0)
0044551e        long double st0_7 = normalize_vector(&vector_1)
00445523        long double temp19_1 = fconvert.t(0.980000019f)
00445523        st0_7 - temp19_1
0044552e        if ((((st0_7 < temp19_1 ? 1 : 0) << 8 | (is_unordered.t(st0_7, temp19_1) ? 1 : 0) << 0xa | (st0_7 == temp19_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00445538        *(player->__offset(0x408).d + 0x355e30) = 2
00445556        player->__offset(0x418).d = fconvert.s(fconvert.t(*(player->__offset(0x408).d + 0x38)) * fconvert.t(0.5f))
0044555c        void* eax_38 = player->__offset(0x408).d
00445568        if (*(eax_38 + 0x355e9c) == 1)
0044557a        vector.x = fconvert.s(fconvert.t(*(eax_38 + 0x355e74)) - fconvert.t(player->__offset(0x2964).d))
0044558e        vector.y = fconvert.s(fconvert.t(*(eax_38 + 0x355e78)) - fconvert.t(player->__offset(0x2968).d))
004455a2        vector_1.x = vector.x
004455a6        vector_1.y = vector.y
004455aa        vector.z = fconvert.s(fconvert.t(*(eax_38 + 0x355e7c)) - fconvert.t(player->__offset(0x296c).d))
004455ae        long double x87_r7_88 = fconvert.t(player->__offset(0x6c).d)
004455b1        long double temp4_1 = fconvert.t(0.49000001f)
004455b1        x87_r7_88 - temp4_1
004455bb        vector_1.z = vector.z
004455bf        float eax_39
004455bf        eax_39.w = (x87_r7_88 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_88, temp4_1) ? 1 : 0) << 0xa | (x87_r7_88 == temp4_1 ? 1 : 0) << 0xe
004455c4        if ((eax_39:1.b & 1) == 0)
004455c6        long double x87_r7_89 = fconvert.t(vector.z)
004455ca        long double temp9_1 = fconvert.t(1f)
004455ca        x87_r7_89 - temp9_1
004455d0        eax_39.w = (x87_r7_89 < temp9_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_89, temp9_1) ? 1 : 0) << 0xa | (x87_r7_89 == temp9_1 ? 1 : 0) << 0xe
004455d5        if ((eax_39:1.b & 1) != 0)
004455db        long double st0_8 = normalize_vector(&vector_1)
004455e0        long double temp15_1 = fconvert.t(3f)
004455e0        st0_8 - temp15_1
004455eb        if ((((st0_8 < temp15_1 ? 1 : 0) << 8 | (is_unordered.t(st0_8, temp15_1) ? 1 : 0) << 0xa | (st0_8 == temp15_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
004455f3        *(player->__offset(0x408).d + 0x355e9c) = 2
00445603        arm_jetpack_gauge(player + 0x2750)
00445608        void* i_6 = nullptr
00445829        while (i_6 s< 0x3f0)
00445614        int32_t edx_21 = player->__offset(0x408).d
00445621        void* eax_41 = i_6 + edx_21
00445627        if (*(i_6 + edx_21 + 0x35b80c) == 1)
00445639        vector_2.x = fconvert.s(fconvert.t(*(eax_41 + 0x35b7f4)) - fconvert.t(player->__offset(0x2964).d))
00445649        vector_2.y = fconvert.s(fconvert.t(*(eax_41 + 0x35b7f8)) - fconvert.t(player->__offset(0x2968).d))
00445653        long double x87_r7_96 = fconvert.t(*(eax_41 + 0x35b7fc)) - fconvert.t(player->__offset(0x296c).d)
00445661        struct Vec3 vector_4
00445661        vector_4.x = vector_2.x
00445665        vector_4.y = vector_2.y
00445669        vector_2.z = fconvert.s(x87_r7_96)
0044566d        long double temp14_1 = fconvert.t(1f)
0044566d        x87_r7_96 - temp14_1
00445677        vector_4.z = vector_2.z
0044567e        float eax_42
0044567e        eax_42.w = (x87_r7_96 < temp14_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_96, temp14_1) ? 1 : 0) << 0xa | (x87_r7_96 == temp14_1 ? 1 : 0) << 0xe
00445683        if ((eax_42:1.b & 1) != 0)
0044568d        long double st0_9 = normalize_vector(&vector_4)
00445692        long double temp18_1 = fconvert.t(0.980000019f)
00445692        st0_9 - temp18_1
0044569d        if ((((st0_9 < temp18_1 ? 1 : 0) << 8 | (is_unordered.t(st0_9, temp18_1) ? 1 : 0) << 0xa | (st0_9 == temp18_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
004456a9        *(i_6 + player->__offset(0x408).d + 0x35b80c) = 2
004456b4        int32_t eax_44
004456b4        eax_44.b = player->__offset(0x440).b
004456bc        if (eax_44.b == 0)
004456be        void* ecx_50 = player->__offset(0x408).d
004456c4        int32_t eax_45 = *(i_6 + ecx_50 + 0x35b814)
004456d2        if (eax_45 == 3 || eax_45 == 7)
004456ec        player->__offset(0x418).d = 0xbdcccccd
004456f2        play_sound_effect(0x2b)
004456dd        player->__offset(0x418).d = fconvert.s(fconvert.t(*(ecx_50 + 0x38)) * fconvert.t(0.5f))
004456f7        void* ecx_52 = player->__offset(0x408).d
004456fd        int32_t eax_46 = *(i_6 + ecx_52 + 0x35b814)
00445710        int32_t eax_50
00445710        if (eax_46 == 4 || eax_46 == 5)
004457ab        int32_t eax_51 = player->__offset(0x404).d
004457b4        if (eax_51 s< 0xa)
004457c0        if ((*(ecx_52 + 0x4c) & 0x10) != 0 && *(ecx_52 + 0x40) != 3)
004457c3        player->__offset(0x404).d = eax_51 + 1
004457d4        play_voice_manager(0x751498, 5, 1, 0xffffffff)
004457d9        int32_t eax_53 = player->__offset(0x308).d
004457e2        if (eax_53 s< 8)
004457e5        player->__offset(0x308).d = eax_53 + 1
004457ed        if (eax_53 == 8)
004457ef        player->__offset(0x308).d = 7
004457fb        eax_50 = player->__offset(0x308).d - 1
004457ff        if (eax_50 s> 6)
004457ff        goto label_445801
0044580d        play_sound_effect(eax_50 + 1)
00445818        add_subgoldy_score(player, 2, 0)
00445719        if (eax_46 == 8)
0044571b        int32_t eax_47 = player->__offset(0x308).d
00445724        if (eax_47 s< 8)
00445727        player->__offset(0x308).d = eax_47 + 1
0044572f        if (eax_47 == 8)
00445731        player->__offset(0x308).d = 7
0044573d        eax_50 = player->__offset(0x308).d - 1
00445741        if (eax_50 s<= 6)
0044580d        play_sound_effect(eax_50 + 1)
00445818        add_subgoldy_score(player, 2, 0)
00445801        label_445801:
0044580d        play_sound_effect(6 + 1)
00445818        add_subgoldy_score(player, 2, 0)
0044574f        if (eax_46 == 1)
00445757        add_subgoldy_score(player, 2, 0)
00445763        play_sound_effect(1)
00445775        if (eax_46 == 2 || eax_46 == 6)
00445781        add_subgoldy_score(player, 2, 0)
0044578d        play_sound_effect(0x2a)
00445798        player->__offset(0x374).d = player->__offset(0x378).d
004457a4        initialize_nuke(player + 0x150)
0044581d        i_6 += 0x1f8
00445836        return
