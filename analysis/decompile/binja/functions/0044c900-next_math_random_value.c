/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: next_math_random_value @ 0x44c900 */

0044c90c        int32_t temp1 = mods.dp.d(sx.q(data_77ff3c + 1), 0x1fff)
0044c90e        data_77ff3c = temp1
0044c91b        return *((temp1 << 2) + &data_787f8c)
