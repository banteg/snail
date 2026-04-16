/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: release_mouse_cursor @ 0x44c400 */

0044c403        if (*arg1 == 1)
0044c408        int32_t edx_1 = *(arg1 + 0x10)
0044c40b        *(arg1 + 4) = *(arg1 + 0xc)
0044c40e        *(arg1 + 8) = edx_1
0044c411        *arg1 = 0
0044c414        return
