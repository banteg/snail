/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: premultiply_matrix_in_place @ 0x44d1e0 */

0044d1f6        float var_40[0x10]
0044d1f6        __builtin_memcpy(&var_40, arg1, 0x40)
0044d20a        return multiply_matrices(arg1, arg2, &var_40)
