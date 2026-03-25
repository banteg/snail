/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: normalize_vector_from_source @ 0x44cd20 */

0044cd29        out->x = src->x
0044cd2e        out->y = src->y
0044cd34        out->z = src->z
0044cd3d        return normalize_vector(out)
