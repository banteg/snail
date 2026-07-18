/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: vector_magnitude @ 0x44ccf0 */

0044ccf0        long double x87_r7_2 = fconvert.t(vector->z)
0044ccf3        long double x87_r6 = fconvert.t(vector->y)
0044ccf6        long double x87_r5 = fconvert.t(vector->x)
0044cd00        struct Vec3* vector_1 = vector
0044cd1a        return square_root(fconvert.s(x87_r5 * x87_r5 + x87_r6 * x87_r6 + x87_r7_2 * x87_r7_2))
