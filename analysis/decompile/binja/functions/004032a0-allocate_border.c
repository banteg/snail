/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: allocate_border @ 0x4032a0 */

004032a0        int32_t i = 0
004032a2        int32_t* edx = &manager->borders[0].flags
004032ab        if ((edx - 0x824)->borders[0].flags == 0)
004032ce        int32_t edx_2 = i * 0x13
004032eb        (&manager->borders[0].created_time)[i + edx_2 * 0x18] = g_game_base->frame_counter
004032f1        return &manager->borders + ((i + edx_2 * 0x18) << 2)
004032ad        i += 1
004032ae        edx = &edx[0x1c9]
004032b9        do while (i s< 0x96)
004032c0        report_errorf("Run out of Borders - Increase RGAME_BORDER_NUMBER")
004032ca        return 0
