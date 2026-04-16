/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: calc_object_bounding_box @ 0x42fb10 */

0042fb25        int32_t* edi = arg1 + 0xb0
0042fb41        *edi = 0xd01502f9
0042fb47        int32_t* ebx = arg1 + 0xa4
0042fb55        edi[1] = 0xd01502f9
0042fb6a        edi[2] = 0xd01502f9
0042fb75        *ebx = 0x501502f9
0042fb7b        int32_t ebp = 0
0042fb7d        ebx[1] = 0x501502f9
0042fb80        *(arg1 + 0x94) = 0
0042fb86        int32_t i_1 = 0
0042fb8a        ebx[2] = 0x501502f9
0042fb8d        int32_t i = *(arg1 + 0x2c)
0042fb92        if (i s> 0)
0042fb9b        float* ecx_1 = *(arg1 + 0x38) + ebp
0042fb9d        long double x87_r7_1 = fconvert.t(*ecx_1)
0042fb9f        long double x87_r6_1 = fconvert.t(*edi)
0042fba1        x87_r6_1 - x87_r7_1
0042fba3        i.w = (x87_r6_1 < x87_r7_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_1, x87_r7_1) ? 1 : 0) << 0xa | (x87_r6_1 == x87_r7_1 ? 1 : 0) << 0xe
0042fba8        long double x87_r7_2
0042fba8        if ((i:1.b & 0x41) != 0)
0042fbb8        x87_r7_2 = fconvert.t(*ecx_1)
0042fbaa        x87_r7_2 = fconvert.t(*(arg1 + 0xb0))
0042fbb0        edi = arg1 + 0xb0
0042fbba        *edi = fconvert.s(x87_r7_2)
0042fbbc        long double x87_r7_3 = fconvert.t(*ebx)
0042fbbe        long double x87_r6_2 = fconvert.t(*ecx_1)
0042fbc0        x87_r6_2 - x87_r7_3
0042fbc2        i.w = (x87_r6_2 < x87_r7_3 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_2, x87_r7_3) ? 1 : 0) << 0xa | (x87_r6_2 == x87_r7_3 ? 1 : 0) << 0xe
0042fbc7        long double x87_r7_4
0042fbc7        if ((i:1.b & 0x41) != 0)
0042fbd7        x87_r7_4 = fconvert.t(*ecx_1)
0042fbc9        x87_r7_4 = fconvert.t(*(arg1 + 0xa4))
0042fbcf        ebx = arg1 + 0xa4
0042fbd9        *ebx = fconvert.s(x87_r7_4)
0042fbdb        long double x87_r7_5 = fconvert.t(ecx_1[1])
0042fbde        long double x87_r6_3 = fconvert.t(*(arg1 + 0xb4))
0042fbe4        x87_r6_3 - x87_r7_5
0042fbe6        i.w = (x87_r6_3 < x87_r7_5 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_3, x87_r7_5) ? 1 : 0) << 0xa | (x87_r6_3 == x87_r7_5 ? 1 : 0) << 0xe
0042fbeb        long double x87_r7_6
0042fbeb        if ((i:1.b & 0x41) != 0)
0042fbf5        x87_r7_6 = fconvert.t(ecx_1[1])
0042fbed        x87_r7_6 = fconvert.t(*(arg1 + 0xb4))
0042fbf8        *(arg1 + 0xb4) = fconvert.s(x87_r7_6)
0042fbfe        long double x87_r7_7 = fconvert.t(*(arg1 + 0xa8))
0042fc04        long double x87_r6_4 = fconvert.t(ecx_1[1])
0042fc07        x87_r6_4 - x87_r7_7
0042fc09        i.w = (x87_r6_4 < x87_r7_7 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_4, x87_r7_7) ? 1 : 0) << 0xa | (x87_r6_4 == x87_r7_7 ? 1 : 0) << 0xe
0042fc0e        long double x87_r7_8
0042fc0e        if ((i:1.b & 0x41) != 0)
0042fc18        x87_r7_8 = fconvert.t(ecx_1[1])
0042fc10        x87_r7_8 = fconvert.t(*(arg1 + 0xa8))
0042fc1b        *(arg1 + 0xa8) = fconvert.s(x87_r7_8)
0042fc21        long double x87_r7_9 = fconvert.t(ecx_1[2])
0042fc24        long double x87_r6_5 = fconvert.t(*(arg1 + 0xb8))
0042fc2a        x87_r6_5 - x87_r7_9
0042fc2c        i.w = (x87_r6_5 < x87_r7_9 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_5, x87_r7_9) ? 1 : 0) << 0xa | (x87_r6_5 == x87_r7_9 ? 1 : 0) << 0xe
0042fc31        long double x87_r7_10
0042fc31        if ((i:1.b & 0x41) != 0)
0042fc3b        x87_r7_10 = fconvert.t(ecx_1[2])
0042fc33        x87_r7_10 = fconvert.t(*(arg1 + 0xb8))
0042fc3e        *(arg1 + 0xb8) = fconvert.s(x87_r7_10)
0042fc44        long double x87_r7_11 = fconvert.t(*(arg1 + 0xac))
0042fc4a        long double x87_r6_6 = fconvert.t(ecx_1[2])
0042fc4d        x87_r6_6 - x87_r7_11
0042fc4f        i.w = (x87_r6_6 < x87_r7_11 ? 1 : 0) << 8 | (is_unordered.t(x87_r6_6, x87_r7_11) ? 1 : 0) << 0xa | (x87_r6_6 == x87_r7_11 ? 1 : 0) << 0xe
0042fc54        long double x87_r7_12
0042fc54        if ((i:1.b & 0x41) != 0)
0042fc5e        x87_r7_12 = fconvert.t(ecx_1[2])
0042fc56        x87_r7_12 = fconvert.t(*(arg1 + 0xac))
0042fc61        *(arg1 + 0xac) = fconvert.s(x87_r7_12)
0042fc67        long double st0_1 = vector_magnitude(ecx_1)
0042fc6c        long double temp0_1 = fconvert.t(*(arg1 + 0x94))
0042fc6c        st0_1 - temp0_1
0042fc72        i.w = (st0_1 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(st0_1, temp0_1) ? 1 : 0) << 0xa | (st0_1 == temp0_1 ? 1 : 0) << 0xe | 0x3800
0042fc77        if ((i:1.b & 0x41) == 0)
0042fc79        *(arg1 + 0x94) = fconvert.s(st0_1)
0042fc8a        i = i_1 + 1
0042fc8b        ebp += 0xc
0042fc90        i_1 = i
0042fc94        do while (i s< *(arg1 + 0x2c))
0042fca1        return i
