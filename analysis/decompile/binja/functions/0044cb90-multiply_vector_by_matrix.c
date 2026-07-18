/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: multiply_vector_by_matrix @ 0x44cb90 */

0044cb95        float x = vector->x
0044cb9b        float y = vector->y
0044cba2        float z = vector->z
0044cbc9        vector->x = fconvert.s(fconvert.t(z) * fconvert.t(matrix.basis_forward.x) + fconvert.t(y) * fconvert.t(matrix.basis_up.x) + fconvert.t(x) * fconvert.t(matrix.basis_right.x) + fconvert.t(matrix.position.x))
0044cbeb        vector->y = fconvert.s(fconvert.t(matrix.basis_forward.y) * fconvert.t(z) + fconvert.t(matrix.basis_up.y) * fconvert.t(y) + fconvert.t(matrix.basis_right.y) * fconvert.t(x) + fconvert.t(matrix.position.y))
0044cc0e        vector->z = fconvert.s(fconvert.t(matrix.basis_forward.z) * fconvert.t(z) + fconvert.t(matrix.basis_up.z) * fconvert.t(y) + fconvert.t(matrix.basis_right.z) * fconvert.t(x) + fconvert.t(matrix.position.z))
0044cc14        return
