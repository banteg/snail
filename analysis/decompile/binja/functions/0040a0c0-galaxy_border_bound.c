/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: galaxy_border_bound @ 0x40a0c0 */

0040a0cc        float result
0040a0cc        long double x87_r7_1
0040a0cc        if (*(arg5 + 0x25c) != 2)
0040a14f        long double x87_r7_8 = fconvert.t(*(arg5 + 0x238))
0040a155        long double temp1_1 = fconvert.t(*arg1)
0040a155        x87_r7_8 - temp1_1
0040a157        result.w = (x87_r7_8 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_8, temp1_1) ? 1 : 0) << 0xa | (x87_r7_8 == temp1_1 ? 1 : 0) << 0xe
0040a15c        if ((result:1.b & 1) != 0)
0040a164        *arg1 = *(arg5 + 0x238)
0040a16c        x87_r7_1 = fconvert.t(*(arg5 + 0x248)) + fconvert.t(*(arg5 + 0x238))
0040a178        long double temp3_1 = fconvert.t(*arg2)
0040a178        x87_r7_1 - temp3_1
0040a17a        result.w = (x87_r7_1 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp3_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp3_1 ? 1 : 0) << 0xe | 0x3800
0040a17f        if ((result:1.b & 0x41) == 0)
0040a181        *arg2 = fconvert.s(x87_r7_1)
0040a0d8        x87_r7_1 = fconvert.t(*arg2) - fconvert.t(*arg1)
0040a0da        long double temp2_1 = fconvert.t(*(arg5 + 0x248))
0040a0da        x87_r7_1 - temp2_1
0040a0e0        result.w = (x87_r7_1 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp2_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp2_1 ? 1 : 0) << 0xe | 0x3800
0040a0e5        if ((result:1.b & 1) != 0)
0040a0f3        x87_r7_1 = fconvert.t(*arg1) - (fconvert.t(*(arg5 + 0x248)) - x87_r7_1) * fconvert.t(0.5f)
0040a0f5        *arg1 = fconvert.s(x87_r7_1)
0040a10b        *arg1 = fconvert.s((fconvert.t(*(arg5 + 0x248)) - (fconvert.t(*arg2) - x87_r7_1)) * fconvert.t(0.5f) + x87_r7_1)
0040a114        long double x87_r7_5 = fconvert.t(*(arg5 + 0x23c))
0040a11a        long double temp4 = fconvert.t(*arg3)
0040a11a        x87_r7_5 - temp4
0040a11c        result.w = (x87_r7_5 < temp4 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_5, temp4) ? 1 : 0) << 0xa | (x87_r7_5 == temp4 ? 1 : 0) << 0xe
0040a121        if ((result:1.b & 1) != 0)
0040a129        *arg3 = *(arg5 + 0x23c)
0040a131        long double x87_r7_7 = fconvert.t(*(arg5 + 0x24c)) + fconvert.t(*(arg5 + 0x23c))
0040a13d        long double temp5 = fconvert.t(*arg4)
0040a13d        x87_r7_7 - temp5
0040a13f        result.w = (x87_r7_7 < temp5 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_7, temp5) ? 1 : 0) << 0xa | (x87_r7_7 == temp5 ? 1 : 0) << 0xe | 0x3800
0040a144        if ((result:1.b & 0x41) != 0)
0040a187        return result
0040a146        *arg4 = fconvert.s(x87_r7_7)
0040a148        return result
