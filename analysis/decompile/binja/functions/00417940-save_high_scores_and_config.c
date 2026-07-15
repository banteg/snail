/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: save_high_scores_and_config @ 0x417940 */

00417940        struct SubHighScore* bank_1 = bank
00417951        struct CompactHighScoreRecord* pointer = allocate_tracked_memory(0x4c4b40, "High Score Table")
00417961        if ((save_mask & 1) != 0)
00417963        struct CompactHighScoreRecord* compact = pointer
00417965        uint32_t ebp_1 = 0
00417967        struct SubSolution (* record)[0xb] = &bank->postal_records
0041796a        bank_1 = 0xb
00417993        bool cond:0_1
00417975        if ((record - 8)->postal_records[0].active == 1)
0041797f        ebp_1 += serialize_compact_high_score_record(record, compact)
00417981        compact = pointer + ebp_1
00417988        record = &(*record)[1]
0041798e        cond:0_1 = bank_1 != 1
0041798f        bank_1 -= 1
00417993        do while (cond:0_1)
00417997        xor_decode_buffer_with_index(pointer, ebp_1)
004179a3        write_file_bytes("ScoreA.dat", pointer, ebp_1)
004179b0        if ((save_mask & 2) != 0)
004179b2        struct CompactHighScoreRecord* compact_1 = pointer
004179b4        uint32_t ebp_2 = 0
004179b6        struct SubSolution (* record_1)[0xb] = &bank->survival_records
004179bc        bank_1 = 0xb
004179e5        bool cond:1_1
004179c7        if ((record_1 - 0x15c648)->survival_records[0].active == 1)
004179d1        ebp_2 += serialize_compact_high_score_record(record_1, compact_1)
004179d3        compact_1 = pointer + ebp_2
004179da        record_1 = &(*record_1)[1]
004179e0        cond:1_1 = bank_1 != 1
004179e1        bank_1 -= 1
004179e5        do while (cond:1_1)
004179e9        xor_decode_buffer_with_index(pointer, ebp_2)
004179f5        write_file_bytes("ScoreB.dat", pointer, ebp_2)
00417a02        if ((save_mask & 8) != 0)
00417a04        struct SubSolution (* record_2)[0x33] = &bank->time_trial_route_records
00417a0a        struct CompactHighScoreRecord* compact_2 = pointer
00417a0c        uint32_t ebp_3 = 0
00417a0e        int32_t i_1 = 0x33
00417a2c        int32_t i
00417a16        if ((record_2 - 0x2b8c88)->time_trial_route_records[0].active == 1)
00417a20        ebp_3 += serialize_compact_high_score_record(record_2, compact_2)
00417a22        compact_2 = pointer + ebp_3
00417a25        record_2 = &(*record_2)[1]
00417a2b        i = i_1
00417a2b        i_1 -= 1
00417a2c        do while (i != 1)
00417a30        xor_decode_buffer_with_index(pointer, ebp_3)
00417a3c        write_file_bytes("ScoreC.dat", pointer, ebp_3)
00417a45        free_tracked_memory(pointer)
00417a66        return save_config_file("SnailMail.cfg", &g_runtime_config, 0xc4)
