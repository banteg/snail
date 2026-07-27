/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_high_score_screen @ 0x417260 */
/* selector: update_high_score_screen */

// Exact void Windows `cRHighScore::AI()`: runs replay launch, bank toggling, inline name submission, and exit actions while borrowing row widgets and the separate persistent cRSubHighScore bank. Android directly tail-branches to Init, UnInit, and Exit; the Windows transcription is proof-grade at 205/205 instructions.
void __thiscall update_high_score_screen(HighScore *high_score)
{
  FrontendWidget *v2; // ecx
  FrontendWidgetFlag widget_flags; // eax
  FrontendWidget *submit_name_button; // ecx
  FrontendWidgetFlag v5; // eax
  FrontendWidget *v6; // eax
  FrontendWidget *cancel_name_button; // ecx
  FrontendWidgetFlag v8; // eax
  FrontendWidget *bank_toggle_button; // ecx
  FrontendWidgetFlag v10; // eax
  int32_t selected_bank; // eax
  FrontendWidget *back_button; // ecx
  FrontendWidgetFlag v13; // eax
  int32_t mode; // eax
  GameRoot *v15; // edx
  int32_t v16; // ebp
  int v17; // edi
  FrontendWidget *v18; // ecx
  FrontendWidgetFlag v19; // eax
  FrontendWidget **replay_row_widgets; // [esp+Ch] [ebp-4h]

  if ( high_score->entering_name != 0 )
  {
    v2 = high_score->name_row_widgets[high_score->selected_rank];
    widget_flags = v2->widget_flags;
    if ( (BYTE1(widget_flags) & 0x40) != 0 )
    {
      BYTE1(widget_flags) &= ~0x40u;
      v2->widget_flags = widget_flags;
      destroy_high_score_screen(high_score);
      kill_game_sprites(&g_sprite_manager);
      rstrcpy_checked_ascii(
        g_game_base->subgame.sub_high_score.active_record_bank[high_score->selected_rank].player_name,
        (const char *)&high_score->name_row_widgets[high_score->selected_rank]->text_buffer);
      rstrcpy_checked_ascii(
        g_game_base->players[0].player_name,
        (const char *)&high_score->name_row_widgets[high_score->selected_rank]->text_buffer);
      rstrcpy_checked_ascii(
        g_runtime_config.last_entered_player_name,
        (const char *)&high_score->name_row_widgets[high_score->selected_rank]->text_buffer);
      exit_high_score_screen(high_score);
    }
    else
    {
      submit_name_button = high_score->submit_name_button;
      v5 = submit_name_button->widget_flags;
      if ( (v5 & 0x20) != 0 )
      {
        LOBYTE(v5) = v5 & 0xDF;
        submit_name_button->widget_flags = v5;
        v6 = high_score->name_row_widgets[high_score->selected_rank];
        v6->widget_flags |= 0x8000000u;
      }
      cancel_name_button = high_score->cancel_name_button;
      v8 = cancel_name_button->widget_flags;
      if ( (v8 & 0x20) != 0 )
      {
        LOBYTE(v8) = v8 & 0xDF;
        cancel_name_button->widget_flags = v8;
        destroy_high_score_screen(high_score);
        kill_game_sprites(&g_sprite_manager);
        mini_delete_high_score_entry(&g_game_base->subgame.sub_high_score, high_score->selected_rank);
        exit_high_score_screen(high_score);
      }
    }
  }
  else
  {
    bank_toggle_button = high_score->bank_toggle_button;
    v10 = bank_toggle_button->widget_flags;
    if ( (v10 & 0x20) != 0 )
    {
      LOBYTE(v10) = v10 & 0xDF;
      bank_toggle_button->widget_flags = v10;
      destroy_high_score_screen(high_score);
      selected_bank = high_score->selected_bank;
      if ( selected_bank != 0 )
      {
        if ( selected_bank == 1 )
          high_score->selected_bank = 0;
      }
      else
      {
        high_score->selected_bank = 1;
      }
      g_runtime_config.high_score_selected_bank = high_score->selected_bank;
      initialize_high_score_screen(high_score, high_score->selected_bank, -1);
    }
    else
    {
      back_button = high_score->back_button;
      v13 = back_button->widget_flags;
      if ( (v13 & 0x20) != 0 )
      {
        LOBYTE(v13) = v13 & 0xDF;
        back_button->widget_flags = v13;
        mode = high_score->mode;
        if ( mode == 1 )
        {
          g_game_base->players[0].frontend_state = 10;
          g_game_base->players[0].redispatch_requested = 1;
          destroy_high_score_screen(high_score);
        }
        else
        {
          if ( mode == 0 )
            g_game_base->players[0].frontend_state = 4;
          destroy_high_score_screen(high_score);
        }
      }
      else
      {
        v15 = g_game_base;
        v16 = 0;
        if ( g_game_base->subgame.sub_high_score.active_record_count > 0 )
        {
          v17 = 0;
          replay_row_widgets = high_score->replay_row_widgets;
          do
          {
            if ( v15->subgame.sub_high_score.active_record_bank[v17].active == 1 )
            {
              v18 = *replay_row_widgets;
              if ( *replay_row_widgets != nullptr )
              {
                v19 = v18->widget_flags;
                if ( (v19 & 0x20) != 0 )
                {
                  LOBYTE(v19) = v19 & 0xDF;
                  v18->widget_flags = v19;
                  g_game_base->players[0].frontend_state = 10;
                  g_game_base->players[0].redispatch_requested = 1;
                  destroy_high_score_screen(high_score);
                  g_game_base->subgame.selected_level_record = &g_game_base->subgame.sub_high_score.active_record_bank[v17];
                  g_game_base->subgame.selected_level_record_active = 1;
                  g_game_base->subgame.selected_level_record_persistent = 1;
                  g_game_base->subgame.selected_level_record_cursor = 18;
                  g_game_base->subgame.level_mode = g_game_base->subgame.selected_level_record->replay_mode_id;
                  v15 = g_game_base;
                }
              }
            }
            ++v16;
            ++v17;
            ++replay_row_widgets;
          }
          while ( v16 < v15->subgame.sub_high_score.active_record_count );
        }
      }
    }
  }
}
