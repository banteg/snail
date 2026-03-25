/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_cutscene @ 0x4466d0 */

004466df        arg1[0x16].b = 0
004466e3        float eax_1 = arg1[3] - 1
004466fa        struct TransformMatrix* var_100
004466fa        void transform
004466fa        struct TransformMatrix transform_1
004466fa        switch (eax_1)
00446701        case 0
00446701        void* ecx = *arg1
00446704        int32_t var_fc_1 = 0xffffffff
00446706        var_100 = 1
00446709        arg1[3] = 2
00446710        arg1[0x14] = 0
00446717        arg1[0x15] = 0x3c088889
0044671a        arg1[0x16].b = 1
0044671d        dispatch_cutscene_animation(ecx, 9, var_100.b, var_fc_1)
00446722        void* ecx_1 = *arg1
00446725        int32_t var_fc_2 = 0xffffffff
00446727        var_100 = nullptr
0044672b        dispatch_cutscene_animation(ecx_1, 9, var_100.b, var_fc_2)
00446730        void* ecx_2 = *arg1
00446733        int32_t var_fc_3 = 0xffffffff
00446735        var_100 = nullptr
00446738        dispatch_cutscene_animation(ecx_2, 1, var_100.b, var_fc_3)
00446740        label_446740:
00446740        arg1[2] = 1
00446745        set_matrix_identity(&arg1[4])
0044674a        void* eax_2 = *arg1
0044675c        arg1[0x10] = *(eax_2 + 0x1888)
00446761        arg1[0x11] = *(eax_2 + 0x188c)
00446767        arg1[0x12] = *(eax_2 + 0x1890)
0044676c        look_at_point(&arg1[4], eax_2 + 0x68)
00446774        long double x87_r7_2 = fconvert.t(arg1[0x14]) + fconvert.t(arg1[0x15])
00446777        arg1[0x14] = fconvert.s(x87_r7_2)
0044677a        long double temp0_1 = fconvert.t(1f)
0044677a        x87_r7_2 - temp0_1
00446780        eax_1.w = (x87_r7_2 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp0_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp0_1 ? 1 : 0) << 0xe
00446785        if ((eax_1:1.b & 0x41) == 0)
0044678b        arg1[0x15] = 0x3c088889
0044678f        arg1[3] = 8
00446796        arg1[0x14] = 0
004466fa        case 1
004466fa        goto label_446740
00446b50        case 4
00446b50        void* ecx_31 = *arg1
00446b58        int32_t var_fc_21 = 0xffffffff
00446b59        var_100 = 1
00446b5c        arg1[3] = 7
00446b63        arg1[2] = 0xffffffff
00446b66        dispatch_cutscene_animation(ecx_31, 8, var_100.b, var_fc_21)
00446b6b        void* ecx_32 = *arg1
00446b6e        int32_t var_fc_22 = 0xffffffff
00446b6f        var_100 = nullptr
00446b73        dispatch_cutscene_animation(ecx_32, 9, var_100.b, var_fc_22)
00446b78        void* ecx_33 = *arg1
00446b7b        int32_t var_fc_23 = 0xffffffff
00446b7c        var_100 = nullptr
00446b80        dispatch_cutscene_animation(ecx_33, 9, var_100.b, var_fc_23)
00446b85        void* eax_17 = *arg1
00446b88        arg1[3] = 6
00446b8f        arg1[0x14] = 0
00446b96        arg1[0x15] = 0x3c088889
00446b9d        *(eax_17 + 0x1930) = 0x3c888889
00446ba7        void* eax_18 = *arg1
00446bb0        *(eax_18 + 0x192c) = *(eax_18 + 0x1930)
00446bb6        arg1[0x16].b = 1
00446bb9        void* ecx_35 = data_4df904
00446bbf        int32_t eax_19 = *(ecx_35 + 0x74658)
00446bc7        if (eax_19 == 0)
00446bd2        struct TransformMatrix* eax_20 = *(arg1[1] + 0x4338)
00446bda        void* edx_13
00446bda        edx_13.b = eax_20 == *(ecx_35 + 0x2247f8)
00446bdd        int32_t var_dc
00446bdd        var_dc.b = edx_13.b
00446be6        var_100 = eax_20
00446bfe        initialize_completion_screen(ecx_35 + 0x12e6df0, var_100, var_dc)
00446beb        if (eax_19 == 1)
00446bf0        int32_t var_fc_24 = 1
00446bf7        var_100 = *(arg1[1] + 0x4338)
00446bfe        initialize_completion_screen(ecx_35 + 0x12e6df0, var_100, var_fc_24)
00446c0a        play_sound_effect(0x2e)
00446c0a        goto label_446c13
00446c13        case 5
00446c13        label_446c13:
00446c13        arg1[2] = 0xffffffff
00446c16        set_matrix_identity(&transform_1)
00446c1b        void* eax_22 = *arg1
00446c29        float edx_16 = *(eax_22 + 0x1840)
00446c2f        float edx_17 = *(eax_22 + 0x1844)
00446c36        float ecx_40 = *(eax_22 + 0x1848)
00446c69        float eax_24 = arg1[0x14]
00446caa        float var_e8_3 = fconvert.s((fconvert.t(*(eax_22 + 0x1888)) - fconvert.t(edx_16)) * fconvert.t(eax_24) + fconvert.t(edx_16))
00446cba        float var_fc_26 = var_e8_3
00446cbb        transform_1.position.x = var_e8_3
00446cd2        transform_1.position.y = fconvert.s(fconvert.t(edx_17) + fconvert.t(fconvert.s(fconvert.t(fconvert.s(fconvert.t(*(eax_22 + 0x188c)) - fconvert.t(edx_17))) * fconvert.t(eax_24))))
00446cea        transform_1.position.z = fconvert.s(fconvert.t(ecx_40) + fconvert.t(fconvert.s(fconvert.t(fconvert.s(fconvert.t(*(eax_22 + 0x1890)) - fconvert.t(ecx_40))) * fconvert.t(eax_24))))
00446cf9        long double x87_r7_49 = sine(fconvert.s(fconvert.t(arg1[0x14]) * fconvert.t(3.14159274f))) * fconvert.t(0.5f)
00446d14        transform_1.position.x = fconvert.s(fconvert.t(transform_1.position.x) - x87_r7_49)
00446d1b        look_at_point(&transform_1, *arg1 + 0x68)
00446d43        int32_t var_fc_29 = __builtin_memcpy(&transform, *(*arg1 + 0x100) + 0x200, 0x40)
00446d4c        float var_fc_31 = fconvert.s(sine(fconvert.s(fconvert.t(arg1[0x14]) * fconvert.t(1.57079637f))))
00446d57        var_100 = &transform_1
00446d5c        linear_interpolate_matrix(&arg1[4], &transform, var_100, var_fc_31)
00446d64        long double x87_r7_55 = fconvert.t(arg1[0x14]) + fconvert.t(arg1[0x15])
00446d67        arg1[0x14] = fconvert.s(x87_r7_55)
00446d6a        long double temp4_1 = fconvert.t(1f)
00446d6a        x87_r7_55 - temp4_1
00446d70        eax_1.w = (x87_r7_55 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_55, temp4_1) ? 1 : 0) << 0xa | (x87_r7_55 == temp4_1 ? 1 : 0) << 0xe
00446d75        if ((eax_1:1.b & 0x41) == 0)
00446d78        arg1[3] = 7
00446d7f        arg1[0x14] = 0
00446d86        arg1[0x15] = 0x3c888889
00446d9a        case 6
00446d9a        arg1[2] = 0xffffffff
00446da3        arg1[0x16].b = 1
00446da7        set_matrix_identity(&arg1[4])
00446dac        void* eax_26 = *arg1
00446dbe        arg1[0x10] = *(eax_26 + 0x1888)
00446dc3        arg1[0x11] = *(eax_26 + 0x188c)
00446dc9        arg1[0x12] = *(eax_26 + 0x1890)
00446dce        look_at_point(&arg1[4], eax_26 + 0x68)
00446dd3        void* ecx_51 = *arg1
00446dd6        eax_1 = *(ecx_51 + 0x140)
00446dde        if (eax_1 == 0)
00446de0        int32_t var_fc_33 = 0xffffffff
00446de2        var_100 = nullptr
00446de6        eax_1 = dispatch_cutscene_animation(ecx_51, 9, var_100.b, var_fc_33)
00446df1        arg1[0x14] = fconvert.s(fconvert.t(arg1[0x15]) + fconvert.t(arg1[0x14]))
004467b1        case 7
004467b1        *(data_4df904 + 0x42fec4) = 0
004467b8        arg1[2] = 1
004467bf        set_matrix_identity(&transform)
004467d0        int32_t* eax_5 = *arg1 + 0x1888
004467d5        float ecx_8 = *eax_5
004467db        float var_fc_5 = ecx_8
004467e2        int32_t var_8c_1 = eax_5[1]
004467e9        int32_t var_88_1 = eax_5[2]
004467ed        long double st0_1 = sine(fconvert.s(fconvert.t(arg1[0x14]) * fconvert.t(3.14159274f)))
00446806        float var_90_2 = fconvert.s(st0_1 + st0_1 + fconvert.t(ecx_8))
0044680a        look_at_point(&transform, *arg1 + 0x68)
00446832        int32_t var_fc_8 = __builtin_memcpy(&transform_1, *(*arg1 + 0x100) + 0x200, 0x40)
0044683b        float var_fc_10 = fconvert.s(sine(fconvert.s(fconvert.t(arg1[0x14]) * fconvert.t(1.57079637f))))
00446846        var_100 = &transform_1
0044684b        linear_interpolate_matrix(&arg1[4], &transform, var_100, var_fc_10)
00446850        void* eax_7 = *arg1
00446878        struct Vec3 vector
00446878        vector.x = fconvert.s(fconvert.t(arg1[0x10]) - fconvert.t(*(eax_7 + 0x68)))
0044687c        vector.y = fconvert.s(fconvert.t(arg1[0x11]) - fconvert.t(*(eax_7 + 0x6c)))
00446888        vector.z = fconvert.s(fconvert.t(arg1[0x12]) - fconvert.t(*(eax_7 + 0x70)))
00446890        long double st0_3
00446890        st0_3, eax_1 = normalize_vector(&vector)
00446895        long double temp3_1 = fconvert.t(1.5f)
00446895        st0_3 - temp3_1
0044689b        eax_1.w = (st0_3 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(st0_3, temp3_1) ? 1 : 0) << 0xa | (st0_3 == temp3_1 ? 1 : 0) << 0xe | 0x3800
004468a0        if ((eax_1:1.b & 1) != 0)
004468a2        long double x87_r7_18 = fconvert.t(1.5f) - st0_3
004468b8        float var_e4_2 = fconvert.s(fconvert.t(vector.y) * x87_r7_18)
004468bc        long double x87_r7_19 = x87_r7_18 * fconvert.t(vector.z)
004468c7        arg1[0x10] = fconvert.s(fconvert.t(fconvert.s(fconvert.t(vector.x) * x87_r7_18)) + fconvert.t(arg1[0x10]))
004468d1        arg1[0x11] = fconvert.s(fconvert.t(var_e4_2) + fconvert.t(arg1[0x11]))
004468d7        arg1[0x12] = fconvert.s(x87_r7_19 + fconvert.t(arg1[0x12]))
004468e1        long double x87_r7_23 = fconvert.t(arg1[0x14]) + fconvert.t(arg1[0x15])
004468e4        arg1[0x14] = fconvert.s(x87_r7_23)
004468e7        long double temp6_1 = fconvert.t(1f)
004468e7        x87_r7_23 - temp6_1
004468ed        eax_1.w = (x87_r7_23 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_23, temp6_1) ? 1 : 0) << 0xa | (x87_r7_23 == temp6_1 ? 1 : 0) << 0xe
004468f2        if ((eax_1:1.b & 0x41) == 0)
004468f9        arg1[3] = 9
00446900        arg1[0x14] = 0
00446907        arg1[0x15] = 0x3c088889
00446929        case 8
0044692f        __builtin_memcpy(&arg1[4], *(*arg1 + 0x100) + 0x200, 0x40)
00446932        arg1[3] = 0
00446943        case 9
00446943        void* ecx_16 = *arg1
0044694e        int32_t var_fc_11 = 0xffffffff
0044694f        var_100 = 1
00446952        arg1[2] = 0xffffffff
00446955        dispatch_cutscene_animation(ecx_16, 7, var_100.b, var_fc_11)
0044695a        int32_t var_fc_12 = 0xffffffff
0044695b        var_100 = 2
00446964        arg1[3] = 0xb
0044696b        arg1[0x14] = 0
00446972        arg1[0x15] = 0x3c088889
00446979        arg1[0x16].b = 1
0044697c        play_voice_manager(0x751498, 3, var_100, var_fc_12)
0044698a        *(*(*arg1 + 0x100) + 0x44c) = 1
00446993        release_snail_weapons(*arg1)
0044699c        label_44699c:
0044699c        arg1[2] = 0xffffffff
0044699f        set_matrix_identity(&transform_1)
004469b0        int32_t* edx_8 = *arg1 + 0x1888
004469b8        transform_1.position.x = *edx_8
004469bf        int32_t ecx_20 = edx_8[1]
004469c2        int32_t var_fc_13 = ecx_20
004469c3        transform_1.position.y = ecx_20
004469d0        transform_1.position.z = edx_8[2]
004469d7        long double st0_4 = sine(fconvert.s(fconvert.t(arg1[0x14]) * fconvert.t(3.14159274f)))
004469e8        transform_1.position.x = fconvert.s(st0_4 + st0_4 + fconvert.t(transform_1.position.x))
004469ef        long double x87_r7_29 = fconvert.t(transform_1.position.y)
004469f6        long double temp1_1 = fconvert.t(0f)
004469f6        x87_r7_29 - temp1_1
00446a01        if ((((x87_r7_29 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_29, temp1_1) ? 1 : 0) << 0xa | (x87_r7_29 == temp1_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00446a03        transform_1.position.y = 0
00446a19        look_at_point(&transform_1, *arg1 + 0x68)
00446a25        long double x87_r7_30 = fconvert.t(arg1[0x14])
00446a41        int32_t var_fc_16 = __builtin_memcpy(&transform, *(*arg1 + 0x100) + 0x200, 0x40)
00446a4a        float var_fc_18 = fconvert.s(sine(fconvert.s(x87_r7_30 * fconvert.t(1.57079637f))))
00446a55        var_100 = &transform_1
00446a5a        linear_interpolate_matrix(&arg1[4], &transform, var_100, var_fc_18)
00446a62        long double x87_r7_34 = fconvert.t(arg1[0x14]) + fconvert.t(arg1[0x15])
00446a65        arg1[0x14] = fconvert.s(x87_r7_34)
00446a68        long double temp5_1 = fconvert.t(1f)
00446a68        x87_r7_34 - temp5_1
00446a6e        eax_1.w = (x87_r7_34 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_34, temp5_1) ? 1 : 0) << 0xa | (x87_r7_34 == temp5_1 ? 1 : 0) << 0xe
00446a73        if ((eax_1:1.b & 0x41) == 0)
00446a7a        arg1[3] = 0xc
00446a81        arg1[0x14] = 0
00446a88        arg1[0x15] = 0x3c888889
004466fa        case 0xa
004466fa        goto label_44699c
00446aa3        case 0xb
00446aa3        arg1[2] = 0xffffffff
00446aaa        arg1[0x16].b = 1
00446aad        set_matrix_identity(&arg1[4])
00446ab2        void* ecx_26 = *arg1
00446ac4        arg1[0x10] = *(ecx_26 + 0x1888)
00446ac9        arg1[0x11] = *(ecx_26 + 0x188c)
00446acf        arg1[0x12] = *(ecx_26 + 0x1890)
00446ad2        long double x87_r7_35 = fconvert.t(arg1[0x11])
00446ad5        long double temp2_1 = fconvert.t(0f)
00446ad5        x87_r7_35 - temp2_1
00446adb        int32_t* eax_15
00446adb        eax_15.w = (x87_r7_35 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_35, temp2_1) ? 1 : 0) << 0xa | (x87_r7_35 == temp2_1 ? 1 : 0) << 0xe
00446adf        if ((1 & eax_15:1.b) != 0)
00446ae1        arg1[0x11] = 0
00446aee        look_at_point(&arg1[4], ecx_26 + 0x68)
00446af3        void* ecx_29 = arg1[1]
00446af6        eax_1.b = *(ecx_29 + 0x84)
00446afe        if (eax_1.b == 0)
00446b04        initialize_subgoldy_death(ecx_29)
00446b09        eax_1 = arg1[1]
00446b0c        ecx_29.b = *(eax_1 i+ 0x44d)
00446b14        if (ecx_29.b == 0)
00446b1a        int32_t var_fc_20 = 0xffffffff
00446b1c        var_100 = 2
00446b25        int32_t eax_16 = play_voice_manager(0x751498, 0xb, var_100, var_fc_20)
00446b2f        *(arg1[1] + 0x44d) = 1
00446b38        *(arg1[1] + 0x44c) = 1
00446b44        arg1[0x14] = fconvert.s(fconvert.t(arg1[0x15]) + fconvert.t(arg1[0x14]))
00446b4f        return eax_16
00446df1        arg1[0x14] = fconvert.s(fconvert.t(arg1[0x15]) + fconvert.t(arg1[0x14]))
00446dfe        return eax_1
