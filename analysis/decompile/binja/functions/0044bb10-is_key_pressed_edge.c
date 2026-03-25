/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: is_key_pressed_edge @ 0x44bb10 */

0044bb14        uint32_t result = zx.d(arg1)
0044bb2a        if (*(result + 0x777c4c) == 0x80 && *(result + 0x777b4c) == 0)
0044bb2c        result.b = 1
0044bb2e        return result
0044bb2f        result.b = 0
0044bb31        return result
