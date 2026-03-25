/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: reset_tooltip @ 0x403be0 */

00403be3        int32_t eax = *(arg1 + 4)
00403be6        int32_t result = eax - 2
00403be9        if (eax == 2)
00403c0a        *(arg1 + 4) = 1
00403beb        int32_t result_1 = result
00403beb        result -= 1
00403bec        if (result_1 == 1)
00403bf1        data_4df904
00403bfe        result = kill_border(*(arg1 + 0x18))
00403c03        *(arg1 + 0x18) = 0
00403c0a        *(arg1 + 4) = 1
00403c12        return result
