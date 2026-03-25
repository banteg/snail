/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: normalize_vector @ 0x44cca0 */

0044cca5        int32_t ecx
0044cca5        long double st0
0044cca5        st0, ecx = dot_vectors(vector, vector)
0044ccaa        int32_t var_8_1 = ecx
0044ccae        long double st0_1 = square_root(fconvert.s(st0))
0044ccb3        long double temp0 = fconvert.t(0f)
0044ccb3        st0_1 - temp0
0044ccc1        if ((((st0_1 < temp0 ? 1 : 0) << 8 | (is_unordered.t(st0_1, temp0) ? 1 : 0) << 0xa | (st0_1 == temp0 ? 1 : 0) << 0xe | 0x3800):1.b & 0x40) != 0)
0044cccc        return (fconvert.t(0f)).q
0044ccd3        long double x87_r6_1 = fconvert.t(1f) / st0_1
0044ccd9        vector->x = fconvert.s(x87_r6_1 * fconvert.t(vector->x))
0044cce0        vector->y = fconvert.s(x87_r6_1 * fconvert.t(vector->y))
0044cce6        vector->z = fconvert.s(x87_r6_1 * fconvert.t(vector->z))
0044ccea        return st0_1.q
