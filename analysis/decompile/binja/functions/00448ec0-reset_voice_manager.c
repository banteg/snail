/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: reset_voice_manager @ 0x448ec0 */

00448ec0        *(arg1 + 0x180) = 0
00448eca        int32_t* result = arg1 + 0x10
00448ecd        int32_t i_1 = 0x10
00448edc        int32_t i
00448ed2        *result = 0
00448ed8        result = &result[6]
00448edb        i = i_1
00448edb        i_1 -= 1
00448edc        do while (i != 1)
00448ede        return result
