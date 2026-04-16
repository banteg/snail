/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: capture_mouse_cursor @ 0x44c3c0 */

0044c3c6        if (*arg1 == 0)
0044c3c8        long double x87_r7_1 = fconvert.t(*(arg1 + 4))
0044c3cb        *(arg1 + 0xc) = fconvert.s(x87_r7_1)
0044c3ce        long double x87_r6_1 = fconvert.t(*(arg1 + 8))
0044c3d1        *(arg1 + 0x10) = fconvert.s(x87_r6_1)
0044c3d4        int32_t eax_1
0044c3d4        int16_t x87control
0044c3d4        int16_t x87control_1
0044c3d4        eax_1, x87control_1 = __ftol(x87control, x87_r6_1)
0044c3e2        click_mouse_screen(0, __ftol(x87control_1, x87_r7_1), eax_1)
0044c3ea        arg1[0x14] = 1
0044c3ee        *arg1 = 1
0044c3f2        return
