/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_axis_from_quaternion @ 0x44d580 */

0044d583        float* edi = arg2
0044d592        arg2 = fconvert.s(arccosine(edi[3]))
0044d59b        long double st0_1 = sine(arg2)
0044d5a3        *arg1 = fconvert.s(fconvert.t(*edi) / st0_1)
0044d5a5        long double st0_2 = sine(arg2)
0044d5ae        arg1[1] = fconvert.s(fconvert.t(edi[1]) / st0_2)
0044d5b1        int32_t result
0044d5b1        long double st0_3
0044d5b1        st0_3, result = sine(arg2)
0044d5bd        arg1[2] = fconvert.s(fconvert.t(edi[2]) / st0_3)
0044d5c0        long double x87_r0_7 = fconvert.t(arg2)
0044d5c6        arg1[3] = fconvert.s(x87_r0_7 + x87_r0_7)
0044d5cb        return result
