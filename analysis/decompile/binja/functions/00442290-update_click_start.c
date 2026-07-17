/* tool: binary_ninja */
/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/binary_ninja/SnailMail_unwrapped.exe.bndb */
/* manifest: /Users/banteg/dev/banteg/snail-mail/analysis/symbols/gameplay-functions.json */
/* function: update_click_start @ 0x442290 */

004422a0        if (g_game_base->subgame.subgame_pause_gate != 0)
004422a0        return
004422ac        struct FrontendWidget* prompt = click_start->prompt
004422b4        if (click_start->hide_prompt == 0)
004422bd        unhide_border_init(prompt)
004422b6        hide_border_init(prompt)
004422d1        switch (click_start->state)
004422de        case CLICK_START_STATE_WAITING_FOR_START
004422de        g_game_base->backdrop.unknown_660 = 1
004422e5        struct GameRoot* game_base_1 = g_game_base
004422f1        if (game_base_1->subgame.replay_update_cursor s> 8)
004422f3        game_base_1->subgame.replay_update_cursor = 8
004422fd        game_base_1 = g_game_base
00442302        uint8_t selected_level_record_active = game_base_1->subgame.selected_level_record_active
0044230a        if (selected_level_record_active == 0)
00442332        label_442332:
00442346        if (click_start->hide_prompt == 0 && ((game_base_1->players[0].game_input->input.pressed_buttons).w:1.b & 0x40) != 0)
00442346        goto label_442358
00442322        if ((*&game_base_1->subgame.selected_level_record->run_records[0 + game_base_1->subgame.replay_update_cursor].flags & 0x20) != 0)
00442358        label_442358:
00442358        click_start->owner_player->startup_track_index = game_base_1->subgame.replay_update_cursor
0044235e        click_start->state = CLICK_START_STATE_START_PENDING
00442368        struct GameRoot* game_base_3 = g_game_base
00442376        if (game_base_3->subgame.selected_level_record_active == 0)
0044237e        int32_t eax_4 = game_base_3->subgame.replay_update_cursor * 3
00442381        *&(&game_base_3->subgame.current_high_score_record.run_records[0].flags)[eax_4] |= 0x20
00442390        struct GameRoot* game_base_4 = g_game_base
0044239c        int32_t edx_2 = game_base_4->subgame.replay_update_cursor * 3
0044239f        *&(&game_base_4->subgame.current_high_score_record.run_records[0].flags)[edx_2] &= 0xfffe
004423b0        struct GameRoot* game_base_2 = g_game_base
004423bb        game_base_2->subgame.current_high_score_record.source_tail = game_base_2->subgame.replay_update_cursor
004423cd        set_input_controller_pointer_authored_xy(0, 320f, 240f)
004423de        set_input_controller_pointer_authored_xy(1, 320f, 240f)
004423ed        play_sound_effect(8)
004423f3        return
00442326        if (selected_level_record_active == 0)
00442326        goto label_442332
00442401        case CLICK_START_STATE_START_PENDING
00442401        set_math_random_seed(g_game_base->subgame.current_high_score_record.runtime_build_seed)
00442406        struct FrontendWidget* prompt_1 = click_start->prompt
0044240f        click_start->state = CLICK_START_STATE_TEARDOWN
00442419        click_start->teardown_progress = 0f
00442423        click_start->teardown_progress_step = 0.0166666675f
0044242d        g_game_base
0044243a        kill_border(prompt_1)
0044244e        label_44244e:
0044244e        click_start->bod.transform.position.y = fconvert.s(fconvert.t(click_start->teardown_progress) * fconvert.t(16f) + fconvert.t(click_start->bod.transform.position.y))
0044245d        click_start->teardown_progress = fconvert.s(fconvert.t(click_start->teardown_progress_step) + fconvert.t(click_start->teardown_progress))
00442468        struct BodList* ecx_9 = &g_game_base->active_bod_list
0044246e        uint16_t list_flags = (click_start->bod.bod.bod.list_flags).w
00442474        if ((list_flags:1.b & 2) == 0)
0044247b        report_errorf("List remove")
00442483        click_start->state = CLICK_START_STATE_INACTIVE
0044248e        return
00442491        if ((list_flags.b & 0x40) != 0)
00442498        report_errorf("List remove NEXTBOD")
004424a0        click_start->state = CLICK_START_STATE_INACTIVE
004424ab        return
004424ac        struct BodNode* list_next = click_start->bod.bod.bod.list_next
004424b1        if (list_next != 0)
004424b6        list_next->list_prev = click_start->bod.bod.bod.list_prev
004424b9        struct BodNode* list_prev = click_start->bod.bod.bod.list_prev
004424be        if (list_prev == 0)
004424cb        ecx_9->first = click_start->bod.bod.bod.list_next
004424c3        list_prev->list_next = click_start->bod.bod.bod.list_next
004424d1        click_start->bod.bod.bod.list_next = ecx_9->free_top
004424d4        ecx_9->free_top = click_start
004424d7        uint32_t list_flags_1 = click_start->bod.bod.bod.list_flags
004424da        click_start->state = CLICK_START_STATE_INACTIVE
004424e4        list_flags_1:1.b &= 0xfd
004424e7        click_start->bod.bod.bod.list_flags = list_flags_1
004422d1        case CLICK_START_STATE_TEARDOWN
004422d1        goto label_44244e
004424eb        return
