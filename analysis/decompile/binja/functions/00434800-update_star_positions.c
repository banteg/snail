/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_star_positions @ 0x434800 */

00434800        void* result = *(arg1 + 0x40)
00434807        int32_t i = 0
0043480b        if (result s> 0)
00434813        int32_t edx_1 = 0
00434818        void* eax_1 = *(arg1 + 0x3c) + edx_1
00434820        *(eax_1 + 0x24) = fconvert.s(fconvert.t(*(eax_1 + 0x20)) + fconvert.t(*(eax_1 + 0x24)))
00434823        int32_t eax_2 = *(arg1 + 0x3c)
00434826        long double x87_r7_3 = fconvert.t(*(edx_1 + eax_2 + 0x24))
0043482a        long double temp1_1 = fconvert.t(35f)
0043482a        x87_r7_3 - temp1_1
00434830        int32_t* esi_1 = edx_1 + eax_2 + 0x24
00434834        eax_2.w = (x87_r7_3 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_3, temp1_1) ? 1 : 0) << 0xa | (x87_r7_3 == temp1_1 ? 1 : 0) << 0xe
00434839        if ((eax_2:1.b & 0x41) == 0)
0043483f        *esi_1 = 0
0043484c        *(*(edx_1 + *(arg1 + 0x3c) + 0x1c) + 0x8c) = 0
00434856        void* eax_5 = data_4df904
0043489f        float var_20_1 = fconvert.s(fconvert.t(fconvert.s(fconvert.t(*(eax_5 + 0x6d8)) * fconvert.t(50f))) + fconvert.t(*(eax_5 + 0x6e8)))
004348b4        float var_1c_1 = fconvert.s(fconvert.t(fconvert.s(fconvert.t(*(eax_5 + 0x6dc)) * fconvert.t(50f))) + fconvert.t(*(eax_5 + 0x6ec)))
004348b8        float* eax_8 = *(edx_1 + *(arg1 + 0x3c) + 0x1c) + 0x48
004348bb        *eax_8 = fconvert.s(fconvert.t(*(eax_5 + 0x6d4)) * fconvert.t(50f) + fconvert.t(*(eax_5 + 0x6e4)))
004348c1        eax_8[1] = var_20_1
004348c8        eax_8[2] = var_1c_1
004348ce        void* eax_10 = *(arg1 + 0x3c) + edx_1
004348d6        int32_t* eax_12 = *(eax_10 + 0x1c) + 0x54
004348db        *eax_12 = *(eax_10 + 0x10)
004348e0        eax_12[1] = *(eax_10 + 0x14)
004348e6        eax_12[2] = *(eax_10 + 0x18)
004348ec        void* eax_14 = *(arg1 + 0x3c) + edx_1
00434900        float var_8_1 = fconvert.s(fconvert.t(*(eax_14 + 0x14)) * fconvert.t(10f))
00434910        float* eax_16 = *(eax_14 + 0x1c) + 0x48
00434913        float var_4_1 = fconvert.s(fconvert.t(*(eax_14 + 0x18)) * fconvert.t(10f))
00434919        *eax_16 = fconvert.s(fconvert.t(*(eax_14 + 0x10)) * fconvert.t(10f) + fconvert.t(*eax_16))
00434922        eax_16[1] = fconvert.s(fconvert.t(var_8_1) + fconvert.t(eax_16[1]))
0043492c        eax_16[2] = fconvert.s(fconvert.t(var_4_1) + fconvert.t(eax_16[2]))
00434932        void* eax_18 = *(arg1 + 0x3c) + edx_1
00434940        *(eax_18 + 0x24) = fconvert.s(fconvert.t(*(eax_18 + 0x20)) * fconvert.t(10f) + fconvert.t(*(eax_18 + 0x24)))
00434946        void* eax_20 = *(arg1 + 0x3c) + edx_1
00434948        i += 1
00434949        edx_1 += 0x2c
00434958        result = *(eax_20 + 0x1c)
00434965        *(result + 0x38) = fconvert.s((fconvert.t(*(eax_20 + 0x24)) - fconvert.t(2f)) * fconvert.t(*(eax_20 + 0x28)) * fconvert.t(0.0114285713f) * fconvert.t(arg2))
0043496b        do while (i s< *(arg1 + 0x40))
00434977        return result
