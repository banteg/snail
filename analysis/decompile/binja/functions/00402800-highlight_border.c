/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: highlight_border @ 0x402800 */

00402800        int32_t result = *(arg1 + 0x218)
00402806        *(arg1 + 0x20c) = 0x3f800000
00402810        *(arg1 + 0x21c) = result
00402816        return result
