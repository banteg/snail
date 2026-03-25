/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: get_track_skirt_color @ 0x442120 */

00442142        void var_10
00442142        int32_t* eax_1 = set_color_rgba(&var_10, *(arg1 + 0x1b0140), *(arg1 + 0x1b0144), *(arg1 + 0x1b0148), 0x3ecccccd)
00442151        *arg2 = *eax_1
00442156        arg2[1] = eax_1[1]
0044215c        arg2[2] = eax_1[2]
00442163        arg2[3] = eax_1[3]
00442169        return arg2
