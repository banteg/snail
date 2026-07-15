/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_row_event_display @ 0x404cf0 */

00404cfc        if (completion->state == COMPLETION_STATE_INACTIVE)
00404cfc        return
00404d0f        struct FrontendWidget* delivered_count_widget = completion->delivered_count_widget
00404d12        if (g_game_base->subgame.subgame_pause_gate != 0)
00404d14        hide_border_init(delivered_count_widget)
00404d1b        hide_border_init(completion->widget_a)
00404d23        hide_border_init(completion->widget_d)
00404d2b        hide_border_init(completion->bonus_widget)
00404d33        hide_border_init(completion->continue_widget)
00404d3d        return
00404d3e        unhide_border_init(delivered_count_widget)
00404d45        unhide_border_init(completion->widget_a)
00404d4d        unhide_border_init(completion->widget_d)
00404d55        unhide_border_init(completion->continue_widget)
00404d5a        enum CompletionState state = completion->state
00404d60        if (state u> COMPLETION_STATE_EMPTY_DELIVERY_DELAY)
00404d60        goto label_404ed7
00404d66        switch (state)
00404d70        case COMPLETION_STATE_STAGING_PARCELS
00404d70        long double x87_r7_2 = fconvert.t(completion->progress_step) + fconvert.t(completion->progress)
00404d73        completion->progress = fconvert.s(x87_r7_2)
00404d76        long double temp2_1 = fconvert.t(1f)
00404d76        x87_r7_2 - temp2_1
00404d81        if ((((x87_r7_2 < temp2_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_2, temp2_1) ? 1 : 0) << 0xa | (x87_r7_2 == temp2_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00404d87        int32_t staged_parcel_count = completion->staged_parcel_count
00404d8f        if (staged_parcel_count s< completion->parcel_target_count)
00404d92        completion->staged_parcel_count = staged_parcel_count + 1
00404d95        struct GameRoot* game_base_1 = g_game_base
00404dae        struct Parcel* eax_4 = spawn_track_parcel(&game_base_1->subgame, &game_base_1->subgame.player.presentation.snail_hotspots_world[0xb], &game_base_1->subgame.player)
00404db3        struct Sprite* sprite = eax_4->sprite
00404db6        eax_4->state = PARCEL_STATE_DELIVERY_PENDING
00404dbd        sprite->size_end = 0f
00404dc3        eax_4->sprite->size_start = 0f
00404dc6        int32_t parcel_target_count = completion->parcel_target_count
00404dcc        bool cond:2_1 = completion->staged_parcel_count != parcel_target_count
00404dce        completion->progress = 0f
00404dd1        if (not(cond:2_1))
00404dd9        if (parcel_target_count != 0)
00404df1        completion->state = COMPLETION_STATE_WAITING_FOR_DELIVERIES
00404ddb        completion->state = COMPLETION_STATE_EMPTY_DELIVERY_DELAY
00404de2        completion->progress = 0f
00404de5        completion->progress_step = 0.00833333377f
00404d81        goto label_404ed7
00404d66        case COMPLETION_STATE_WAITING_FOR_DELIVERIES, COMPLETION_STATE_CONTINUE_ACCEPTED
00404d66        goto label_404ed7
00404e26        case COMPLETION_STATE_SUMMARY_PENDING
00404e26        unhide_border_init(completion->continue_widget)
00404e2b        int32_t bonus_enabled = completion->bonus_enabled
00404e2e        completion->gate_18 = 0
00404e33        completion->state = COMPLETION_STATE_SUMMARY_ACTIVE
00404e3a        if (bonus_enabled == 0)
00404e3a        goto label_404e74
00404e3f        unhide_border_init(completion->bonus_widget)
00404e47        if (completion->parcel_target_count != 0)
00404e47        goto label_404e74
00404e49        struct GameRoot* game_base_2 = g_game_base
00404e55        if (game_base_2->subgame.level_mode == 1)
00404e63        add_subgoldy_score(&game_base_2->subgame.player, 5, completion->bonus_score)
00404e6f        play_sound_effect(0x31)
00404e74        label_404e74:
00404e74        game_base_2 = g_game_base
00404e7c        if (completion->bonus_enabled != 0)
00404e81        long double x87_r7_6 = fconvert.t(completion->bonus_blink_step) + fconvert.t(completion->bonus_blink_progress)
00404e84        completion->bonus_blink_progress = fconvert.s(x87_r7_6)
00404e87        long double temp4_1 = fconvert.t(1f)
00404e87        x87_r7_6 - temp4_1
00404e92        if ((((x87_r7_6 < temp4_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_6, temp4_1) ? 1 : 0) << 0xa | (x87_r7_6 == temp4_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00404e94        struct FrontendWidget* bonus_widget = completion->bonus_widget
00404e97        completion->bonus_blink_progress = 0f
00404ea3        if (((bonus_widget->widget_flags).w:1.b & 0x10) == 0)
00404eac        hide_border_init(bonus_widget)
00404ea5        unhide_border_init(bonus_widget)
00404eb1        game_base_2 = g_game_base
00404ec2        if (((game_base_2->players[0].game_input->input.pressed_buttons).w:1.b & 0x40) != 0)
00404ecb        completion->state = COMPLETION_STATE_CONTINUE_ACCEPTED
00404ed2        play_sound_effect(8)
00404ed7        label_404ed7:
00404ed7        game_base_2 = g_game_base
00404f08        long double x87_r6_5 = fconvert.t(game_base_2->players[0].transform.basis_up.x)
00404f10        long double x87_r5_1 = fconvert.t(game_base_2->players[0].transform.basis_up.y)
00404f1c        long double x87_r5_3 = fconvert.t(game_base_2->players[0].transform.basis_up.z)
00404f93        long double x87_r6_8 = x87_r6_5 + x87_r6_5 + fconvert.t(game_base_2->players[0].transform.basis_right.x) * fconvert.t(7.30000019f) + fconvert.t(game_base_2->players[0].transform.position.x) + fconvert.t(game_base_2->players[0].transform.basis_forward.x) * fconvert.t(6f)
00404fa3        long double x87_r7_11 = fconvert.t(fconvert.s(fconvert.t(fconvert.s(fconvert.t(fconvert.s(fconvert.t(game_base_2->players[0].transform.basis_right.y) * fconvert.t(7.30000019f))) + fconvert.t(game_base_2->players[0].transform.position.y))) + fconvert.t(fconvert.s(x87_r5_1 + x87_r5_1)))) + fconvert.t(fconvert.s(fconvert.t(game_base_2->players[0].transform.basis_forward.y) * fconvert.t(6f)))
00404fa7        completion->widget_world.x = fconvert.s(x87_r6_8)
00404fb9        completion->widget_world.y = fconvert.s(x87_r7_11)
00404fc4        completion->widget_world.z = fconvert.s(fconvert.t(fconvert.s(fconvert.t(fconvert.s(fconvert.t(fconvert.s(fconvert.t(game_base_2->players[0].transform.basis_right.z) * fconvert.t(7.30000019f))) + fconvert.t(game_base_2->players[0].transform.position.z))) + fconvert.t(fconvert.s(x87_r5_3 + x87_r5_3)))) + fconvert.t(fconvert.s(fconvert.t(game_base_2->players[0].transform.basis_forward.z) * fconvert.t(6f))))
00404fc7        int32_t delivered_parcel_count = completion->delivered_parcel_count
00404fcd        if (delivered_parcel_count s>= 0xa)
00404ff2        *(completion->delivered_count_widget + 0x2cc) = (delivered_parcel_count s/ 0xa).b + 0x30
00404fd2        *(completion->delivered_count_widget + 0x2cc) = 0x20
00405009        *(completion->delivered_count_widget + 0x2cd) = (mods.dp.d(sx.q(completion->delivered_parcel_count), 0xa)).b + 0x30
00404d66        case COMPLETION_STATE_SUMMARY_ACTIVE
00404d66        goto label_404e74
00404e00        case COMPLETION_STATE_EMPTY_DELIVERY_DELAY
00404e00        long double x87_r7_4 = fconvert.t(completion->progress_step) + fconvert.t(completion->progress)
00404e03        completion->progress = fconvert.s(x87_r7_4)
00404e06        long double temp3_1 = fconvert.t(1f)
00404e06        x87_r7_4 - temp3_1
00404e11        if ((((x87_r7_4 < temp3_1 ? 1 : 0) << 8 | (is_unordered.t(x87_r7_4, temp3_1) ? 1 : 0) << 0xa | (x87_r7_4 == temp3_1 ? 1 : 0) << 0xe):1.b & 0x41) == 0)
00404e17        completion->state = COMPLETION_STATE_SUMMARY_PENDING
00404e11        goto label_404ed7
00405014        return
