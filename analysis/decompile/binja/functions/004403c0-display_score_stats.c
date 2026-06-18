/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: display_score_stats @ 0x4403c0 */

004403c3        int32_t result = stats->total_score
004403cb        if (result == 0)
004404b0        return result
004403d1        int32_t result_1 = result
004403d2        char* var_c_1 = "\n Score Stats: %i\n"
004403ec        stats->total_score
004403f2        int32_t var_10_1 = divs.dp.d(sx.q(stats->score_buckets[SUBGOLDY_SCORE_GARBAGE] * 0x64), stats->total_score)
004403f3        char* var_14_1 = "Garbage       :%i%%\n"
0044040d        stats->total_score
00440413        int32_t var_18_1 = divs.dp.d(sx.q(stats->score_buckets[SUBGOLDY_SCORE_SLUG] * 0x64), stats->total_score)
00440414        char* var_1c_1 = "Slug          :%i%%\n"
0044042e        stats->total_score
00440434        int32_t var_20_1 = divs.dp.d(sx.q(stats->score_buckets[SUBGOLDY_SCORE_RING] * 0x64), stats->total_score)
00440435        char* var_24_1 = "Ring          :%i%%\n"
0044044f        stats->total_score
00440455        int32_t var_28_1 = divs.dp.d(sx.q(stats->score_buckets[SUBGOLDY_SCORE_PARCEL_COLLECT] * 0x64), stats->total_score)
00440456        char* var_2c_1 = "Parcel Collect:%i%%\n"
00440470        stats->total_score
00440476        int32_t var_30_1 = divs.dp.d(sx.q(stats->score_buckets[SUBGOLDY_SCORE_PARCEL_DELIVER] * 0x64), stats->total_score)
00440477        char* var_34_1 = "Parcel Deliver:%i%%\n"
00440491        stats->total_score
00440497        int32_t var_38_1 = divs.dp.d(sx.q(stats->score_buckets[SUBGOLDY_SCORE_BONUS] * 0x64), stats->total_score)
00440498        char* var_3c_1 = "Bonus         :%i%%\n"
004404a2        void* var_40_1 = &data_4a44cc
004404a7        return sub_449c00()
