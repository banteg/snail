/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: is_slide_cache_tile_family @ 0x439a40 */

00439a40        int32_t result
00439a40        result.b = cell->tile_id
00439a59        if (result.b != 1 && result.b != 0x14 && result.b != 0x15 && result.b != 0x21 && result.b != 0x22 && result.b != 0x1b)
00439a5b        result.b = 0
00439a5d        return result
00439a5e        result.b = 1
00439a60        return result
