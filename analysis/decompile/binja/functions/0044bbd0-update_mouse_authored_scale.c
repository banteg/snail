/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_mouse_authored_scale @ 0x44bbd0 */

0044bbd0        int32_t ecx
0044bbd0        int32_t var_4_1 = ecx
0044bbe8        int32_t result = data_777d8c
0044bbf1        float ecx_3 = data_777d94 - result
0044bbfb        data_777d6c = fconvert.s(fconvert.t(arg1) / float.t(data_777d90 - data_777d88))
0044bc09        data_777d68 = fconvert.s(fconvert.t(arg2) / float.t(ecx_3))
0044bc10        return result
