/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: activate_landscape_entry @ 0x418870 */

00418878        int32_t eax = *(data_4df904 + 0x74658)
00418884        void* esi = arg1
00418886        char var_8
00418886        if (eax == 7)
00418888        var_8 = 0
00418892        if (eax != 1)
004188c2        arg1.b = data_4df9bc.b
004188c8        arg1.b &= 1
004188cb        var_8 = arg1.b
004188a1        long double x87_r7_2 = float.t(next_math_random_value()) * fconvert.t(3.05175781e-05f)
004188a7        long double temp1_1 = fconvert.t(0.5f)
004188a7        x87_r7_2 - temp1_1
004188ad        int32_t eax_1
004188ad        eax_1.w = (x87_r7_2 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp1_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp1_1 ? 1 : 0) << 0xe
004188b2        if ((eax_1:1.b & 0x41) != 0)
004188bb        var_8 = 1
004188b4        var_8 = 0
004188d3        int32_t i = 0
004188d5        int32_t i_1 = 0
004188df        void* edi = esi + arg2 * 0x124
004188e2        int32_t* esi_1 = esi + 4
004188ec        if (*(edi + 0x6b0) != 0xffffffff)
0041890a        void* eax_4 = data_4df904 + 0x3ca25c
00418915        if (((*esi_1).w:1.b & 2) == 0)
00418926        esi_1[1] = eax_4
0041892f        esi_1[2] = *(eax_4 + 0xc)
00418932        *(eax_4 + 0xc) = &esi_1[-1]
00418935        void* eax_5 = esi_1[2]
0041893a        if (eax_5 != 0)
0041893c        *(eax_5 + 8) = &esi_1[-1]
00418941        int32_t eax_6
00418941        eax_6:1.b = (*esi_1):1.b | 2
00418944        *esi_1 = eax_6
0041891c        report_errorf("List ADDafter")
00418946        esi_1[0x1f] = 1
0041894f        int32_t eax_7
0041894f        eax_7.b = (*esi_1).b | 0x20
00418951        *esi_1 = eax_7
00418972        set_bod_object(&esi_1[-1], *(data_4df904 + *(edi + 0x6b0) * 0xbc + 0x48e2c))
00418977        void* eax_10 = esi_1[8]
00418989        esi_1[0x21] = fconvert.s(fconvert.t(*(eax_10 + 0xb8)) - fconvert.t(*(eax_10 + 0xac)))
0041898f        set_matrix_identity(&esi_1[0xd])
004189a4        esi_1[0x1b] = fconvert.s((float.t(i_1) - fconvert.t(0.5f)) * fconvert.t(esi_1[0x21]))
004189b3        esi_1[0x22] = data_4df904 + 0x42fd7c
004188f5        *esi_1 &= 0xffffffdf
004188fa        set_bod_object(&esi_1[-1], 0)
004189b9        i += 1
004189ba        esi_1 = &esi_1[0x24]
004189c3        i_1 = i
004189c7        do while (i s< 0xa)
004189e5        change_backdrop(data_4df904 + 0x4ec10, edi + 0x5a4, var_8)
004189f8        set_border_justify_centre(data_4df904 + 0xb4c, 0)
00418a08        int32_t* result = data_4df904 + 0x14
00418a0d        *result = *(edi + 0x6b4)
00418a12        result[1] = *(edi + 0x6b8)
00418a18        result[2] = *(edi + 0x6bc)
00418a20        result[3] = *(edi + 0x6c0)
00418a27        return result
