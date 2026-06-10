/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: wall2_emitter_maybe_fire_sub_lazer @ 0x439d50 */

00439d56        float result = arg1->__offset(0x40).d
00439d5c        if ((result:1.b & 0x20) != 0)
00439d62        void* ecx = data_4df904
00439d68        result.b = *(ecx + 0x74621)
00439d70        if (result.b == 0)
00439d76        result.b = arg1->tile_id
00439d7b        struct Vec3 var_34
00439d7b        float var_10
00439d7b        if (result.b == 0xe)
00439d81        long double x87_r7_1 = float.t(*(ecx + 0x74668))
00439d87        long double temp0_1 = fconvert.t(*(ecx + 0x42fdec))
00439d87        x87_r7_1 - temp0_1
00439d8d        result.w = (x87_r7_1 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp0_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp0_1 ? 1 : 0) << 0xe
00439d92        if ((result:1.b & 1) != 0)
00439d98        void* __saved_edi_1 = &data_4a4dc8
00439da2        long double st0_1
00439da2        st0_1, result = random_float_below(100f)
00439da7        long double temp3_1 = fconvert.t(4f)
00439da7        st0_1 - temp3_1
00439db0        result.w = (st0_1 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(st0_1, temp3_1) ? 1 : 0) << 0xa | (st0_1 == temp3_1 ? 1 : 0) << 0xe
00439db5        if ((result:1.b & 1) == 0)
00439edb        ecx = data_4df904
00439dbb        float x = arg1->anchor_position.x
00439dbe        var_34.y = 0
00439dd1        float z = arg1->anchor_position.z
00439dd4        struct Vec3 direction
00439dd4        direction.x = x
00439de9        var_34.x = arg1->__offset(0x40).d u>> 8 & 0xf
00439df5        char* __saved_edi_2 = "Wall2"
00439dff        float z_1 = z
00439e03        direction.y = fconvert.s(fconvert.t(arg1->anchor_position.y) + fconvert.t(8f))
00439e0d        direction.z = z
00439e15        direction.x = fconvert.s(float.t(var_34.x.q) * fconvert.t(0.5f) + fconvert.t(x))
00439e19        long double st0_2 = random_signed_float_below(3f)
00439e1e        ecx = data_4df904
00439e33        float edx_5 = *(ecx + 0x42fde8)
00439e39        long double x87_r7_10 = st0_2 + fconvert.t(8f) + fconvert.t(*(ecx + 0x42fdec))
00439e3f        var_10 = *(ecx + 0x42fde4)
00439e5f        var_34.x = fconvert.s(fconvert.t(var_10) - fconvert.t(direction.x))
00439e6b        long double x87_r7_11 = x87_r7_10 - fconvert.t(direction.z)
00439e6f        var_34.y = fconvert.s(fconvert.t(edx_5) - fconvert.t(direction.y))
00439e77        long double temp4_1 = fconvert.t(-4f)
00439e77        x87_r7_11 - temp4_1
00439e81        var_34.z = fconvert.s(x87_r7_11)
00439e85        result.w = (x87_r7_11 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_11, temp4_1) ? 1 : 0) << 0xa | (x87_r7_11 == temp4_1 ? 1 : 0) << 0xe
00439e8a        if ((result:1.b & 1) != 0)
00439e90        normalize_vector(&var_34)
00439eb6        var_34.x = fconvert.s(fconvert.t(var_34.x) * fconvert.t(0.400000006f))
00439ec4        var_34.y = fconvert.s(fconvert.t(var_34.y) * fconvert.t(0.400000006f))
00439ed2        var_34.z = fconvert.s(fconvert.t(var_34.z) * fconvert.t(0.400000006f))
00439ed6        shoot_subgoldy(data_4df904 + 0x3cb118, &direction, &var_34)
00439edb        ecx = data_4df904
00439ee1        long double x87_r7_20 = fconvert.t(arg1->anchor_position.z)
00439ee4        long double temp2_1 = fconvert.t(*(ecx + 0x4326fc))
00439ee4        x87_r7_20 - temp2_1
00439eea        result.w = (x87_r7_20 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_20, temp2_1) ? 1 : 0) << 0xa | (x87_r7_20 == temp2_1 ? 1 : 0) << 0xe
00439eef        if ((result:1.b & 1) != 0)
00439f00        return destroy_sub_lazer_projectile(arg1)
00439f03        if (result.b == 0x16)
00439f05        long double x87_r7_21 = fconvert.t(arg1->anchor_position.z)
00439f08        long double temp1_1 = fconvert.t(*(ecx + 0x4326fc))
00439f08        x87_r7_21 - temp1_1
00439f0e        result.w = (x87_r7_21 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_21, temp1_1) ? 1 : 0) << 0xa | (x87_r7_21 == temp1_1 ? 1 : 0) << 0xe
00439f13        if ((result:1.b & 1) != 0)
00439f24        return destroy_sub_lazer_projectile(arg1)
00439f2b        if (result.b == 0x1d || result.b == 0x1e)
00439f73        int16_t top
00439f73        if (arg1->attachment_template_record->kind == PATH_TEMPLATE_KIND_WORM)
00439f8c        arg1->_pad_1c[4].d = fconvert.s(fconvert.t(arg1->_pad_1c[4].d) - fconvert.t(*(ecx + 0x74650)) * fconvert.t(0.0333333351f))
00439f8f        set_color_alpha(&arg1->_pad_1c[0xc], 0.800000012f)
00439f8f        top = 0xffff
00439f94        ecx = data_4df904
00439fa6        float* eax_7 = get_track_skirt_color(ecx + 0x74618, &var_10)
00439faf        int32_t eax_8 = get_track_cell_row_index(arg1)
00439fc2        char* ecx_13 = data_4df904 + eax_8 * 0xf4 + 0x6411b8
00439fc9        float edx_9 = *eax_7
00439fcb        *ecx_13 = edx_9.b
00439fcb        ecx_13[1] = edx_9:1.b
00439fcb        ecx_13[2] = edx_9:2.b
00439fcb        ecx_13[3] = edx_9:3.b
00439fcd        int32_t eax_10 = eax_7[1]
00439fd0        ecx_13[4] = eax_10.b
00439fd0        ecx_13[5] = eax_10:1.b
00439fd0        ecx_13[6] = eax_10:2.b
00439fd0        ecx_13[7] = eax_10:3.b
00439fd3        int32_t edx_10 = eax_7[2]
00439fd6        ecx_13[8] = edx_10.b
00439fd6        ecx_13[9] = edx_10:1.b
00439fd6        ecx_13[0xa] = edx_10:2.b
00439fd6        ecx_13[0xb] = edx_10:3.b
00439fd9        result = eax_7[3]
00439fdd        ecx_13[0xc] = result.b
00439fdd        ecx_13[0xd] = result:1.b
00439fdd        ecx_13[0xe] = result:2.b
00439fdd        ecx_13[0xf] = result:3.b
00439fe9        unimplemented  {fild st0, dword [ecx+0x48]}
00439fec        unimplemented  {fadd dword [0x497288]}
00439ff2        unimplemented  {fsubr st0, dword [edx+0x4326fc]}
00439ff8        long double temp5_1 = fconvert.t(arg1->anchor_position.z)
00439ff8        unimplemented  {fcomp st0, dword [esi+0x18]} f- temp5_1
00439ff8        bool c0_8 = unimplemented  {fcomp st0, dword [esi+0x18]} f< temp5_1
00439ff8        bool c2_8 = is_unordered.t(unimplemented  {fcomp st0, dword [esi+0x18]}, temp5_1)
00439ff8        bool c3_8 = unimplemented  {fcomp st0, dword [esi+0x18]} f== temp5_1
00439ff8        unimplemented  {fcomp st0, dword [esi+0x18]}
00439ffb        result.w = (c0_8 ? 1 : 0) << 8 | (c2_8 ? 1 : 0) << 0xa | (c3_8 ? 1 : 0) << 0xe | (top & 7) << 0xb
0043a000        if ((result:1.b & 0x41) == 0)
0043a004        return destroy_sub_lazer_projectile(arg1)
00439f2d        long double x87_r7_22 = fconvert.t(arg1->anchor_position.z)
00439f30        long double temp6_1 = fconvert.t(*(ecx + 0x4326fc))
00439f30        x87_r7_22 - temp6_1
00439f36        result.w = (x87_r7_22 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_22, temp6_1) ? 1 : 0) << 0xa | (x87_r7_22 == temp6_1 ? 1 : 0) << 0xe
00439f3b        if ((result:1.b & 1) != 0)
00439f4a        var_34.x = *(ecx + 0x74670) - 5
00439f4e        long double x87_r7_23 = float.t(var_34.x)
00439f52        long double temp7_1 = fconvert.t(arg1->anchor_position.z)
00439f52        x87_r7_23 - temp7_1
00439f55        result.w = (x87_r7_23 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_23, temp7_1) ? 1 : 0) << 0xa | (x87_r7_23 == temp7_1 ? 1 : 0) << 0xe
00439f5a        if ((result:1.b & 0x41) == 0)
00439f6b        return destroy_sub_lazer_projectile(arg1)
0043a00d        return result
