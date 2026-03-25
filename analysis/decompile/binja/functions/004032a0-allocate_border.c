/* tool: binary_ninja */
/* target: 63967:1:3859193737586600258 */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: allocate_border @ 0x4032a0 */

004032a0        int32_t i = 0
004032a2        int32_t* edx = arg1 + 0x824
004032ab        if (*edx == 0)
004032ce        int32_t edx_2 = i * 0x13
004032eb        *(arg1 + ((i + edx_2 * 0x18) << 2) + 0x820) = *(data_4df904 + 0x51c)
004032f1        return arg1 + ((i + edx_2 * 0x18) << 2) + 0x684
004032ad        i += 1
004032ae        edx = &edx[0x1c9]
004032b9        do while (i s< 0x96)
004032c0        report_errorf("Run out of Borders - Increase RGAME_BORDER_NUMBER")
004032ca        return 0
