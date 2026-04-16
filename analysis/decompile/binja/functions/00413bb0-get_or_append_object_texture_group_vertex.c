/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: get_or_append_object_texture_group_vertex @ 0x413bb0 */

00413bc4        if (arg2 s>= *(arg1 + 0x2c))
00413bcb        report_errorf("VertexRef out of Range")
00413bd3        int32_t ecx = *(arg1 + 0x38)
00413bd6        int32_t eax_1 = arg2 * 3
00413bd9        int32_t esi = data_5031bc
00413bdf        void* edx = ecx + (eax_1 << 2)
00413be2        float eax_2 = *(ecx + (eax_1 << 2))
00413be9        float ecx_1 = *(edx + 4)
00413bf0        float edx_1 = *(edx + 8)
00413bf7        int32_t result = 0
00413bfb        if (esi s> 0)
00413c0c        float* ecx_2 = data_5031c4 + 4
00413c11        void* eax_3
00413c11        if ((*(arg1 + 0x10) & 4) == 0)
00413c40        long double x87_r7_4 = fconvert.t(ecx_2[-1])
00413c43        long double temp0_1 = fconvert.t(eax_2)
00413c43        x87_r7_4 - temp0_1
00413c47        eax_3.w = (x87_r7_4 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_4, temp0_1) ? 1 : 0) << 0xa | (x87_r7_4 == temp0_1 ? 1 : 0) << 0xe
00413c4c        if ((eax_3:1.b & 0x40) != 0)
00413c4e        long double x87_r7_5 = fconvert.t(*ecx_2)
00413c50        long double temp1_1 = fconvert.t(ecx_1)
00413c50        x87_r7_5 - temp1_1
00413c54        eax_3.w = (x87_r7_5 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_5, temp1_1) ? 1 : 0) << 0xa | (x87_r7_5 == temp1_1 ? 1 : 0) << 0xe
00413c59        if ((eax_3:1.b & 0x40) != 0)
00413c5b        long double x87_r7_6 = fconvert.t(ecx_2[1])
00413c5e        long double temp3_1 = fconvert.t(edx_1)
00413c5e        x87_r7_6 - temp3_1
00413c62        eax_3.w = (x87_r7_6 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_6, temp3_1) ? 1 : 0) << 0xa | (x87_r7_6 == temp3_1 ? 1 : 0) << 0xe
00413c67        if ((eax_3:1.b & 0x40) != 0)
00413c69        long double x87_r7_7 = fconvert.t(ecx_2[3])
00413c6c        long double temp5_1 = fconvert.t(arg3)
00413c6c        x87_r7_7 - temp5_1
00413c70        eax_3.w = (x87_r7_7 < temp5_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_7, temp5_1) ? 1 : 0) << 0xa | (x87_r7_7 == temp5_1 ? 1 : 0) << 0xe
00413c75        if ((eax_3:1.b & 0x40) != 0)
00413c7d        long double x87_r7_9 = fconvert.t(1f) - fconvert.t(arg4)
00413c81        long double temp6_1 = fconvert.t(ecx_2[4])
00413c81        x87_r7_9 - temp6_1
00413c84        eax_3.w = (x87_r7_9 < temp6_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_9, temp6_1) ? 1 : 0) << 0xa | (x87_r7_9 == temp6_1 ? 1 : 0) << 0xe
00413c89        if ((eax_3:1.b & 0x40) != 0)
00413d1f        return result
00413c16        if (ecx_2[5] == arg2)
00413c18        long double x87_r7_1 = fconvert.t(ecx_2[3])
00413c1b        long double temp2_1 = fconvert.t(arg3)
00413c1b        x87_r7_1 - temp2_1
00413c1f        eax_3.w = (x87_r7_1 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp2_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp2_1 ? 1 : 0) << 0xe
00413c24        if ((eax_3:1.b & 0x40) != 0)
00413c2c        long double x87_r7_3 = fconvert.t(1f) - fconvert.t(arg4)
00413c30        long double temp4_1 = fconvert.t(ecx_2[4])
00413c30        x87_r7_3 - temp4_1
00413c33        eax_3.w = (x87_r7_3 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_3, temp4_1) ? 1 : 0) << 0xa | (x87_r7_3 == temp4_1 ? 1 : 0) << 0xe
00413c38        if ((eax_3:1.b & 0x40) != 0)
00413d1f        return result
00413c8f        result += 1
00413c90        ecx_2 = &ecx_2[7]
00413c95        do while (result s< esi)
00413cae        int32_t esi_3 = result * 0x1c
00413cb1        *(esi_3 + data_5031c4) = fconvert.s(fconvert.t(eax_2))
00413cbe        *(esi_3 + data_5031c4 + 4) = fconvert.s(fconvert.t(ecx_1))
00413ccb        *(esi_3 + data_5031c4 + 8) = fconvert.s(fconvert.t(edx_1))
00413cd9        *(esi_3 + data_5031c4 + 0x10) = fconvert.s(fconvert.t(arg3))
00413ced        *(esi_3 + data_5031c4 + 0x14) = fconvert.s(fconvert.t(1f) - fconvert.t(arg4))
00413cf8        if ((*(arg1 + 0x10) & 0x10000) == 0)
00413d25        *(esi_3 + data_5031c4 + 0xc) = 0xffffffff
00413d0f        pack_color_rgba_u8(esi_3 + data_5031c4 + 0xc, *(arg1 + 0x48) + (arg2 << 4))
00413d33        *(esi_3 + data_5031c4 + 0x18) = arg2
00413d3c        int32_t eax_10 = data_5031bc + 1
00413d3f        data_5031bc = eax_10
00413d4a        return eax_10 - 1
