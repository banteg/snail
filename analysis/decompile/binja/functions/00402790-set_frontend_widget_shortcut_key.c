/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: set_frontend_widget_shortcut_key @ 0x402790 */

00402794        *(arg1 + 0x194) = arg2
004027a0        int32_t result = *(arg1 + 0x1a0) | 0x80000
004027a5        *(arg1 + 0x1a0) = result
004027ab        return result
