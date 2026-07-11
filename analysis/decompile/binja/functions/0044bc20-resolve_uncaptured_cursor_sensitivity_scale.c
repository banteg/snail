/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: resolve_uncaptured_cursor_sensitivity_scale @ 0x44bc20 */

0044bc32        if (is_mouse_captured(&g_game_base[0x290]) == 0)
0044bc4b        return (fconvert.t(scale) * fconvert.t(1.79999995f) + fconvert.t(0.699999988f)).d
0044bc3a        return (fconvert.t(1f)).d
