/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: add_subgoldy_score @ 0x4402c0 */

004402cb        int32_t bonus_score_1
004402cb        if (score_kind u> 5)
004402f4        report_errorf("Unknown Score Type")
004402fc        bonus_score_1 = 0
004402cb        switch (score_kind)
004402d4        case 0
004402d4        bonus_score_1 = 0xa
004402db        case 1
004402db        bonus_score_1 = 0x1f4
004402e2        case 2, 3, 4
004402e2        bonus_score_1 = 0x64
004402e9        case 5
004402e9        bonus_score_1 = bonus_score
00440307        player->score_buckets[score_kind] += bonus_score_1
0044030e        int32_t total_score = player->total_score
00440314        int32_t ecx_2 = total_score + bonus_score_1
0044031e        player->total_score = ecx_2
00440343        if (total_score s/ 0xc350 == ecx_2 s/ 0xc350)
00440343        return
00440345        int32_t visible_life_stock = player->visible_life_stock
0044034e        if (visible_life_stock s>= 9)
0044034e        return
00440351        player->visible_life_stock = visible_life_stock + 1
00440357        struct GameRoot* game_base_1 = g_game_base
0044036b        if (game_base_1->subgame.level_mode == 0 && game_base_1->fade.state == 0)
00440374        play_sound_effect(0x2c)
0044037b        return
