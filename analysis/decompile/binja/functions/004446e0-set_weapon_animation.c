/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: set_weapon_animation @ 0x4446e0 */

004446e6        if (arg3 == 0)
004447a6        *(arg1 + (*(arg1 + 0x144) << 2) + 0x11c) = arg2
004447b3        int32_t eax_8 = *(arg1 + 0x144) + 1
004447b4        *(arg1 + 0x144) = eax_8
004447ba        return eax_8
004446f1        int32_t eax_2 = arg2 << 7
00444702        int16_t* eax_3 = *(*(eax_2 + arg1 + 0x174) + 0xbc)
0044470f        *(arg1 + 0x114) = eax_3
00444715        if (arg4 != 0xffffffff)
00444717        *eax_3 = arg4.w
0044471a        char* edx_2 = *(arg1 + 0x114)
00444723        if ((*edx_2 & 8) == 0)
00444750        void* edx_3 = *(arg1 + 0x114)
00444756        *(arg1 + 0x10c) = 0
00444760        long double x87_r7_4 = fconvert.t(*(edx_3 + 0x10))
00444763        long double temp1_1 = fconvert.t(0f)
00444763        x87_r7_4 - temp1_1
00444769        long double x87_r7_5 = fconvert.t(*(edx_3 + 0x10))
0044476c        eax_3.w = (x87_r7_4 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_4, temp1_1) ? 1 : 0) << 0xa | (x87_r7_4 == temp1_1 ? 1 : 0) << 0xe | 0x3800
00444771        if ((eax_3:1.b & 1) != 0)
00444773        x87_r7_5 = fneg(x87_r7_5)
00444775        *(arg1 + 0x110) = fconvert.s(x87_r7_5)
00444725        long double x87_r7 = fconvert.t(*(edx_2 + 0x10))
00444728        long double temp2_1 = fconvert.t(0f)
00444728        x87_r7 - temp2_1
0044472e        long double x87_r7_1 = fconvert.t(*(edx_2 + 0x10))
00444731        eax_3.w = (x87_r7 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7, temp2_1) ? 1 : 0) << 0xa | (x87_r7 == temp2_1 ? 1 : 0) << 0xe | 0x3800
00444736        if ((eax_3:1.b & 1) != 0)
00444738        x87_r7_1 = fneg(x87_r7_1)
0044473a        long double x87_r7_2 = fneg(x87_r7_1)
0044473c        *(arg1 + 0x110) = fconvert.s(x87_r7_2)
00444748        *(arg1 + 0x10c) = fconvert.s(x87_r7_2 + fconvert.t(1f))
0044477b        int32_t eax_4 = *(eax_2 + arg1 + 0x174)
0044477d        *(arg1 + 0x144) = 0
00444787        *(arg1 + 0x24) = eax_4
0044478a        void* ecx = *(arg1 + 0x148)
00444794        int32_t eax_5
00444794        eax_5.b = (*(ecx + 4)).b | 0x20
00444796        *(ecx + 4) = eax_5
00444799        return eax_5
