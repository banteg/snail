/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: get_path_position_at_node @ 0x42b9c0 */

0042b9c7        struct PathTemplateSample* primary_samples = self->primary_samples
0042b9d6        long double x87_r7 = fconvert.t(local->y)
0042b9dd        int32_t eax_2 = node * 0x15
0042b9e4        float* eax_3 = primary_samples + (eax_2 << 3)
0042b9f7        long double x87_r6_4 = fconvert.t(local->x)
0042ba3f        float var_20_1 = fconvert.s(fconvert.t(fconvert.s(fconvert.t(fconvert.s(x87_r6_4 * fconvert.t(eax_3[1]))) + fconvert.t(eax_3[0xd]))) + fconvert.t(fconvert.s(x87_r7 * fconvert.t(eax_3[5]))))
0042ba49        float var_1c = fconvert.s(x87_r6_4 * fconvert.t(eax_3[2]) + fconvert.t(eax_3[0xe]) + x87_r7 * fconvert.t(eax_3[6]))
0042ba57        float var_4 = var_1c
0042ba5b        float* out_1 = out
0042ba63        *out_1 = fconvert.s(fconvert.t(fconvert.s(fconvert.t(fconvert.s(x87_r6_4 * fconvert.t(*eax_3))) + fconvert.t(eax_3[0xc]))) + fconvert.t(fconvert.s(x87_r7 * fconvert.t(*(&primary_samples->transform.basis_up + (eax_2 << 3))))))
0042ba65        out_1[1] = var_20_1
0042ba70        out_1[2] = fconvert.s(float.t(row_index) + fconvert.t(var_1c))
0042ba76        return
