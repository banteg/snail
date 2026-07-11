/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: release_mouse_cursor @ 0x44c400 */

0044c403        if (mouse->captured == 1)
0044c408        float saved_y = mouse->saved_y
0044c40b        mouse->live_x = mouse->saved_x
0044c40e        mouse->live_y = saved_y
0044c411        mouse->captured = 0
0044c414        return
