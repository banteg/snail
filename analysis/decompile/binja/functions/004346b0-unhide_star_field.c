/* tool: binary_ninja */
/* target: 37628:1:6042901297493365194 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: unhide_star_field @ 0x4346b0 */

004346b0        int32_t result = *(arg1 + 0x38)
004346b5        if (result != 0)
004346b7        result = *(arg1 + 0x40)
004346ba        int32_t edx_1 = 0
004346be        if (result s> 0)
004346c2        int32_t esi_1 = 0
004346c7        esi_1 += 0x2c
004346ca        void* eax_1 = *(*(arg1 + 0x3c) + esi_1 - 0x10)
004346d4        edx_1 += 1
004346d5        *(eax_1 + 4) |= 0x40
004346d8        result = *(arg1 + 0x40)
004346dd        do while (edx_1 s< result)
004346e1        return result
