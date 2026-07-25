/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: read_left_mouse_button_state @ 0x407810 */

00407814        g_left_mouse_button_latch[slot] = 0
00407821        return g_left_mouse_button_state[slot]
