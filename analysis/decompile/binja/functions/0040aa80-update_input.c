/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_input @ 0x40aa80 */

0040aa80        int32_t result = *(arg1 + 0x34)
0040aa86        int32_t edx_1 = *(arg1 + 0xc) ^ result
0040aa8e        *(arg1 + 0xc) = result
0040aa91        *(arg1 + 4) = edx_1 & result
0040aa96        int32_t esi_3 = not.d(result)
0040aa9a        *(arg1 + 0x10) = esi_3
0040aa9f        *(arg1 + 0x34) = 0
0040aaa6        *(arg1 + 8) = esi_3 & edx_1
0040aaab        return result
