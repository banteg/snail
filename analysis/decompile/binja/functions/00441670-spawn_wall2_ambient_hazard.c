/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: spawn_wall2_ambient_hazard @ 0x441670 */

00441678        *(arg1 + 0x80) = 1
00441684        set_matrix_identity(arg1 + 0x38)
00441698        *(arg1 + 0x68) = *arg2
0044169d        *(arg1 + 0x6c) = arg2[1]
004416a7        *(arg1 + 0x70) = arg2[2]
004416ae        *(arg1 + 0x8c) = *arg3
004416b3        *(arg1 + 0x90) = arg3[1]
004416b6        int32_t edx_3 = arg3[2]
004416b9        *(arg1 + 0x98) = 0
004416c8        *(arg1 + 0x94) = edx_3
004416cb        void* eax_2 = *(arg1 + 0x88)
004416e2        bool cond:0 = (0x200 & *(arg1 + 4)) == 0
004416e4        *(arg1 + 0x9c) = fconvert.s(fconvert.t(*(eax_2 + 0x38)) * fconvert.t(0.00555555569f))
004416ea        if (not(cond:0))
004416f1        report_errorf("List ADDafter")
00441704        return set_matrix_z_direction(arg1 + 0x38, arg1 + 0x8c)
00441707        *(arg1 + 8) = eax_2 + 0x355bd4
0044170d        *(arg1 + 0xc) = *(eax_2 + 0x355be0)
00441710        *(eax_2 + 0x355be0) = arg1
00441713        void* eax_5 = *(arg1 + 0xc)
00441718        if (eax_5 != 0)
0044171a        *(eax_5 + 8) = arg1
00441725        *(arg1 + 4) |= 0x200
00441730        return set_matrix_z_direction(arg1 + 0x38, arg1 + 0x8c)
