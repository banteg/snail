/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: is_floor_cache_tile_family @ 0x439ad0 */

00439ad0        int32_t result
00439ad0        result.b = cell->tile_id
00439af1        if (result.b != 0xf && result.b != 0x17 && result.b != 0x18 && result.b != 0x19 && result.b != 0x1a && result.b != 0x10 && result.b != 0x12 && result.b != 0x13)
00439af3        result.b = 0
00439af5        return result
00439af6        result.b = 1
00439af8        return result
