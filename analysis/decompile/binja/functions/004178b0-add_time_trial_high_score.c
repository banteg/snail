/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: add_time_trial_high_score @ 0x4178b0 */

004178c6        record->high_score_mode_tag = 2
004178cd        record->route_or_rank_index = route_index
004178d0        record->replay_cursor = 0
004178d3        if (route_active == 0)
004178d5        record->score_or_time.total_seconds = 0
004178e7        __builtin_memcpy(&bank->current_result_record, record, 0x1fac0)
004178e9        if (route_active == 0)
004178e9        return
004178f2        long double x87_r7_1 = fconvert.t(record->score_or_time.total_seconds)
00417901        void* ebp_1 = bank + route_index * 0x1fac0
00417903        long double temp1_1 = fconvert.t(*(ebp_1 + 0x2b8c90))
00417903        x87_r7_1 - temp1_1
0041790e        long double x87_r7_2
0041790e        long double temp2_1
0041790e        if ((((x87_r7_1 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp1_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp1_1 ? 1 : 0) << 0xe):1.b & 1) == 0)
00417910        x87_r7_2 = fconvert.t(*(ebp_1 + 0x2b8c90))
00417916        temp2_1 = fconvert.t(0f)
00417916        x87_r7_2 - temp2_1
00417921        if ((((x87_r7_1 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_1, temp1_1) ? 1 : 0) << 0xa | (x87_r7_1 == temp1_1 ? 1 : 0) << 0xe):1.b & 1) != 0 || (((x87_r7_2 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp2_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp2_1 ? 1 : 0) << 0xe):1.b & 0x40) != 0)
00417930        __builtin_memcpy(ebp_1 + 0x2b8c88, record, 0x1fac0)
00417932        *(ebp_1 + 0x2b8cc8) = route_index
0041793c        return
