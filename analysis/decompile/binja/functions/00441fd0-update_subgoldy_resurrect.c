/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_subgoldy_resurrect @ 0x441fd0 */

00441fd3        player->velocity.z = 0f
00441fe7        if (g_game_base->fade.state == 0)
00441fef        long double x87_r7_2 = fconvert.t(player->resurrect_progress_step) + fconvert.t(player->resurrect_progress)
00441ff5        player->resurrect_progress = fconvert.s(x87_r7_2)
00441ffb        long double temp1_1 = fconvert.t(1f)
00441ffb        x87_r7_2 - temp1_1
00442006        if ((((x87_r7_2 < temp1_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp1_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp1_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
0044200e        struct FrontendFade* ecx_2 = &g_game_base->fade
00442014        if (ecx_2->state == 0)
00442018        begin_frontend_fade_out(ecx_2, 0)
0044201d        long double x87_r7_3 = fconvert.t(player->resurrect_progress)
00442023        long double temp0 = fconvert.t(1f)
00442023        x87_r7_3 - temp0
0044203e        if ((((x87_r7_3 < temp0 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_3, temp0) ? 1 : 0) << 0xa | (x87_r7_3 == temp0 ? 1 : 0) << 0xe):1.b & 0x41) != 0 || g_game_base->fade.state != 4)
0044203e        return
0044204c        struct SubgameRuntime* game = player->game
00442052        if (player->resurrect_final_loss == 0)
00442059        if (game->level_mode == 0)
0044205b        player->visible_life_stock -= 1
00442061        struct GameRoot* game_base_1 = g_game_base
0044206d        game_base_1->players[0].saved_frontend_state = game_base_1->players[0].frontend_state
00442079        g_game_base->players[0].frontend_state = 0x1c
00442083        return
00442084        game->subgame_rebuild_selector = 2
00442096        complete_subgame(player->game, 1)
004420a9        struct GameRoot* game_base_2 = g_game_base
004420ae        if (player->game->selected_level_record_persistent != 0)
004420b7        game_base_2->players[0].saved_frontend_state = game_base_2->players[0].frontend_state
004420c2        g_game_base->players[0].frontend_state = 0x1a
004420cc        return
004420d3        game_base_2->players[0].saved_frontend_state = game_base_2->players[0].frontend_state
004420e4        struct GameRoot* game_base_3 = g_game_base
004420f3        if (player->game->level_mode == 0 && game_base_3->players[0].high_score_entry_pending == 0)
004420f5        game_base_3->players[0].frontend_state = 0x1a
00442105        g_game_base->players[0].saved_frontend_state = 2
0044210f        return
00442110        game_base_3->players[0].frontend_state = 0x1b
0044211b        return
