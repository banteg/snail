/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: is_floor_cache_tile_family @ 0x439ad0 */

00439ad0        char eax = *(arg1 + 0x3c)
00439af1        if (eax != 0xf && eax != 0x17 && eax != 0x18 && eax != 0x19 && eax != 0x1a && eax != 0x10 && eax != 0x12 && eax != 0x13)
00439af5        return 0
00439af8        return 1
