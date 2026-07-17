/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_click_start @ 0x442290 */
/* selector: update_click_start */

// Windows `ClickStart::update_click_start`, authored as `cRClickStart::AI`: advances the prompt hide gate and selected-replay or player-confirm handoff through `SubgameRuntime`'s replay record/cursor fields, updates the working `SubSolution` run flags and parent startup index, recenters both pointers, plays SFX 8, and recycles the embedded RenderableBod child through `GameRoot::active_bod_list`.
void __thiscall update_click_start(ClickStart *click_start)
{
  FrontendWidget *prompt; // ecx
  GameRoot *v3; // eax
  FrontendWidget *v4; // ecx
  BodList *p_active_bod_list; // ecx
  uint32_t list_flags; // eax
  struct BodNode *list_next; // eax
  struct BodNode *list_prev; // eax
  uint32_t v9; // eax

  if ( !g_game_base->subgame.subgame_pause_gate )
  {
    prompt = click_start->prompt;
    if ( click_start->hide_prompt )
      hide_border_init(prompt);
    else
      unhide_border_init(prompt);
    switch ( click_start->state )
    {
      case CLICK_START_STATE_WAITING_FOR_START:
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
        else if ( click_start->hide_prompt || (v3->players[0].game_input->input.pressed_buttons & 0x4000) == 0 )
        {
          return;
        }
        click_start->owner_player->startup_track_index = v3->subgame.replay_update_cursor;
        click_start->state = CLICK_START_STATE_START_PENDING;
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
      case CLICK_START_STATE_START_PENDING:
        set_math_random_seed(g_game_base->subgame.current_high_score_record.runtime_build_seed);
        v4 = click_start->prompt;
        click_start->state = CLICK_START_STATE_TEARDOWN;
        click_start->teardown_progress = 0.0;
        click_start->teardown_progress_step = 0.016666668;
        kill_border(v4);
        goto LABEL_17;
      case CLICK_START_STATE_TEARDOWN:
LABEL_17:
        click_start->bod.transform.position.y = click_start->teardown_progress * 16.0
                                              + click_start->bod.transform.position.y;
        click_start->teardown_progress = click_start->teardown_progress_step + click_start->teardown_progress;
        p_active_bod_list = &g_game_base->active_bod_list;
        list_flags = click_start->bod.bod.bod.list_flags;
        if ( (list_flags & 0x200) != 0 )
        {
          if ( (list_flags & 0x40) != 0 )
          {
            report_errorf(aListRemoveNext);
            click_start->state = CLICK_START_STATE_INACTIVE;
          }
          else
          {
            list_next = click_start->bod.bod.bod.list_next;
            if ( list_next )
              list_next->list_prev = click_start->bod.bod.bod.list_prev;
            list_prev = click_start->bod.bod.bod.list_prev;
            if ( list_prev )
              list_prev->list_next = click_start->bod.bod.bod.list_next;
            else
              p_active_bod_list->first = click_start->bod.bod.bod.list_next;
            click_start->bod.bod.bod.list_next = p_active_bod_list->free_top;
            p_active_bod_list->free_top = &click_start->bod.bod.bod;
            v9 = click_start->bod.bod.bod.list_flags;
            click_start->state = CLICK_START_STATE_INACTIVE;
            BYTE1(v9) &= ~2u;
            click_start->bod.bod.bod.list_flags = v9;
          }
        }
        else
        {
          report_errorf(aListRemove);
          click_start->state = CLICK_START_STATE_INACTIVE;
        }
        return;
      default:
        return;
    }
  }
}
