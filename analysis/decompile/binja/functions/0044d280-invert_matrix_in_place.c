/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: invert_matrix_in_place @ 0x44d280 */

0044d292        float var_40
0044d292        __builtin_memcpy(&var_40, transform, 0x40)
0044d2b7        float var_30
0044d2b7        transform->basis_right.y = var_30
0044d2c0        float var_3c
0044d2c0        float var_38
0044d2c0        float var_10
0044d2c0        float var_c
0044d2c0        transform->position.x = fconvert.s(fneg(fconvert.t(var_38) * fconvert.t(transform->position.z) + fconvert.t(var_c) * fconvert.t(var_3c) + fconvert.t(var_10) * fconvert.t(var_40)))
0044d2d2        float var_20
0044d2d2        transform->basis_right.z = var_20
0044d2d9        transform->basis_up.x = var_3c
0044d2ea        float var_1c
0044d2ea        transform->basis_up.z = var_1c
0044d2f2        transform->basis_forward.x = var_38
0044d2f7        float var_28
0044d2f7        transform->basis_forward.y = var_28
0044d2fd        float var_2c
0044d2fd        transform->position.y = fconvert.s(fneg(fconvert.t(var_28) * fconvert.t(transform->position.z) + fconvert.t(var_2c) * fconvert.t(var_c) + fconvert.t(var_30) * fconvert.t(var_10)))
0044d31d        float var_18
0044d31d        transform->position.z = fconvert.s(fneg(fconvert.t(var_18) * fconvert.t(transform->position.z) + fconvert.t(var_1c) * fconvert.t(var_c) + fconvert.t(var_20) * fconvert.t(var_10)))
0044d323        return
