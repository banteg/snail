/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_cutscene @ 0x4428d0 */

004428d0        void* result = data_4df904
004428dc        void* ebx = arg1
004428de        arg1.b = *(result + 0x74621)
004428e6        if (arg1.b != 0)
00442e38        return result
004428f5        update_snail_skin_transition(ebx + 0x1938)
004428fa        void* ecx_1 = *(ebx + 0x100)
00442900        long double x87_r7_1 = fconvert.t(*(ecx_1 + 0x2dc))
00442906        long double temp0_1 = fconvert.t(0f)
00442906        x87_r7_1 - temp0_1
00442911        struct TransformMatrix var_140
00442911        void to
00442911        if ((((x87_r7_1 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp0_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp0_1 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
004429ce        int16_t eax
004429ce        eax.b = *(ecx_1 + 0x41d)
004429d6        if (eax.b != 0)
004429e6        __builtin_memcpy(&var_140, ecx_1 + 0x38, 0x40)
004429f3        __builtin_memcpy(&to, ecx_1 + 0x38, 0x40)
004429f9        set_matrix_rotation_identity(&var_140)
00442a16        linear_interpolate_matrix(*(ebx + 0x100) + 0x38, &var_140, &to, 0.970000029f)
00442923        *(ecx_1 + 0x2dc) = fconvert.s(fconvert.t(*(ecx_1 + 0x2e0)) + fconvert.t(*(ecx_1 + 0x2dc)))
00442929        void* ecx_2 = *(ebx + 0x100)
0044292f        long double x87_r7_4 = fconvert.t(*(ecx_2 + 0x2dc))
00442935        long double temp1_1 = fconvert.t(1f)
00442935        x87_r7_4 - temp1_1
00442940        if ((((x87_r7_4 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_4, temp1_1) ? 1 : 0) << 0xa | (x87_r7_4 == temp1_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00442942        *(ecx_2 + 0x2dc) = 0
00442957        int32_t eax_2 = *(ebx + 0x100) + 0x38
00442960        __builtin_memcpy(&var_140, eax_2, 0x40)
0044296d        __builtin_memcpy(&to, eax_2, 0x40)
00442973        set_matrix_rotation_identity(&var_140)
00442990        long double x87_r7_8 = (fconvert.t(-0.785398185f) - fconvert.t(*(*(ebx + 0x100) + 0x2dc)) * fconvert.t(6.28318548f)) * fconvert.t(1.39999998f)
00442996        float var_15c_1 = fconvert.s(x87_r7_8)
0044299a        long double temp3_1 = fconvert.t(-6.28318548f)
0044299a        x87_r7_8 - temp3_1
004429a5        if ((((x87_r7_8 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_8, temp3_1) ? 1 : 0) << 0xa | (x87_r7_8 == temp3_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
004429a7        var_15c_1 = -6.28318548f
004429b8        rotate_matrix_world_x(&var_140, var_15c_1)
00442a16        linear_interpolate_matrix(*(ebx + 0x100) + 0x38, &var_140, &to, 0.939999998f)
00442a1b        void* eax_5 = *(ebx + 0x100)
00442a33        __builtin_memcpy(ebx + 0x38, eax_5 + 0x38, 0x40)
00442a40        *(ebx + 0x68) = *(eax_5 + 0x2964)
00442a42        int32_t edx_3 = *(eax_5 + 0x2968)
00442a45        float alpha
00442a45        __builtin_strncpy(&alpha, "333?", 4)
00442a4a        *(ebx + 0x6c) = edx_3
00442a50        *(ebx + 0x70) = *(eax_5 + 0x296c)
00442a58        __builtin_memcpy(&var_140, ebx + 0x38, 0x40)
00442a68        linear_interpolate_matrix(ebx + 0x38, &var_140, ebx + 0xc0, alpha)
00442a74        long double x87_r7_9 = fconvert.t(*(ebx + 0x4c))
00442a77        long double temp2_1 = fconvert.t(0f)
00442a77        x87_r7_9 - temp2_1
00442a7f        *(ebx + 0x68) = var_140.position.x
00442a85        *(ebx + 0x6c) = var_140.position.y
00442a8c        *(ebx + 0x70) = var_140.position.z
00442a8f        float eax_11
00442a8f        eax_11.w = (x87_r7_9 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_9, temp2_1) ? 1 : 0) << 0xa | (x87_r7_9 == temp2_1 ? 1 : 0) << 0xe
00442a94        if ((eax_11:1.b & 0x41) == 0)
00442a9e        float* var_170_3 = ebx + 0x68
00442aaa        rotate_matrix_world_y(ebx + 0x38, fconvert.s((fconvert.t(*(ebx + 0x68)) - fconvert.t(*(ebx + 0xf0))) * fconvert.t(0.800000012f)))
00442ab5        long double x87_r7_14 = fconvert.t(*(ebx + 0x15c0)) + fconvert.t(*(ebx + 0x15bc))
00442abb        long double temp4_1 = fconvert.t(1f)
00442abb        x87_r7_14 - temp4_1
00442ac1        *(ebx + 0x15bc) = fconvert.s(x87_r7_14)
00442ac1        bool c1_1 = unimplemented  {fst dword [ebx+0x15bc], st0}
00442ac7        eax_11.w = (x87_r7_14 < temp4_1 ? 1 : 0) << 8 | (c1_1 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_14, temp4_1) ? 1 : 0) << 0xa | (x87_r7_14 == temp4_1 ? 1 : 0) << 0xe | 0x3800
00442acc        if ((eax_11:1.b & 0x41) == 0)
00442ad4        *(ebx + 0x15bc) = fconvert.s(x87_r7_14 - fconvert.t(1f))
00442ae4        long double x87_r7_18 = fconvert.t(*(ebx + 0x15c8)) + fconvert.t(*(ebx + 0x15c4))
00442aea        long double temp5_1 = fconvert.t(1f)
00442aea        x87_r7_18 - temp5_1
00442af0        *(ebx + 0x15c4) = fconvert.s(x87_r7_18)
00442af0        bool c1_2 = unimplemented  {fst dword [ebx+0x15c4], st0}
00442af6        eax_11.w = (x87_r7_18 < temp5_1 ? 1 : 0) << 8 | (c1_2 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_18, temp5_1) ? 1 : 0) << 0xa | (x87_r7_18 == temp5_1 ? 1 : 0) << 0xe | 0x3800
00442afb        if ((eax_11:1.b & 0x41) == 0)
00442b03        *(ebx + 0x15c4) = fconvert.s(x87_r7_18 - fconvert.t(1f))
00442b1b        float var_40[0x10]
00442b1b        __builtin_memcpy(&var_40, ebx + 0x38, 0x40)
00442b24        void transform
00442b24        set_matrix_identity(&transform)
00442b35        void* var_170_5 = &transform
00442b4e        rotate_matrix_world_z(&transform, fconvert.s(sine(fconvert.s(fconvert.t(*(ebx + 0x15bc)) * fconvert.t(6.28318548f))) * fconvert.t(0.0174499992f)))
00442b5b        float var_80[0x10]
00442b5b        invert_matrix_from_source(&var_80, ebx + 0x38)
00442b6a        multiply_matrix_in_place(ebx + 0x38, &var_80)
00442b81        float* var_170_10 = &transform
00442b82        *(ebx + 0x6c) = fconvert.s(fconvert.t(*(ebx + 0x6c)) + fconvert.t(1.29999995f))
00442b85        multiply_matrix_in_place(ebx + 0x38, var_170_10)
00442b9c        float (* var_170_11)[0x10] = &var_40
00442b9d        *(ebx + 0x6c) = fconvert.s(fconvert.t(*(ebx + 0x6c)) - fconvert.t(1.29999995f))
00442ba0        multiply_matrix_in_place(ebx + 0x38, var_170_11)
00442bb1        struct TransformMatrix* var_170_12 = ebx + 0x38
00442bb5        long double st0_2 = sine(fconvert.s(fconvert.t(*(ebx + 0x15c4)) * fconvert.t(6.28318548f)))
00442bf7        float var_148_1 = fconvert.s(fconvert.t(fconvert.s(st0_2 * fconvert.t(*(ebx + 0x4c)))) * fconvert.t(0.0299999993f))
00442bfb        long double x87_r7_33 = st0_2 * fconvert.t(*(ebx + 0x50)) * fconvert.t(0.0299999993f)
00442c08        *(ebx + 0x68) = fconvert.s(fconvert.t(fconvert.s(fconvert.t(fconvert.s(st0_2 * fconvert.t(*(ebx + 0x48)))) * fconvert.t(0.0299999993f))) + fconvert.t(*(ebx + 0x68)))
00442c12        *(ebx + 0x6c) = fconvert.s(fconvert.t(var_148_1) + fconvert.t(*(ebx + 0x6c)))
00442c18        *(ebx + 0x70) = fconvert.s(x87_r7_33 + fconvert.t(*(ebx + 0x70)))
00442c1b        long double x87_r7_35 = fconvert.t(*(ebx + 0x192c))
00442c21        long double temp6_1 = fconvert.t(0f)
00442c21        x87_r7_35 - temp6_1
00442c27        int32_t ecx_19 = __builtin_memcpy(ebx + 0xc0, ebx + 0x38, 0x40)
00442c2e        if ((((x87_r7_35 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_35, temp6_1) ? 1 : 0) << 0xa | (x87_r7_35 == temp6_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00442c3c        int32_t var_170_14 = ecx_19
00442c42        rotate_matrix_world_y(ebx + 0x38, fconvert.s(fconvert.t(*(ebx + 0x192c)) * fconvert.t(-2.09439516f)))
00442c4d        long double x87_r7_39 = fconvert.t(*(ebx + 0x1930)) + fconvert.t(*(ebx + 0x192c))
00442c53        *(ebx + 0x192c) = fconvert.s(x87_r7_39)
00442c59        long double temp7_1 = fconvert.t(1f)
00442c59        x87_r7_39 - temp7_1
00442c64        if ((((x87_r7_39 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_39, temp7_1) ? 1 : 0) << 0xa | (x87_r7_39 == temp7_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00442c66        *(ebx + 0x192c) = 0x3f800000
00442c70        int16_t eax_12
00442c70        eax_12.b = *(ebx + 0x1934)
00442c78        if (eax_12.b == 0)
00442d65        __builtin_memcpy(ebx + 0x1218, ebx + 0x38, 0x40)
00442d74        __builtin_memcpy(ebx + 0x684, ebx + 0x38, 0x40)
00442d83        __builtin_memcpy(ebx + 0xe3c, ebx + 0x38, 0x40)
00442d92        __builtin_memcpy(ebx + 0xa60, ebx + 0x38, 0x40)
00442c8a        *(ebx + 0x1248) = fconvert.s(fconvert.t(*(ebx + 0x15b0)) + fconvert.t(*(ebx + 0x1248)))
00442c9c        *(ebx + 0x124c) = fconvert.s(fconvert.t(*(ebx + 0x15b4)) + fconvert.t(*(ebx + 0x124c)))
00442cae        *(ebx + 0x1250) = fconvert.s(fconvert.t(*(ebx + 0x15b8)) + fconvert.t(*(ebx + 0x1250)))
00442cc0        *(ebx + 0x6b4) = fconvert.s(fconvert.t(*(ebx + 0xa1c)) + fconvert.t(*(ebx + 0x6b4)))
00442cd2        *(ebx + 0x6b8) = fconvert.s(fconvert.t(*(ebx + 0xa20)) + fconvert.t(*(ebx + 0x6b8)))
00442ce4        *(ebx + 0x6bc) = fconvert.s(fconvert.t(*(ebx + 0xa24)) + fconvert.t(*(ebx + 0x6bc)))
00442cf6        *(ebx + 0xe6c) = fconvert.s(fconvert.t(*(ebx + 0x11d4)) + fconvert.t(*(ebx + 0xe6c)))
00442d08        *(ebx + 0xe70) = fconvert.s(fconvert.t(*(ebx + 0x11d8)) + fconvert.t(*(ebx + 0xe70)))
00442d1a        *(ebx + 0xe74) = fconvert.s(fconvert.t(*(ebx + 0x11dc)) + fconvert.t(*(ebx + 0xe74)))
00442d2c        *(ebx + 0xa90) = fconvert.s(fconvert.t(*(ebx + 0xdf8)) + fconvert.t(*(ebx + 0xa90)))
00442d3e        *(ebx + 0xa94) = fconvert.s(fconvert.t(*(ebx + 0xdfc)) + fconvert.t(*(ebx + 0xa94)))
00442d50        *(ebx + 0xa98) = fconvert.s(fconvert.t(*(ebx + 0xe00)) + fconvert.t(*(ebx + 0xa98)))
00442d94        void* eax_13 = *(ebx + 0x100)
00442da7        __builtin_memcpy(ebx + 0x1604, ebx + 0x38, 0x40)
00442dbc        __builtin_memcpy(ebx + 0x1684, eax_13 + 0x38, 0x40)
00442dc6        *(ebx + 0x16b4) = *(eax_13 + 0x2964)
00442dcf        *(ebx + 0x16b8) = *(eax_13 + 0x2968)
00442dd5        *(ebx + 0x16bc) = *(eax_13 + 0x296c)
00442dda        update_snail_skin(ebx)
00442dea        if (*(ebx + 0x1964) != 0)
00442df2        update_cutscene(ebx + 0x1958)
00442e01        if (*(ebx + 0x140) == 0)
00442e09        int32_t eax_17
00442e09        eax_17.b = *(*(ebx + 0x100) + 0x2d8)
00442e11        if (eax_17.b == 0)
00442e1b        dispatch_cutscene_animation(ebx, 1, 0, 0xffffffff)
00442e2c        return update_jet_particles(*(ebx + 0x100) + 0x2750)
