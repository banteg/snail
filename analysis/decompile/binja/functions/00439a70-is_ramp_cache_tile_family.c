/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: is_ramp_cache_tile_family @ 0x439a70 */

00439a70        char eax = *(arg1 + 0x3c)
00439aa1        if (eax != 2 && eax != 3 && eax != 4 && eax != 8 && eax != 9 && eax != 0xa && eax != 0xb && eax != 0xc && eax != 0xd && eax != 5 && eax != 6 && eax != 7)
00439aa5        return 0
00439aa8        return 1
