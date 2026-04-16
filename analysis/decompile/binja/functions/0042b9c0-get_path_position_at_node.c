/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: get_path_position_at_node @ 0x42b9c0 */

0042b9c7        int32_t ecx = *(arg1 + 0x58)
0042b9d6        long double x87_r7 = fconvert.t(arg5[1])
0042b9dd        int32_t eax_2 = arg3 * 0x15
0042b9e4        float* eax_3 = ecx + (eax_2 << 3)
0042b9f7        long double x87_r6_4 = fconvert.t(*arg5)
0042ba3f        float var_20_1 = fconvert.s(fconvert.t(fconvert.s(fconvert.t(fconvert.s(x87_r6_4 * fconvert.t(eax_3[1]))) + fconvert.t(eax_3[0xd]))) + fconvert.t(fconvert.s(x87_r7 * fconvert.t(eax_3[5]))))
0042ba49        float var_1c = fconvert.s(x87_r6_4 * fconvert.t(eax_3[2]) + fconvert.t(eax_3[0xe]) + x87_r7 * fconvert.t(eax_3[6]))
0042ba57        float var_4 = var_1c
0042ba63        *arg2 = fconvert.s(fconvert.t(fconvert.s(fconvert.t(fconvert.s(x87_r6_4 * fconvert.t(*eax_3))) + fconvert.t(eax_3[0xc]))) + fconvert.t(fconvert.s(x87_r7 * fconvert.t(*(ecx + (eax_2 << 3) + 0x10)))))
0042ba65        arg2[1] = var_20_1
0042ba68        float result = fconvert.s(float.t(arg4) + fconvert.t(var_1c))
0042ba70        arg2[2] = result
0042ba76        return result
