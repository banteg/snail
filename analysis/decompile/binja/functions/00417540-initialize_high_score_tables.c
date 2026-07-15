/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: initialize_high_score_tables @ 0x417540 */

00417545        int32_t route_or_rank_index = 0
00417547        struct SubSolution (* record)[0xb] = &bank->postal_records
0041755a        initialize_high_score_entry(record, 0, 0, 0x3f800000, 0, 0, route_or_rank_index)
0041755f        route_or_rank_index += 1
00417560        record = &(*record)[1]
00417569        do while (route_or_rank_index s< 0xb)
0041756b        int32_t route_or_rank_index_1 = 0
0041756d        struct SubSolution (* record_1)[0xb] = &bank->survival_records
00417583        initialize_high_score_entry(record_1, 0, 0, 0x3f800000, 0, 1, route_or_rank_index_1)
00417588        route_or_rank_index_1 += 1
00417589        record_1 = &(*record_1)[1]
00417592        do while (route_or_rank_index_1 s< 0xb)
00417594        int32_t route_or_rank_index_2 = 0
00417596        struct SubSolution (* record_2)[0x33] = &bank->time_trial_route_records
004175ac        initialize_high_score_entry(record_2, 0, 0, 0x3f800000, 0, 2, route_or_rank_index_2)
004175b1        route_or_rank_index_2 += 1
004175b2        record_2 = &(*record_2)[1]
004175bb        do while (route_or_rank_index_2 s< 0x33)
004175d2        initialize_high_score_entry(&bank->current_result_record, 0, 0, 0x3f800000, 0, 0, 0)
004175da        return
