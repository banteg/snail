/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: is_ramp_cache_tile_family @ 0x439a70 */

00439a70        int32_t result
00439a70        result.b = cell->tile_id
00439aa1        if (result.b != 2 && result.b != 3 && result.b != 4 && result.b != 8 && result.b != 9 && result.b != 0xa && result.b != 0xb && result.b != 0xc && result.b != 0xd && result.b != 5 && result.b != 6 && result.b != 7)
00439aa3        result.b = 0
00439aa5        return result
00439aa6        result.b = 1
00439aa8        return result
