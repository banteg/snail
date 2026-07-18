/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: multiply_vector_by_matrix_copy @ 0x44cac0 */

0044cac7        float x = vector->x
0044cace        float y = vector->y
0044cad5        float z = vector->z
0044cb14        float var_8 = fconvert.s(fconvert.t(matrix->basis_forward.y) * fconvert.t(vector->z) + fconvert.t(matrix->basis_right.y) * fconvert.t(vector->x) + fconvert.t(matrix->basis_up.y) * fconvert.t(vector->y) + fconvert.t(matrix->position.y))
0044cb34        float* out_1 = out
0044cb36        float var_4 = fconvert.s(fconvert.t(matrix->basis_forward.z) * fconvert.t(vector->z) + fconvert.t(matrix->basis_right.z) * fconvert.t(vector->x) + fconvert.t(matrix->basis_up.z) * fconvert.t(vector->y) + fconvert.t(matrix->position.z))
0044cb3a        *out_1 = fconvert.s(fconvert.t(matrix->basis_forward.x) * fconvert.t(vector->z) + fconvert.t(matrix->basis_up.x) * fconvert.t(vector->y) + fconvert.t(matrix->basis_right.x) * fconvert.t(vector->x) + fconvert.t(matrix->position.x))
0044cb40        out_1[1] = var_8
0044cb47        out_1[2] = var_4
0044cb4d        return out
