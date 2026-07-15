/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: display_score_stats @ 0x4403c0 */

004403cb        if (player->total_score == 0)
004403cb        return
004403dc        player->score_buckets[0]
004403ec        player->total_score
004403fd        player->score_buckets[1]
0044040d        player->total_score
0044041e        player->score_buckets[2]
0044042e        player->total_score
0044043f        player->score_buckets[3]
0044044f        player->total_score
00440460        player->score_buckets[4]
00440470        player->total_score
00440481        player->score_buckets[5]
00440491        player->total_score
004404b0        return
