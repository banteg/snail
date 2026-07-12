/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: is_sub_loc_empty @ 0x439ab0 */

00439ab0        int32_t result
00439ab0        result.b = cell->tile_id
00439ac5        if (result.b != 0 && result.b != 0x1c && result.b != 0x23 && result.b != 0xe && result.b != 0x1d)
00439ac7        result.b = 0
00439ac9        return result
00439aca        result.b = 1
00439acc        return result
