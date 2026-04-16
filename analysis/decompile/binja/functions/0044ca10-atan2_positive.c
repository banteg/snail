/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: atan2_positive @ 0x44ca10 */

0044ca10        long double x87_r7 = fconvert.t(arg1)
0044ca14        long double temp0 = fconvert.t(0f)
0044ca14        x87_r7 - temp0
0044ca1f        int32_t ecx
0044ca1f        long double x87_r7_1
0044ca1f        if ((((x87_r7 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r7, temp0) ? 1 : 0) << 0xa | (x87_r7 == temp0 ? 1 : 0) << 0xe):1.b & 0x41) != 0)
0044ca43        arg1 = fconvert.s(fneg(fconvert.t(arg1)))
0044ca47        x87_r7_1 = fconvert.t(arg2)
0044ca4b        long double temp1_1 = fconvert.t(0f)
0044ca4b        x87_r7_1 - temp1_1
0044ca56        if ((((x87_r7_1 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp1_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp1_1 ? 1 : 0) << 0xe | 0x3800):1.b & 0x41) != 0)
0044ca5f        ecx = 2
0044ca64        x87_r7_1 = fneg(x87_r7_1)
0044ca58        ecx = 3
0044ca21        x87_r7_1 = fconvert.t(arg2)
0044ca25        long double temp2_1 = fconvert.t(0f)
0044ca25        x87_r7_1 - temp2_1
0044ca30        if ((((x87_r7_1 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp2_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp2_1 ? 1 : 0) << 0xe | 0x3800):1.b & 0x41) != 0)
0044ca36        ecx = 1
0044ca64        x87_r7_1 = fneg(x87_r7_1)
0044ca32        ecx = 0
0044ca66        long double temp3 = fconvert.t(0f)
0044ca66        x87_r7_1 - temp3
0044ca71        long double result
0044ca71        if ((((x87_r7_1 < temp3 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp3) ? 1 : 0) << 0xa | (x87_r7_1 == temp3 ? 1 : 0) << 0xe | 0x3800):1.b & 0x40) == 0)
0044ca83        long double result_1
0044ca83        bool c1_1
0044ca83        result_1, c1_1 = __fpatan(float.t(1), fconvert.t(arg1) / x87_r7_1)
0044ca83        result = result_1
0044ca75        result = fconvert.t(1.57079637f)
0044ca87        if (ecx == 0)
0044caa3        return result
0044ca8c        if (ecx == 1)
0044ca94        return fconvert.t(3.14159274f) - result
0044ca98        if (ecx != 2)
0044caa1        return fneg(result)
0044caa0        return result + fconvert.t(3.14159274f)
