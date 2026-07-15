/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: flush_row_event_display @ 0x404830 */

00404838        if (completion->state != COMPLETION_STATE_INACTIVE)
0040483e        int32_t delivered_parcel_count = completion->delivered_parcel_count
00404841        int32_t parcel_target_count = completion->parcel_target_count
00404846        if (delivered_parcel_count != parcel_target_count)
00404848        if (delivered_parcel_count s< parcel_target_count)
0040486c        int32_t parcel_target_count_1
0040486c        int32_t edx_2
00404859        add_subgoldy_score(&g_game_base->subgame.player, 4, 0)
00404861        parcel_target_count_1 = completion->parcel_target_count
00404864        edx_2 = completion->delivered_parcel_count + 1
00404867        completion->delivered_parcel_count = edx_2
0040486c        do while (edx_2 s< parcel_target_count_1)
00404873        if (completion->bonus_enabled != 0)
00404887        add_subgoldy_score(&g_game_base->subgame.player, completion->bonus_score, 0)
0040488f        void* widget_a = completion->widget_a
00404893        completion->delivered_parcel_count += 1
00404896        g_game_base
004048a2        kill_border(widget_a)
004048a7        g_game_base
004048b6        kill_border(completion->delivered_count_widget)
004048be        g_game_base
004048cb        kill_border(completion->widget_d)
004048d3        g_game_base
004048e0        kill_border(completion->bonus_widget)
004048e5        g_game_base
004048f4        kill_border(completion->continue_widget)
004048f9        struct GameRoot* game_base_1 = g_game_base
004048ff        int32_t display_token = completion->display_token
00404908        if (game_base_1->subgame.player.total_score != display_token)
0040490a        game_base_1->subgame.player.total_score = display_token
00404910        completion->state = COMPLETION_STATE_INACTIVE
00404918        return
