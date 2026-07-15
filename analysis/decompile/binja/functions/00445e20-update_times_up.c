/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_times_up @ 0x445e20 */

00445e23        enum TimesUpState state = times_up->state
00445e28        if (state == TIMES_UP_STATE_INACTIVE)
00445e28        return
00445e2b        if (state == 1)
00445e50        long double x87_r7_2 = fconvert.t(times_up->progress_step) + fconvert.t(times_up->progress)
00445e53        times_up->progress = fconvert.s(x87_r7_2)
00445e56        long double temp2_1 = fconvert.t(1f)
00445e56        x87_r7_2 - temp2_1
00445e61        if ((((x87_r7_2 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp2_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp2_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00445e63        times_up->state = 2
00445e2e        if (state == 2)
00445e30        uninit_times_up(times_up)
00445e40        kill_subgoldy(&g_game_base->subgame.player)
00445e45        times_up->state = 0
00445e6a        return
