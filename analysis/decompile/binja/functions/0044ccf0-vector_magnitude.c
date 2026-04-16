/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: vector_magnitude @ 0x44ccf0 */

0044ccf0        long double x87_r7_2 = fconvert.t(arg1[2])
0044ccf3        long double x87_r6 = fconvert.t(arg1[1])
0044ccf6        long double x87_r5 = fconvert.t(*arg1)
0044cd00        float* var_4 = arg1
0044cd1a        return square_root(fconvert.s(x87_r5 * x87_r5 + x87_r6 * x87_r6 + x87_r7_2 * x87_r7_2))
