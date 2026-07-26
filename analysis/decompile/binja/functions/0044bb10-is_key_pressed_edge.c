/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: is_key_pressed_edge @ 0x44bb10 */

0044bb14        uint32_t key_code_1 = zx.d(key_code)
0044bb2a        if (g_keyboard_current_state[key_code_1] == 0x80 && g_keyboard_previous_state[key_code_1] == 0)
0044bb2c        uint32_t eax
0044bb2c        eax.b = 1
0044bb2e        return 1
0044bb2f        uint32_t eax_1
0044bb2f        eax_1.b = 0
0044bb31        return 0
