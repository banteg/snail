/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: unhighlight_border @ 0x4027e0 */

004027e0        int32_t result = *(arg1 + 0x214)
004027e6        *(arg1 + 0x20c) = 0
004027f0        *(arg1 + 0x21c) = result
004027f6        return result
