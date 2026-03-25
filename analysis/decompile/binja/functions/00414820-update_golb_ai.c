/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_golb_ai @ 0x414820 */

00414825        void* ebp = arg1
00414829        struct TrackRowCell* eax = *(ebp + 0x270)
0041482f        arg1.b = eax->_pad_08[1]
00414834        if (arg1.b == 0)
00414841        if (*(ebp + 0x1bc) == 1)
00414844        *(ebp + 0x1bc) = 0
00414851        return eax
00414852        int32_t eax_1 = *(ebp + 0x244)
00414858        eax = eax_1 - 1
00414859        if (eax_1 == 1)
0041485f        eax.b = *(ebp + 0x2bc)
0041486d        struct Vec3 vector_1
0041486d        if (eax.b != 1)
004148f1        *(ebp + 0x1f4) = fconvert.s(fconvert.t(*(ebp + 0x24c)) + fconvert.t(*(ebp + 0x1f4)))
004148f9        *(ebp + 0x1f8) = fconvert.s(fconvert.t(*(ebp + 0x250)) + fconvert.t(*(ebp + 0x1f8)))
00414902        *(ebp + 0x1fc) = fconvert.s(fconvert.t(*(ebp + 0x254)) + fconvert.t(*(ebp + 0x1fc)))
00414905        int32_t eax_6 = *(ebp + 0x1c0)
0041490d        if (eax_6 == 0)
0041490f        long double x87_r7_7 = fconvert.t(*(ebp + 0x1f8))
00414915        long double temp2_1 = fconvert.t(0.49000001f)
00414915        x87_r7_7 - temp2_1
0041491b        eax_6.w = (x87_r7_7 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_7, temp2_1) ? 1 : 0) << 0xa | (x87_r7_7 == temp2_1 ? 1 : 0) << 0xe
00414920        if ((eax_6:1.b & 0x41) == 0)
00414959        *(ebp + 0x250) = fconvert.s(fconvert.t(*(ebp + 0x250)) - fconvert.t(*(*(ebp + 0x270) + 0x38)) * fconvert.t(0.0170000009f))
00414922        long double x87_r7_8 = fconvert.t(*(ebp + 0x1f8))
00414928        long double temp5_1 = fconvert.t(0f)
00414928        x87_r7_8 - temp5_1
0041492e        eax_6.w = (x87_r7_8 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_8, temp5_1) ? 1 : 0) << 0xa | (x87_r7_8 == temp5_1 ? 1 : 0) << 0xe
00414933        if ((eax_6:1.b & 1) != 0)
00414959        *(ebp + 0x250) = fconvert.s(fconvert.t(*(ebp + 0x250)) - fconvert.t(*(*(ebp + 0x270) + 0x38)) * fconvert.t(0.0170000009f))
00414935        *(ebp + 0x250) = 0
00414975        if (eax_6 == 2 && *(ebp + 0x198) != 0)
00414981        long double x87_r7_13 = fconvert.t(*(ebp + 0x1b0)) + fconvert.t(*(ebp + 0x1ac))
00414987        *(ebp + 0x1ac) = fconvert.s(x87_r7_13)
0041498d        long double temp8_1 = fconvert.t(1f)
0041498d        x87_r7_13 - temp8_1
00414993        int32_t eax_8
00414993        eax_8.w = (x87_r7_13 < temp8_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_13, temp8_1) ? 1 : 0) << 0xa | (x87_r7_13 == temp8_1 ? 1 : 0) << 0xe
00414998        if ((eax_8:1.b & 0x41) == 0)
0041499a        *(ebp + 0x1ac) = 0x3f800000
004149ab        float var_70_1 = fconvert.s(normalize_vector(ebp + 0x24c))
004149c8        vector_1.x = fconvert.s(fconvert.t(*(ebp + 0x19c)) - fconvert.t(*(ebp + 0x1f4)))
004149e1        vector_1.y = fconvert.s(fconvert.t(*(ebp + 0x1a0)) - fconvert.t(*(ebp + 0x1f8)))
004149ed        vector_1.z = fconvert.s(fconvert.t(*(ebp + 0x1a4)) - fconvert.t(*(ebp + 0x1fc)))
004149f1        long double st0_2 = normalize_vector(&vector_1)
004149f6        long double temp11_1 = fconvert.t(0.400000006f)
004149f6        st0_2 - temp11_1
00414a01        if ((((st0_2 < temp11_1 ? 1 : 0) << 8 | (is_unordered.t(st0_2, temp11_1) ? 1 : 0) << 0xa | (st0_2 == temp11_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
0041525c        spawn_golb_impact_sprite(ebp, ebp + 0x1f4)
00415263        return kill_golb(ebp)
00414a09        long double x87_r7_22 = fconvert.t(*(ebp + 0x1ac))
00414a25        long double x87_r7_23 = x87_r7_22 * fconvert.t(vector_1.z)
00414a35        long double x87_r6_7 = fconvert.t(1f) - fconvert.t(*(ebp + 0x1ac)) * fconvert.t(1.5f)
00414a4c        long double x87_r6_8 = x87_r6_7 * fconvert.t(*(ebp + 0x254))
00414a5f        long double x87_r5_8 = fconvert.t(fconvert.s(x87_r6_7 * fconvert.t(*(ebp + 0x250)))) + fconvert.t(fconvert.s(fconvert.t(vector_1.y) * x87_r7_22))
00414a67        (ebp + 0x24c)->x = fconvert.s(fconvert.t(fconvert.s(x87_r6_7 * fconvert.t(*(ebp + 0x24c)))) + fconvert.t(fconvert.s(fconvert.t(vector_1.x) * x87_r7_22)))
00414a73        (ebp + 0x24c)->y = fconvert.s(x87_r5_8)
00414a80        (ebp + 0x24c)->z = fconvert.s(x87_r6_8 + x87_r7_23)
00414a83        normalize_vector(ebp + 0x24c)
00414a90        *(ebp + 0x24c) = fconvert.s(fconvert.t(var_70_1) * fconvert.t(*(ebp + 0x24c)))
00414a99        *(ebp + 0x250) = fconvert.s(fconvert.t(var_70_1) * fconvert.t(*(ebp + 0x250)))
00414aa3        *(ebp + 0x254) = fconvert.s(fconvert.t(var_70_1) * fconvert.t(*(ebp + 0x254)))
00414aa6        long double x87_r7_33 = fconvert.t(var_70_1)
00414aaa        long double temp14_1 = fconvert.t(0.100000001f)
00414aaa        x87_r7_33 - temp14_1
00414ab5        if ((((x87_r7_33 < temp14_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_33, temp14_1) ? 1 : 0) << 0xa | (x87_r7_33 == temp14_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00415263        return kill_golb(ebp)
00414ac7        long double x87_r7_34 = fconvert.t(*(ebp + 0x2e4))
00414acd        (ebp + 0x2ac)->x = *(ebp + 0x1f4)
00414ad2        float eax_14 = *(ebp + 0x1fc)
00414ad5        (ebp + 0x2ac)->y = *(ebp + 0x1f8)
00414ad8        (ebp + 0x2ac)->z = eax_14
00414adb        long double temp4_1 = fconvert.t(*(ebp + 0x2b4))
00414adb        x87_r7_34 - temp4_1
00414ae1        eax_14.w = (x87_r7_34 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_34, temp4_1) ? 1 : 0) << 0xa | (x87_r7_34 == temp4_1 ? 1 : 0) << 0xe
00414ae6        if ((eax_14:1.b & 1) != 0)
00414aec        long double x87_r7_35 = fconvert.t(*(ebp + 0x1f8))
00414af2        long double temp7_1 = fconvert.t(1f)
00414af2        x87_r7_35 - temp7_1
00414af8        eax_14.w = (x87_r7_35 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_35, temp7_1) ? 1 : 0) << 0xa | (x87_r7_35 == temp7_1 ? 1 : 0) << 0xe
00414afd        if ((eax_14:1.b & 1) != 0)
00414b03        long double x87_r7_36 = fconvert.t(*(ebp + 0x1f8))
00414b09        long double temp10_1 = fconvert.t(0f)
00414b09        x87_r7_36 - temp10_1
00414b0f        eax_14.w = (x87_r7_36 < temp10_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_36, temp10_1) ? 1 : 0) << 0xa | (x87_r7_36 == temp10_1 ? 1 : 0) << 0xe
00414b14        if ((eax_14:1.b & 0x41) == 0)
00414b22        struct TrackRowCell* edi_4 = get_track_grid_cell_at_world_position(*(ebp + 0x270), ebp + 0x2ac)
00414b29        if (edi_4->tile_type == 0x1e)
00414b32        *(ebp + 0x2e4) = *(ebp + 0x2b4)
00414b40        initialize_path_follow_golb(ebp + 0x2bc, edi_4, ebp + 0x1f4, ebp)
00414b45        long double x87_r7_37 = fconvert.t(*(ebp + 0x254))
00414b4b        long double temp16_1 = fconvert.t(1f)
00414b4b        x87_r7_37 - temp16_1
00414b51        struct TrackRowCell* eax_15
00414b51        eax_15.w = (x87_r7_37 < temp16_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_37, temp16_1) ? 1 : 0) << 0xa | (x87_r7_37 == temp16_1 ? 1 : 0) << 0xe
00414b5e        if ((eax_15:1.b & 0x41) == 0 && edi_4->__offset(0xfffffffffffffd9c).b == 0x1e)
00414b7b        *(ebp + 0x2e4) = fconvert.s(fconvert.t(*(ebp + 0x2b4)) + fconvert.t(1f))
00414b81        initialize_path_follow_golb(ebp + 0x2bc, &edi_4->_pad_00[0xfffffd60], ebp + 0x1f4, ebp)
00414892        switch (calc_path_length_z(ebp + 0x2bc, *(ebp + 0x264), ebp + 0x1f4, ebp + 0x24c))
004148c6        case 0, 2
004148c6        *(ebp + 0x2ac) = *(ebp + 0x2d4)
004148cb        *(ebp + 0x2b0) = *(ebp + 0x2d8)
004148d1        *(ebp + 0x2b4) = *(ebp + 0x2dc)
0041489b        case 1, 3
0041489b        int32_t edx_2 = *(ebp + 0x1f8)
004148a4        *(ebp + 0x2ac) = *(ebp + 0x1f4)
004148aa        int32_t ecx_2 = *(ebp + 0x1fc)
004148ad        *(ebp + 0x2b0) = edx_2
004148b0        *(ebp + 0x2b4) = ecx_2
00414b86        int32_t eax_16 = *(ebp + 0x1c0)
00414b8f        if (eax_16 == 0)
00414c8d        int32_t* ecx_19 = *(ebp + 0x248) + 0x48
00414c93        *ecx_19 = *(ebp + 0x2ac)
00414c98        ecx_19[1] = *(ebp + 0x2b0)
00414c9e        ecx_19[2] = *(ebp + 0x2b4)
00414ca3        spawn_golb_trail_sprite(ebp, ebp + 0x2ac)
00414cd0        float var_34_2 = fconvert.s(fconvert.t(*(ebp + 0x260)) * fconvert.t(0.300000012f))
00414ce5        long double x87_r7_55 = fconvert.t(*(ebp + 0x2b0)) - fconvert.t(fconvert.s(fconvert.t(*(ebp + 0x25c)) * fconvert.t(0.300000012f)))
00414ce9        float var_24 = fconvert.s(fconvert.t(*(ebp + 0x2ac)) - fconvert.t(*(ebp + 0x258)) * fconvert.t(0.300000012f))
00414d01        float var_20_1 = fconvert.s(x87_r7_55)
00414d0f        float var_1c_1 = fconvert.s(fconvert.t(*(ebp + 0x2b4)) - fconvert.t(var_34_2))
00414d13        spawn_golb_trail_sprite(ebp, &var_24)
00414d40        float var_34_3 = fconvert.s(fconvert.t(*(ebp + 0x260)) * fconvert.t(0.600000024f))
00414d55        long double x87_r7_62 = fconvert.t(*(ebp + 0x2b0)) - fconvert.t(fconvert.s(fconvert.t(*(ebp + 0x25c)) * fconvert.t(0.600000024f)))
00414d59        float var_18 = fconvert.s(fconvert.t(*(ebp + 0x2ac)) - fconvert.t(*(ebp + 0x258)) * fconvert.t(0.600000024f))
00414d73        float var_14_1 = fconvert.s(x87_r7_62)
00414d7f        float var_10_1 = fconvert.s(fconvert.t(*(ebp + 0x2b4)) - fconvert.t(var_34_3))
00414d83        spawn_golb_trail_sprite(ebp, &var_18)
00414b96        if (eax_16 == 1)
00414c75        add_vapour_point(ebp + 0x80, ebp + 0x27c)
00414b9d        if (eax_16 == 2)
00414ba9        long double x87_r7_41 = fconvert.t(*(ebp + 0x1b8)) + fconvert.t(*(ebp + 0x1b4))
00414bc0        long double temp13_1 = fconvert.t(6.28318548f)
00414bc0        x87_r7_41 - temp13_1
00414bc6        *(ebp + 0x1b4) = fconvert.s(x87_r7_41)
00414bc6        bool c1_1 = unimplemented  {fst dword [ebp+0x1b4], st0}
00414bcc        __builtin_memcpy(ebp + 0x150, ebp + 0x27c, 0x40)
00414bd3        if ((((x87_r7_41 < temp13_1 ? 1 : 0) << 8 | (c1_1 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_41, temp13_1) ? 1 : 0) << 0xa | (x87_r7_41 == temp13_1 ? 1 : 0) << 0xe | 0x3800):1.b & 0x41) == 0)
00414bdb        *(ebp + 0x1b4) = fconvert.s(x87_r7_41 - fconvert.t(6.28318548f))
00414bee        spawn_golb_smoke(ebp, ebp + 0x2ac)
00414c1b        float var_34_1 = fconvert.s(fconvert.t(*(ebp + 0x260)) * fconvert.t(0.5f))
00414c30        long double x87_r7_48 = fconvert.t(*(ebp + 0x2b0)) - fconvert.t(fconvert.s(fconvert.t(*(ebp + 0x25c)) * fconvert.t(0.5f)))
00414c34        float var_30 = fconvert.s(fconvert.t(*(ebp + 0x2ac)) - fconvert.t(*(ebp + 0x258)) * fconvert.t(0.5f))
00414c4c        float var_2c_1 = fconvert.s(x87_r7_48)
00414c58        float var_28_1 = fconvert.s(fconvert.t(*(ebp + 0x2b4)) - fconvert.t(var_34_1))
00414c5e        spawn_golb_smoke(ebp, &var_30)
00414db8        float var_50_6 = fconvert.s(fconvert.t(*(ebp + 0x2b0)) - fconvert.t(*(ebp + 0x238)))
00414dbf        long double x87_r7_70 = fconvert.t(*(ebp + 0x2b4)) - fconvert.t(*(ebp + 0x23c))
00414dc5        *(ebp + 0x258) = fconvert.s(fconvert.t(*(ebp + 0x2ac)) - fconvert.t(*(ebp + 0x234)))
00414dcb        *(ebp + 0x25c) = var_50_6
00414dd6        *(ebp + 0x260) = fconvert.s(x87_r7_70)
00414de1        if (*(ebp + 0x1c0) == 2)
00414dec        set_matrix_z_direction(ebp + 0x150, ebp + 0x258)
00414dfa        rotate_matrix_world_z(ebp + 0x150, *(ebp + 0x1b4))
00414e05        long double x87_r7_72 = fconvert.t(*(ebp + 0x26c)) + fconvert.t(*(ebp + 0x268))
00414e0d        int32_t ecx_31 = *(ebp + 0x2ac)
00414e0f        *(ebp + 0x268) = fconvert.s(x87_r7_72)
00414e15        int32_t edx_16 = *(ebp + 0x2b0)
00414e18        *(ebp + 0x234) = ecx_31
00414e1e        long double temp12_1 = fconvert.t(1f)
00414e1e        x87_r7_72 - temp12_1
00414e24        int32_t eax_28 = *(ebp + 0x2b4)
00414e27        *(ebp + 0x238) = edx_16
00414e2d        *(ebp + 0x23c) = eax_28
00414e33        eax_28.w = (x87_r7_72 < temp12_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_72, temp12_1) ? 1 : 0) << 0xa | (x87_r7_72 == temp12_1 ? 1 : 0) << 0xe
00414e38        if ((eax_28:1.b & 0x41) == 0)
00415263        return kill_golb(ebp)
00414e3e        void* ecx_32 = *(ebp + 0x278)
00414e44        long double x87_r7_73 = fconvert.t(*(ebp + 0x1fc))
00414e4a        long double temp15_1 = fconvert.t(*(ecx_32 + 0x2980))
00414e4a        x87_r7_73 - temp15_1
00414e50        eax_28.w = (x87_r7_73 < temp15_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_73, temp15_1) ? 1 : 0) << 0xa | (x87_r7_73 == temp15_1 ? 1 : 0) << 0xe
00414e55        if ((eax_28:1.b & 1) != 0)
00415263        return kill_golb(ebp)
00414e5e        long double x87_r7_75 = fconvert.t(*(ecx_32 + 0x70)) + fconvert.t(46f)
00414e64        long double temp17_1 = fconvert.t(*(ebp + 0x1fc))
00414e64        x87_r7_75 - temp17_1
00414e6a        eax_28.w = (x87_r7_75 < temp17_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_75, temp17_1) ? 1 : 0) << 0xa | (x87_r7_75 == temp17_1 ? 1 : 0) << 0xe
00414e6f        if ((eax_28:1.b & 1) != 0)
00415263        return kill_golb(ebp)
00414e7b        void* esi_7 = *(*(ebp + 0x270) + 0x359140)
00414e83        struct Vec3 vector
00414e83        if (esi_7 == 0)
00414f64        label_414f64:
00414f64        int32_t esi_8 = 0
00414f66        int32_t i = 0
00415090        while (i s< 0x760)
00414f6e        void* eax_32 = *(ebp + 0x270) + i
00414f70        int32_t ecx_37 = *(eax_32 + 0x356420)
00414f7e        if (ecx_37 == 1 || ecx_37 == 4)
00414fa7        long double x87_r7_90 = fconvert.t(*(eax_32 + 0x356410)) - fconvert.t(*(ebp + 0x2b4))
00414fae        vector.x = fconvert.s(fconvert.t(*(eax_32 + 0x356408)) - fconvert.t(*(ebp + 0x2ac)))
00414fb2        vector.y = fconvert.s(fconvert.t(*(eax_32 + 0x35640c)) - fconvert.t(*(ebp + 0x2b0)))
00414fb6        long double temp19_1 = fconvert.t(0f)
00414fb6        x87_r7_90 - temp19_1
00414fbc        bool c1_3 = unimplemented  {fst dword [esp+0x34], st0}
00414fc4        vector.z = fconvert.s(x87_r7_90)
00414fc8        float eax_33
00414fc8        eax_33.w = (x87_r7_90 < temp19_1 ? 1 : 0) << 8 | (c1_3 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_90, temp19_1) ? 1 : 0) << 0xa | (x87_r7_90 == temp19_1 ? 1 : 0) << 0xe | 0x3800
00414fcd        if ((eax_33:1.b & 1) != 0)
00414fcf        x87_r7_90 = fneg(x87_r7_90)
00414fd1        long double temp21_1 = fconvert.t(2.5f)
00414fd1        x87_r7_90 - temp21_1
00414fd7        eax_33.w = (x87_r7_90 < temp21_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_90, temp21_1) ? 1 : 0) << 0xa | (x87_r7_90 == temp21_1 ? 1 : 0) << 0xe
00414fdc        if ((eax_33:1.b & 1) != 0)
00414fe6        long double st0_5 = normalize_vector(&vector)
00414feb        long double temp22_1 = fconvert.t(2.5f)
00414feb        st0_5 - temp22_1
00414ff6        if ((((st0_5 < temp22_1 ? 1 : 0) << 8 | (is_unordered.t(st0_5, temp22_1) ? 1 : 0) << 0xa | (st0_5 == temp22_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
00415002        *(ebp + 0x2bc) = 0
0041500e        float var_70_2 = fconvert.s(normalize_vector(ebp + 0x24c))
00415016        vector.y = 0
0041501e        normalize_vector(&vector)
00415033        vector_1.y = 0
00415041        vector_1.x = fconvert.s(fneg(fconvert.t(var_70_2) * fconvert.t(vector.x)))
00415049        long double x87_r7_99 = fconvert.t(var_70_2) * fconvert.t(vector.z)
00415051        *(ebp + 0x24c) = vector_1.x
00415055        vector_1.z = fconvert.s(fneg(x87_r7_99))
00415059        float z = vector_1.z
0041505d        *(ebp + 0x250) = 0
00415060        *(ebp + 0x254) = z
00415063        int32_t eax_36 = *(ebp + 0x1c0)
0041506c        if (eax_36 == 1)
00415173        kill_golb(ebp)
0041517b        spawn_golb_impact_sprite(ebp, ebp + 0x2ac)
004151aa        return hit_slug_hazard(*(ebp + 0x270) + esi_8 * 0xec + 0x3563a0, 2)
00415075        if (eax_36 == 2)
004151ad        kill_golb(ebp)
004151b5        spawn_golb_impact_sprite(ebp, ebp + 0x2ac)
004151e4        return hit_slug_hazard(*(ebp + 0x270) + esi_8 * 0xec + 0x3563a0, 4)
0041507d        if (eax_36 == 0)
004151e5        eax_36.b = *(ebp + 0x1bd)
004151ed        if (eax_36.b != 0)
00415200        kill_golb(ebp)
00415214        return spawn_golb_impact_sprite(ebp, ebp + 0x2ac)
004151f0        *(ebp + 0x1bd) = 1
004151fd        return eax_36
00415083        i += 0xec
00415089        esi_8 += 1
0041521c        eax = get_track_grid_cell_at_world_position(*(ebp + 0x270), ebp + 0x2ac)
00415225        if (eax->tile_type == 0xe)
0041522a        long double x87_r7_110 = fconvert.t(*(ebp + 0x2b4)) - fconvert.t(1f)
00415230        int32_t ecx_59 = *(ebp + 0x2ac)
00415232        int32_t edx_25 = *(ebp + 0x2b0)
00415237        int32_t var_54_10 = ecx_59
0041523b        int32_t var_50_10 = edx_25
0041523f        int32_t var_c = ecx_59
00415251        int32_t var_8_1 = edx_25
00415255        float var_4_1 = fconvert.s(x87_r7_110)
0041525c        spawn_golb_impact_sprite(ebp, &var_c)
00415263        return kill_golb(ebp)
00414e90        while (true)
00414e90        if (*(esi_7 + 0x84) == 1)
00414eb0        long double x87_r7_81 = fconvert.t(*(esi_7 + 0x70)) - fconvert.t(*(ebp + 0x2b4))
00414eb7        vector.x = fconvert.s(fconvert.t(*(esi_7 + 0x68)) - fconvert.t(*(ebp + 0x2ac)))
00414ebb        vector.y = fconvert.s(fconvert.t(*(esi_7 + 0x6c)) - fconvert.t(*(ebp + 0x2b0)))
00414ebf        long double temp18_1 = fconvert.t(0f)
00414ebf        x87_r7_81 - temp18_1
00414ec5        bool c1_2 = unimplemented  {fst dword [esp+0x34], st0}
00414ecd        vector.z = fconvert.s(x87_r7_81)
00414ed1        float eax_29
00414ed1        eax_29.w = (x87_r7_81 < temp18_1 ? 1 : 0) << 8 | (c1_2 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_81, temp18_1) ? 1 : 0) << 0xa | (x87_r7_81 == temp18_1 ? 1 : 0) << 0xe | 0x3800
00414ed6        if ((eax_29:1.b & 1) != 0)
00414ed8        x87_r7_81 = fneg(x87_r7_81)
00414eda        long double temp20_1 = fconvert.t(3f)
00414eda        x87_r7_81 - temp20_1
00414ee0        eax_29.w = (x87_r7_81 < temp20_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_81, temp20_1) ? 1 : 0) << 0xa | (x87_r7_81 == temp20_1 ? 1 : 0) << 0xe
00414ee5        if ((eax_29:1.b & 1) != 0)
00414eeb        long double st0_4 = normalize_vector(&vector)
00414ef6        long double x87_r6_29 = fconvert.t(*(esi_7 + 0x9c)) + fconvert.t(0.49000001f)
00414efe        st0_4 - x87_r6_29
00414f05        if ((((st0_4 < x87_r6_29 ? 1 : 0) << 8 | (is_unordered.t(st0_4, x87_r6_29) ? 1 : 0) << 0xa | (st0_4 == x87_r6_29 ? 1 : 0) << 0xe):1.b & 1) != 0)
00414f07        *(esi_7 + 0x84) = 2
00414f0d        long double x87_r7_84 = fconvert.t(vector.x)
00414f11        long double temp23_1 = fconvert.t(0f)
00414f11        x87_r7_84 - temp23_1
00414f1c        if ((((x87_r7_84 < temp23_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_84, temp23_1) ? 1 : 0) << 0xa | (x87_r7_84 == temp23_1 ? 1 : 0) << 0xe):1.b & 1) == 0)
00414f30        *(esi_7 + 0x88) = 1
00414f1e        *(esi_7 + 0x88) = 2
00414f40        add_subgoldy_score(*(ebp + 0x278), 0, 0)
00414f4b        if (*(ebp + 0x1c0) != 1)
0041509d        kill_golb(ebp)
004150a5        eax = spawn_golb_impact_sprite(ebp, ebp + 0x2ac)
004150b1        if (*(ebp + 0x1c0) == 2)
004150bd        void* i_1 = *(*(ebp + 0x270) + 0x359140)
004150c5        if (i_1 != 0)
004150d1        if (*(i_1 + 0x84) == 1)
004150f8        vector.x = fconvert.s(fconvert.t(*(i_1 + 0x68)) - fconvert.t(*(ebp + 0x2ac)))
004150fc        vector.y = fconvert.s(fconvert.t(*(i_1 + 0x6c)) - fconvert.t(*(ebp + 0x2b0)))
0041510c        vector.z = fconvert.s(fconvert.t(*(i_1 + 0x70)) - fconvert.t(*(ebp + 0x2b4)))
00415110        long double st0_8
00415110        st0_8, eax = normalize_vector(&vector)
00415115        long double temp24_1 = fconvert.t(3f)
00415115        st0_8 - temp24_1
0041511b        eax.w = (st0_8 < temp24_1 ? 1 : 0) << 8 | (is_unordered.t(st0_8, temp24_1) ? 1 : 0) << 0xa | (st0_8 == temp24_1 ? 1 : 0) << 0xe
00415120        if ((eax:1.b & 1) != 0)
00415127        *(i_1 + 0x84) = 2
0041512d        long double x87_r7_108 = fconvert.t(vector.x)
00415131        long double temp25_1 = fconvert.t(0f)
00415131        x87_r7_108 - temp25_1
00415137        eax.w = (x87_r7_108 < temp25_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_108, temp25_1) ? 1 : 0) << 0xa | (x87_r7_108 == temp25_1 ? 1 : 0) << 0xe
0041513c        if ((eax:1.b & 1) == 0)
00415146        *(i_1 + 0x88) = 1
0041513e        *(i_1 + 0x88) = 2
00415156        eax = add_subgoldy_score(*(ebp + 0x278), 0, 0)
0041515b        i_1 = *(i_1 + 0x80)
00415163        do while (i_1 != 0)
00415170        return eax
004150b1        break
00414f56        esi_7 = *(esi_7 + 0x80)
00414f5e        if (esi_7 == 0)
00414f5e        goto label_414f64
0041526f        return eax
