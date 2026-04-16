/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_times_up @ 0x445e20 */

00445e23        int32_t state = controller->state
00445e28        if (state == 0)
00445e28        return 
00445e2b        if (state == 1)
00445e50        long double x87_r7_2 = fconvert.t(controller->progress_step) + fconvert.t(controller->progress)
00445e53        controller->progress = fconvert.s(x87_r7_2)
00445e56        long double temp2_1 = fconvert.t(1f)
00445e56        x87_r7_2 - temp2_1
00445e5c        int32_t eax_1
00445e5c        eax_1.w = (x87_r7_2 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp2_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp2_1 ? 1 : 0) << 0xe
00445e61        if ((eax_1:1.b & 0x41) == 0)
00445e63        controller->state = 2
00445e2e        if (state == 2)
00445e30        uninit_times_up(controller)
00445e40        kill_subgoldy(data_4df904 + 0x42fd7c)
00445e45        controller->state = 0
00445e6a        return
