/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: hide_star_field @ 0x434670 */

00434670        int32_t result = *(arg1 + 0x38)
00434675        if (result != 0)
00434677        result = *(arg1 + 0x40)
0043467a        int32_t edx_1 = 0
0043467e        if (result s> 0)
00434682        int32_t esi_1 = 0
00434687        esi_1 += 0x2c
0043468a        void* eax_1 = *(*(arg1 + 0x3c) + esi_1 - 0x10)
00434694        edx_1 += 1
00434695        *(eax_1 + 4) &= 0xffffffbf
00434698        result = *(arg1 + 0x40)
0043469d        do while (edx_1 s< result)
004346a1        return result
