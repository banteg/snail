/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: premultiply_matrix_in_place @ 0x44d1e0 */

0044d1f6        struct TransformMatrix rhs
0044d1f6        __builtin_memcpy(&rhs, matrix, 0x40)
0044d200        multiply_matrices(matrix, lhs, &rhs)
0044d20a        return
