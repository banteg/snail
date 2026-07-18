/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_quaternion_from_axis @ 0x44d530 */

0044d538        struct Quaternion* out_1 = out
0044d545        long double st0 = sine(fconvert.s(fconvert.t(axis->angle) * fconvert.t(0.5f)))
0044d54e        out->x = fconvert.s(st0 * fconvert.t(axis->x))
0044d555        out->y = fconvert.s(st0 * fconvert.t(axis->y))
0044d55b        out->z = fconvert.s(st0 * fconvert.t(axis->z))
0044d56f        out->w = fconvert.s(cosine(fconvert.s(fconvert.t(axis->angle) * fconvert.t(0.5f))))
0044d577        return
