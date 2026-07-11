/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: capture_mouse_cursor @ 0x44c3c0 */

0044c3c6        if (mouse->captured == 0)
0044c3c8        long double x87_r7_1 = fconvert.t(mouse->live_x)
0044c3cb        mouse->saved_x = fconvert.s(x87_r7_1)
0044c3ce        long double x87_r6_1 = fconvert.t(mouse->live_y)
0044c3d1        mouse->saved_y = fconvert.s(x87_r6_1)
0044c3d4        int32_t eax_1
0044c3d4        int16_t x87control
0044c3d4        int16_t x87control_1
0044c3d4        eax_1, x87control_1 = ftol(x87control, x87_r6_1)
0044c3e2        click_mouse_screen(0, ftol(x87control_1, x87_r7_1), eax_1)
0044c3ea        mouse->suppress_next_draw = 1
0044c3ee        mouse->captured = 1
0044c3f2        return
