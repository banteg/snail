/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_salt_hazard_pool @ 0x441540 */

00441540        int32_t* result = arg1 + 0x80
00441546        int32_t i_1 = 0x28
00441557        int32_t i
0044154b        *result = 0
00441551        result = &result[0x26]
00441556        i = i_1
00441556        i_1 -= 1
00441557        do while (i != 1)
00441559        return result
