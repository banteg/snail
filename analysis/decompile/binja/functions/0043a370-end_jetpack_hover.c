/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: end_jetpack_hover @ 0x43a370 */

0043a374        if (arg1[3] != 1)
0043a374        return 
0043a376        long double x87_r7_1 = fconvert.t(*arg1)
0043a378        long double temp0_1 = fconvert.t(0.939999998f)
0043a378        x87_r7_1 - temp0_1
0043a383        if ((((x87_r7_1 < temp0_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp0_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp0_1 ? 1 : 0) << 0xe):1.b & 1) != 0)
0043a385        *arg1 = 0x3f70a3d7
0043a38b        return
