/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_quaternion_from_axis @ 0x44d530 */

0044d538        float* var_c = arg1
0044d545        long double st0 = sine(fconvert.s(fconvert.t(arg2[3]) * fconvert.t(0.5f)))
0044d54e        *arg1 = fconvert.s(st0 * fconvert.t(*arg2))
0044d555        arg1[1] = fconvert.s(st0 * fconvert.t(arg2[1]))
0044d55b        arg1[2] = fconvert.s(st0 * fconvert.t(arg2[2]))
0044d56a        int32_t result
0044d56a        long double st0_1
0044d56a        st0_1, result = cosine(fconvert.s(fconvert.t(arg2[3]) * fconvert.t(0.5f)))
0044d56f        arg1[3] = fconvert.s(st0_1)
0044d577        return result
