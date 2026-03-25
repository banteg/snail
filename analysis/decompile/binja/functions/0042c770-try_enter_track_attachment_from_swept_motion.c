/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: try_enter_track_attachment_from_swept_motion @ 0x42c770 */

0042c783        float world_x = arg8->world_x
0042c785        int32_t esi = *(arg1 + 0x44)
0042c78c        float floor_height = arg8->floor_height
0042c78f        int32_t i = esi - 1
0042c794        int32_t world_z = arg8->world_z
0042c797        float world_z_1 = world_z
0042c79b        if (esi - 1 s< 0)
0042ca8d        return world_z
0042c7ad        int32_t ebp_2 = i * 0xa8
0042c975        int32_t eax_3
0042c7b5        void* ecx_1 = *(arg1 + 0x5c) + ebp_2
0042c7b7        long double x87_r7_1 = fconvert.t(*(ecx_1 + 0x14))
0042c7ba        long double temp2_1 = fconvert.t(0f)
0042c7ba        x87_r7_1 - temp2_1
0042c7c0        eax_3.w = (x87_r7_1 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp2_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp2_1 ? 1 : 0) << 0xe
0042c7c5        if ((eax_3:1.b & 0x41) == 0)
0042c7ec        float var_1c_1 = fconvert.s(fconvert.t(world_z_1) + fconvert.t(*(ecx_1 + 0x38)))
0042c807        long double x87_r7_6 = fconvert.t(arg3) - fconvert.t(fconvert.s(fconvert.t(floor_height) + fconvert.t(*(ecx_1 + 0x34))))
0042c80b        float var_60 = fconvert.s(fconvert.t(arg2) - (fconvert.t(world_x) + fconvert.t(*(ecx_1 + 0x30))))
0042c80f        float var_44_1 = fconvert.s(x87_r7_6)
0042c826        float var_40_1 = fconvert.s(fconvert.t(arg4) - fconvert.t(var_1c_1))
0042c832        rotate_vector_by_matrix(&var_60, ecx_1 + 0x40)
0042c837        int32_t ecx_4 = *(arg1 + 0x54)
0042c83c        int32_t eax_6
0042c83c        int32_t edx_2
0042c83c        edx_2:eax_6 = sx.q(ecx_4)
0042c84b        long double x87_r7_10 = float.t(neg.d((eax_6 - edx_2) s>> 1)) - fconvert.t(0.300000012f)
0042c851        long double temp3_1 = fconvert.t(var_60)
0042c851        x87_r7_10 - temp3_1
0042c855        eax_3.w = (x87_r7_10 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_10, temp3_1) ? 1 : 0) << 0xa | (x87_r7_10 == temp3_1 ? 1 : 0) << 0xe
0042c85a        if ((eax_3:1.b & 1) != 0)
0042c862        int32_t eax_10
0042c862        int32_t edx_3
0042c862        edx_3:eax_10 = sx.q(ecx_4)
0042c86f        long double x87_r7_12 = float.t((eax_10 - edx_3) s>> 1) + fconvert.t(0.300000012f)
0042c875        long double temp4_1 = fconvert.t(var_60)
0042c875        x87_r7_12 - temp4_1
0042c879        eax_3.w = (x87_r7_12 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_12, temp4_1) ? 1 : 0) << 0xa | (x87_r7_12 == temp4_1 ? 1 : 0) << 0xe
0042c87e        if ((eax_3:1.b & 0x41) == 0)
0042c884        long double x87_r7_13 = fconvert.t(var_44_1)
0042c888        long double temp5_1 = fconvert.t(-0.20000000000000001)
0042c888        x87_r7_13 - temp5_1
0042c88e        eax_3.w = (x87_r7_13 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_13, temp5_1) ? 1 : 0) << 0xa | (x87_r7_13 == temp5_1 ? 1 : 0) << 0xe
0042c893        if ((eax_3:1.b & 1) == 0)
0042c899        long double x87_r7_14 = fconvert.t(var_40_1)
0042c89d        long double temp6_1 = fconvert.t(0f)
0042c89d        x87_r7_14 - temp6_1
0042c8a3        eax_3.w = (x87_r7_14 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_14, temp6_1) ? 1 : 0) << 0xa | (x87_r7_14 == temp6_1 ? 1 : 0) << 0xe
0042c8a8        if ((eax_3:1.b & 0x41) == 0)
0042c8ae        eax_3 = *(arg1 + 0x5c)
0042c8b1        long double x87_r7_15 = fconvert.t(var_40_1)
0042c8b5        long double temp7_1 = fconvert.t(*(eax_3 + ebp_2 + 0x8c))
0042c8b5        x87_r7_15 - temp7_1
0042c8bc        int32_t ecx_5 = eax_3 + ebp_2
0042c8bf        eax_3.w = (x87_r7_15 < temp7_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_15, temp7_1) ? 1 : 0) << 0xa | (x87_r7_15 == temp7_1 ? 1 : 0) << 0xe
0042c8c4        if ((eax_3:1.b & 1) != 0)
0042c8eb        float var_4_1 = fconvert.s(fconvert.t(world_z_1) + fconvert.t(*(ecx_5 + 0x38)))
0042c91a        float var_10_1 = fconvert.s(fconvert.t(arg4) + fconvert.t(arg7))
0042c92e        long double x87_r7_20 = fconvert.t(fconvert.s(fconvert.t(arg3) + fconvert.t(arg6))) - fconvert.t(fconvert.s(fconvert.t(floor_height) + fconvert.t(*(ecx_5 + 0x34))))
0042c932        float var_30 = fconvert.s(fconvert.t(arg5) + fconvert.t(arg2) - (fconvert.t(world_x) + fconvert.t(*(ecx_5 + 0x30))))
0042c936        float var_38_1 = fconvert.s(x87_r7_20)
0042c952        float var_28_1 = fconvert.s(fconvert.t(var_10_1) - fconvert.t(var_4_1))
0042c956        rotate_vector_by_matrix(&var_30, ecx_5 + 0x40)
0042c95b        long double x87_r7_23 = fconvert.t(var_38_1)
0042c95f        long double temp8_1 = fconvert.t(0.00100000005f)
0042c95f        x87_r7_23 - temp8_1
0042c965        eax_3.w = (x87_r7_23 < temp8_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_23, temp8_1) ? 1 : 0) << 0xa | (x87_r7_23 == temp8_1 ? 1 : 0) << 0xe
0042c96a        if ((eax_3:1.b & 0x41) != 0)
0042c98a        *(data_4df904 + 0x430199) = 0
0042c990        int32_t eax_14 = data_4df904
0042c9a2        start_squidge_y(eax_14 + uninit_thanks_screen, *(eax_14 + &data_430190))
0042c9b4        *(data_4df904 + 0x430100) = 1
0042c9c0        *(data_4df904 + 0x430104) = arg1
0042c9cc        *(data_4df904 + 0x430108) = arg8
0042c9d7        *(data_4df904 + 0x43010c) = i
0042c9e7        *(data_4df904 + &data_430110) = fconvert.s(fconvert.t(var_40_1))
0042c9f2        *(data_4df904 + 0x430114) = 0
0042ca02        *(data_4df904 + 0x42fde8) = fconvert.s(fconvert.t(var_44_1))
0042ca0d        *(data_4df904 + &data_430190) = 0
0042ca13        void* eax_19 = data_4df904
0042ca1e        *(eax_19 + 0x430138) = eax_19 + 0x42fd7c
0042ca24        int32_t eax_20 = get_track_cell_row_index(arg8)
0042ca32        void* eax_21 = data_4df904
0042ca44        *(*(eax_21 + 0x430104) + 0x98) = *(eax_21 + eax_20 * 0xf4 + 0x64118c)
0042ca4f        *(data_4df904 + 0x43011c) = 0
0042ca5b        *(data_4df904 + 0x430118) = 0
0042ca61        void* eax_23 = data_4df904
0042ca81        return update_track_attachment_follow_state(eax_23 + 0x430100, *(eax_23 + 0x430194), eax_23 + 0x42fde4, eax_23 + 0x43018c)
0042c96c        i -= 1
0042c96d        ebp_2 -= 0xa8
0042c975        do while (i s>= 0)
0042c982        return eax_3
