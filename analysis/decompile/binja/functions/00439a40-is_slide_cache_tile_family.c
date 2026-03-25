/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: is_slide_cache_tile_family @ 0x439a40 */

00439a40        char eax = *(arg1 + 0x3c)
00439a59        if (eax != 1 && eax != 0x14 && eax != 0x15 && eax != 0x21 && eax != 0x22 && eax != 0x1b)
00439a5d        return 0
00439a60        return 1
