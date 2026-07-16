/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: load_high_scores_from_file @ 0x4175e0 */

004175e2        char* path = file_name
004175f6        if (archive_or_file_exists(path, 1) == 0)
004175f6        return
00417607        struct CompactHighScoreRecord* compact = load_file_bytes(path, &file_name)
00417609        char* byte_count = file_name
0041760f        int32_t ebx_1 = byte_count + compact
00417612        xor_decode_buffer_with_index(compact, byte_count)
0041761c        while (compact u< ebx_1)
0041761e        int32_t bank_selector = compact->bank_selector
00417624        if (bank_selector == 0)
00417687        deserialize_compact_high_score_record(&bank->postal_records[compact->entry_index], compact)
00417627        if (bank_selector == 1)
00417687        deserialize_compact_high_score_record(&bank->survival_records[compact->entry_index], compact)
0041762a        if (bank_selector == 2)
00417687        deserialize_compact_high_score_record(&bank->time_trial_route_records[compact->entry_index], compact)
0041768c        compact += compact->byte_count
00417695        return
