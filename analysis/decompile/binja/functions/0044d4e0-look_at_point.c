/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: look_at_point @ 0x44d4e0 */

0044d4fd        long double x87_r7_5 = fconvert.t(arg2[2]) - fconvert.t(arg1[0xe])
0044d508        float var_8 = fconvert.s(fconvert.t(arg2[1]) - fconvert.t(arg1[0xd]))
0044d50c        float var_c = fconvert.s(fconvert.t(*arg2) - fconvert.t(arg1[0xc]))
0044d51d        float var_4 = fconvert.s(x87_r7_5)
0044d529        return set_matrix_z_direction(arg1, &var_c)
