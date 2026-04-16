/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: linear_interpolate_matrix @ 0x44da90 */

0044da93        int32_t ebx
0044da93        int32_t var_28 = ebx
0044da94        int32_t esi
0044da94        int32_t var_2c = esi
0044da95        int32_t edi
0044da95        int32_t var_30 = edi
0044da9c        struct TransformMatrix* from_1 = from
0044da9d        struct TransformMatrix* source
0044da9d        invert_matrix_from_source(out, source)
0044daa9        multiply_matrix_in_place(out, from)
0044dab5        interpolate_matrix_rotation(out, to)
0044dabd        premultiply_matrix_in_place(out, from)
0044dac4        orthogonalize_matrix(out)
0044daef        long double x87_r6_5 = fconvert.t(1f) - fconvert.t(to)
0044db25        out->position.x = fconvert.s(fconvert.t(fconvert.s(x87_r6_5 * fconvert.t(from->position.x))) + fconvert.t(to) * fconvert.t(from->position.x))
0044db37        out->position.y = fconvert.s(fconvert.t(fconvert.s(x87_r6_5 * fconvert.t(from->position.y))) + fconvert.t(fconvert.s(fconvert.t(to) * fconvert.t(from->position.y))))
0044db42        out->position.z = fconvert.s(fconvert.t(fconvert.s(x87_r6_5 * fconvert.t(from->position.z))) + fconvert.t(fconvert.s(fconvert.t(to) * fconvert.t(from->position.z))))
0044db4a        return
