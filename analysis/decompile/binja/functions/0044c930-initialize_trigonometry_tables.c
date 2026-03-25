/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_trigonometry_tables @ 0x44c930 */

0044c930        int32_t ecx
0044c930        int32_t var_4 = ecx
0044c931        int32_t i = 0
0044c933        int32_t i_1 = 0
0044c937        long double x87_r7_1 = float.t(i_1)
0044c93b        i += 1
0044c941        i_1 = i
0044c94b        long double x87_r7_3 = x87_r7_1 * fconvert.t(0.000122070312f) * fconvert.t(6.28318548f)
0044c953        long double st0_1
0044c953        bool c2_1
0044c953        st0_1, c2_1 = __fcos(x87_r7_3)
0044c955        *((i << 2) + &data_777f38) = fconvert.s(st0_1)
0044c95c        long double st0_2
0044c95c        bool c2_2
0044c95c        st0_2, c2_2 = __fsin(x87_r7_3)
0044c95e        (&data_77ff88)[i] = fconvert.s(st0_2)
0044c965        do while (i s< 0x2000)
0044c96d        return initialize_math_random_table()
