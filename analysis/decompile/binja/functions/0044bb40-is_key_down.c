/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: is_key_down @ 0x44bb40 */

0044bb50        uint32_t result
0044bb50        result.b = *(zx.d(arg1) + 0x777c4c) == 0x80
0044bb53        return result
