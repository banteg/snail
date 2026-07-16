/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_click_start @ 0x442290 */
/* selector: update_click_start */

// Windows `ClickStart::update_click_start`, authored as `cRClickStart::AI`: advances the prompt hide gate and selected-replay or player-confirm handoff through `SubgameRuntime`'s replay record/cursor fields, updates the working `SubSolution` run flags and parent startup index, recenters both pointers, plays SFX 8, and recycles the embedded RenderableBod child through `GameRoot::active_bod_list`.
void __thiscall update_click_start(ClickStartController *controller)
{
  FrontendWidget *prompt; // ecx
  GameRoot *v3; // eax
  FrontendWidget *v4; // ecx
  FrameBodList *p_active_bod_list; // ecx
  int32_t list_flags; // eax
  struct ClickStartController *list_next; // eax
  struct ClickStartController *list_prev; // eax
  int32_t v9; // eax

  if ( !g_game_base->subgame.subgame_pause_gate )
  {
    prompt = controller->prompt;
    if ( controller->hide_prompt )
      hide_border_init(prompt);
    else
      unhide_border_init(prompt);
    switch ( controller->state )
    {
      case 2:
        g_game_base->backdrop.unknown_660 = 1;
        v3 = g_game_base;
        if ( g_game_base->subgame.replay_update_cursor > 8 )
        {
          g_game_base->subgame.replay_update_cursor = 8;
          v3 = g_game_base;
        }
        if ( v3->subgame.selected_level_record_active )
        {
          if ( (v3->subgame.selected_level_record->run_records[v3->subgame.replay_update_cursor].flags & 0x20) == 0 )
            return;
        }
        else if ( controller->hide_prompt || (v3->players[0].game_input->input.pressed_buttons & 0x4000) == 0 )
        {
          return;
        }
        controller->player->startup_track_index = v3->subgame.replay_update_cursor;
        controller->state = 3;
        if ( !g_game_base->subgame.selected_level_record_active )
        {
          LOBYTE(g_game_base->subgame.current_high_score_record.run_records[g_game_base->subgame.replay_update_cursor].flags) |= 0x20u;
          g_game_base->subgame.current_high_score_record.run_records[g_game_base->subgame.replay_update_cursor].flags &= ~1u;
          g_game_base->subgame.current_high_score_record.source_tail = g_game_base->subgame.replay_update_cursor;
        }
        set_input_controller_pointer_authored_xy(0, 320.0, 240.0);
        set_input_controller_pointer_authored_xy(1, 320.0, 240.0);
        play_sound_effect(8);
        break;
      case 3:
        set_math_random_seed(g_game_base->subgame.current_high_score_record.runtime_build_seed);
        v4 = controller->prompt;
        controller->state = 4;
        controller->teardown_progress = 0.0;
        controller->teardown_progress_step = 0.016666668;
        kill_border(v4);
        goto LABEL_17;
      case 4:
LABEL_17:
        controller->transform.position.y = controller->teardown_progress * 16.0 + controller->transform.position.y;
        controller->teardown_progress = controller->teardown_progress_step + controller->teardown_progress;
        p_active_bod_list = &g_game_base->active_bod_list;
        list_flags = controller->list_flags;
        if ( (list_flags & 0x200) != 0 )
        {
          if ( (list_flags & 0x40) != 0 )
          {
            report_errorf(aListRemoveNext);
            controller->state = 0;
          }
          else
          {
            list_next = controller->list_next;
            if ( list_next )
              list_next->list_prev = controller->list_prev;
            list_prev = controller->list_prev;
            if ( list_prev )
              list_prev->list_next = controller->list_next;
            else
              p_active_bod_list->first = (FrameBodBase *)controller->list_next;
            controller->list_next = (struct ClickStartController *)p_active_bod_list->free_top;
            p_active_bod_list->free_top = (FrameBodBase *)controller;
            v9 = controller->list_flags;
            controller->state = 0;
            BYTE1(v9) &= ~2u;
            controller->list_flags = v9;
          }
        }
        else
        {
          report_errorf(aListRemove);
          controller->state = 0;
        }
        return;
      default:
        return;
    }
  }
}
