/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: rotate_vector_by_matrix @ 0x44cc20 */

0044cc25        float x = vector->x
0044cc2b        float y = vector->y
0044cc36        float z = vector->z
0044cc55        vector->x = fconvert.s(fconvert.t(z) * fconvert.t(matrix->basis_forward.x) + fconvert.t(y) * fconvert.t(matrix->basis_up.x) + fconvert.t(x) * fconvert.t(matrix->basis_right.x))
0044cc70        vector->y = fconvert.s(fconvert.t(z) * fconvert.t(matrix->basis_forward.y) + fconvert.t(y) * fconvert.t(matrix->basis_up.y) + fconvert.t(x) * fconvert.t(matrix->basis_right.y))
0044cc8c        vector->z = fconvert.s(fconvert.t(z) * fconvert.t(matrix->basis_forward.z) + fconvert.t(y) * fconvert.t(matrix->basis_up.z) + fconvert.t(x) * fconvert.t(matrix->basis_right.z))
0044cc92        return vector
