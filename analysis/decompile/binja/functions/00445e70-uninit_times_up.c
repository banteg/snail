/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: uninit_times_up @ 0x445e70 */

00445e73        if (times_up->state != TIMES_UP_STATE_INACTIVE)
00445e78        g_game_base
00445e85        kill_border(times_up->border)
00445e8a        return
