/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: is_open_neighbor_tile_family @ 0x439ab0 */

00439ab0        char eax = *(arg1 + 0x3c)
00439ac5        if (eax != 0 && eax != 0x1c && eax != 0x23 && eax != 0xe && eax != 0x1d)
00439ac9        return 0
00439acc        return 1
