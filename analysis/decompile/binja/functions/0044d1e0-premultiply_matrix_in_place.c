/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: premultiply_matrix_in_place @ 0x44d1e0 */

0044d1f6        float var_40[0x10]
0044d1f6        __builtin_memcpy(&var_40, lhs, 0x40)
0044d20a        return multiply_matrices(lhs, rhs, &var_40)
