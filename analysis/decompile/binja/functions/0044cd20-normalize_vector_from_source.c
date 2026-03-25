/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: normalize_vector_from_source @ 0x44cd20 */

0044cd29        *arg1 = *arg2
0044cd2e        arg1[1] = arg2[1]
0044cd34        arg1[2] = arg2[2]
0044cd3d        return normalize_vector(arg1)
