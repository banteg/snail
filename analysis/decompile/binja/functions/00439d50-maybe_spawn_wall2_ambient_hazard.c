/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: maybe_spawn_wall2_ambient_hazard @ 0x439d50 */

00439d56        float lane_bits = arg1->lane_bits
00439d5c        if ((lane_bits:1.b & 0x20) != 0)
00439d62        void* ecx = data_4df904
00439d68        lane_bits.b = *(ecx + 0x74621)
00439d70        if (lane_bits.b == 0)
00439d76        lane_bits.b = arg1->tile_type
00439d7b        float vector
00439d7b        float var_10
00439d7b        if (lane_bits.b == 0xe)
00439d81        long double x87_r7_1 = float.t(*(ecx + 0x74668))
00439d87        long double temp0_1 = fconvert.t(*(ecx + 0x42fdec))
00439d87        x87_r7_1 - temp0_1
00439d8d        lane_bits.w = (x87_r7_1 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp0_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp0_1 ? 1 : 0) << 0xe
00439d92        if ((lane_bits:1.b & 1) != 0)
00439d98        void* __saved_edi_1 = &data_4a4dc8
00439da2        long double st0_1
00439da2        st0_1, lane_bits = random_float_below(100f)
00439da7        long double temp3_1 = fconvert.t(4f)
00439da7        st0_1 - temp3_1
00439db0        lane_bits.w = (st0_1 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(st0_1, temp3_1) ? 1 : 0) << 0xa | (st0_1 == temp3_1 ? 1 : 0) << 0xe
00439db5        if ((lane_bits:1.b & 1) == 0)
00439edb        ecx = data_4df904
00439dbb        float world_x = arg1->world_x
00439dbe        int32_t var_30_1 = 0
00439dc9        long double x87_r7_4 = fconvert.t(arg1->floor_height) + fconvert.t(8f)
00439dd1        float world_z = arg1->world_z
00439dd4        float world_x_1 = world_x
00439dde        float var_18_1 = fconvert.s(x87_r7_4)
00439de9        vector = arg1->lane_bits u>> 8 & 0xf
00439df5        char* __saved_edi_2 = "Wall2"
00439dff        float world_z_1 = world_z
00439e15        world_x_1 = fconvert.s(float.t(vector.q) * fconvert.t(0.5f) + fconvert.t(world_x))
00439e19        long double st0_2 = random_signed_float_below(3f)
00439e1e        ecx = data_4df904
00439e33        float edx_5 = *(ecx + 0x42fde8)
00439e39        long double x87_r7_10 = st0_2 + fconvert.t(8f) + fconvert.t(*(ecx + 0x42fdec))
00439e3f        var_10 = *(ecx + 0x42fde4)
00439e5f        vector = fconvert.s(fconvert.t(var_10) - fconvert.t(world_x_1))
00439e63        float var_18_2 = fconvert.s(fconvert.t(edx_5) - fconvert.t(var_18_1))
00439e6b        long double x87_r7_11 = x87_r7_10 - fconvert.t(world_z)
00439e73        float var_14_1 = fconvert.s(x87_r7_11)
00439e77        long double temp4_1 = fconvert.t(-4f)
00439e77        x87_r7_11 - temp4_1
00439e85        lane_bits.w = (x87_r7_11 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_11, temp4_1) ? 1 : 0) << 0xa | (x87_r7_11 == temp4_1 ? 1 : 0) << 0xe
00439e8a        if ((lane_bits:1.b & 1) != 0)
00439e90        normalize_vector(&vector)
00439eb0        void* ecx_2 = data_4df904 + 0x3cb118
00439eb6        vector = fconvert.s(fconvert.t(vector) * fconvert.t(0.400000006f))
00439ec4        float var_30_3 = fconvert.s(fconvert.t(var_18_2) * fconvert.t(0.400000006f))
00439ed2        float var_2c_2 = fconvert.s(fconvert.t(var_14_1) * fconvert.t(0.400000006f))
00439ed6        shoot_subgoldy(ecx_2, &world_x_1, &vector)
00439edb        ecx = data_4df904
00439ee1        long double x87_r7_20 = fconvert.t(arg1->world_z)
00439ee4        long double temp2_1 = fconvert.t(*(ecx + 0x4326fc))
00439ee4        x87_r7_20 - temp2_1
00439eea        lane_bits.w = (x87_r7_20 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_20, temp2_1) ? 1 : 0) << 0xa | (x87_r7_20 == temp2_1 ? 1 : 0) << 0xe
00439eef        if ((lane_bits:1.b & 1) != 0)
00439f00        return destroy_wall2_ambient_hazard(arg1)
00439f03        if (lane_bits.b == 0x16)
00439f05        long double x87_r7_21 = fconvert.t(arg1->world_z)
00439f08        long double temp1_1 = fconvert.t(*(ecx + 0x4326fc))
00439f08        x87_r7_21 - temp1_1
00439f0e        lane_bits.w = (x87_r7_21 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_21, temp1_1) ? 1 : 0) << 0xa | (x87_r7_21 == temp1_1 ? 1 : 0) << 0xe
00439f13        if ((lane_bits:1.b & 1) != 0)
00439f24        return destroy_wall2_ambient_hazard(arg1)
00439f2b        if (lane_bits.b == 0x1d || lane_bits.b == 0x1e)
00439f73        if (arg1->template_record->kind == 0x18)
00439f8c        arg1->_pad_1c[4].d = fconvert.s(fconvert.t(arg1->_pad_1c[4].d) - fconvert.t(*(ecx + 0x74650)) * fconvert.t(0.0333333351f))
00439f8f        set_color_alpha(&arg1->track_z_anchor, 0x3f4ccccd)
00439f94        ecx = data_4df904
00439fa6        int32_t* eax_7 = get_track_skirt_color(ecx + 0x74618, &var_10)
00439faf        int32_t eax_8 = get_track_cell_row_index(arg1)
00439fc2        int32_t* ecx_13 = data_4df904 + eax_8 * 0xf4 + 0x6411b8
00439fcb        *ecx_13 = *eax_7
00439fd0        ecx_13[1] = eax_7[1]
00439fd6        ecx_13[2] = eax_7[2]
00439fdd        ecx_13[3] = eax_7[3]
00439ff2        long double x87_r7_29 = fconvert.t(*(data_4df904 + 0x4326fc)) - (float.t(arg1->template_record->_pad_48) + fconvert.t(5f))
00439ff8        long double temp5_1 = fconvert.t(arg1->world_z)
00439ff8        x87_r7_29 - temp5_1
00439ffb        lane_bits.w = (x87_r7_29 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_29, temp5_1) ? 1 : 0) << 0xa | (x87_r7_29 == temp5_1 ? 1 : 0) << 0xe
0043a000        if ((lane_bits:1.b & 0x41) == 0)
0043a004        return destroy_wall2_ambient_hazard(arg1)
00439f2d        long double x87_r7_22 = fconvert.t(arg1->world_z)
00439f30        long double temp6_1 = fconvert.t(*(ecx + 0x4326fc))
00439f30        x87_r7_22 - temp6_1
00439f36        lane_bits.w = (x87_r7_22 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_22, temp6_1) ? 1 : 0) << 0xa | (x87_r7_22 == temp6_1 ? 1 : 0) << 0xe
00439f3b        if ((lane_bits:1.b & 1) != 0)
00439f4a        vector = *(ecx + 0x74670) - 5
00439f4e        long double x87_r7_23 = float.t(vector)
00439f52        long double temp7_1 = fconvert.t(arg1->world_z)
00439f52        x87_r7_23 - temp7_1
00439f55        lane_bits.w = (x87_r7_23 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_23, temp7_1) ? 1 : 0) << 0xa | (x87_r7_23 == temp7_1 ? 1 : 0) << 0xe
00439f5a        if ((lane_bits:1.b & 0x41) == 0)
00439f6b        return destroy_wall2_ambient_hazard(arg1)
0043a00d        return lane_bits
