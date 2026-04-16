/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: advance_frame_sequence @ 0x430470 */

00430471        int32_t esi = *(arg1 + 0xe0)
00430478        int32_t edi = *(arg1 + 0x5c)
0043047e        int32_t result = esi * 0x30
00430485        *(arg1 + 0xec) = *(result + edi + 0xc)
0043048b        int32_t edx_1 = *(arg1 + 0xdc)
00430494        if ((edx_1.b & 0x11) == 0)
004304a0        long double x87_r7_2 = fconvert.t(*(arg1 + 0xe8)) + fconvert.t(*(arg1 + 0xe4))
004304a6        long double temp0_1 = fconvert.t(1f)
004304a6        x87_r7_2 - temp0_1
004304ac        *(arg1 + 0xe4) = fconvert.s(x87_r7_2)
004304ac        bool c1_1 = unimplemented  {fst dword [ecx+0xe4], st0}
004304b2        result.w = (x87_r7_2 < temp0_1 ? 1 : 0) << 8 | (c1_1 ? 1 : 0) << 9 | (is_unordered.t(x87_r7_2, temp0_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp0_1 ? 1 : 0) << 0xe | 0x3800
004304b7        if ((result:1.b & 0x41) == 0)
004304c6        *(arg1 + 0xe4) = fconvert.s(x87_r7_2 - fconvert.t(1f))
004304cc        if ((edx_1.b & 8) == 0)
0043050a        int32_t esi_1 = *(arg1 + 0x54)
0043050f        *(arg1 + 0xe0) = esi + 1
00430515        if (esi + 1 == esi_1)
0043051a        if ((edx_1.b & 4) != 0)
00430522        *(arg1 + 0xe0) = esi_1 - 2
00430528        *(arg1 + 0xdc) = edx_1 | 8
00430533        if ((edx_1.b & 2) != 0)
0043053e        *(arg1 + 0xe0) = 0
00430538        *(arg1 + 0xdc) = edx_1 | 1
0043053e        *(arg1 + 0xe0) = 0
004304d4        *(arg1 + 0xe0) = esi - 1
004304da        if (esi == 0)
004304df        if ((edx_1.b & 4) != 0)
004304e4        *(arg1 + 0xe0) = 1
004304ee        *(arg1 + 0xdc) = edx_1 & 0xfffffff7
004304f9        if ((edx_1.b & 2) == 0)
00430538        *(arg1 + 0xdc) = edx_1 | 1
0043053e        *(arg1 + 0xe0) = 0
004304ff        *(arg1 + 0xe0) = *(arg1 + 0x54) - 1
00430558        result = *(*(arg1 + 0xe0) * 0x30 + edi + 0xc)
0043055c        *(arg1 + 0xec) = result
00430564        return result
