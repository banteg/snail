/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_high_score_screen @ 0x417260 */
/* selector: update_high_score_screen */

// Runs the high-score screen state machine, including replay launch, bank toggling, inline name submission, and back or exit actions. Cross-port Android and iOS symbols match this helper to `cRHighScore::AI()`.
int __thiscall update_high_score_screen(HighScoreScreen *screen)
{
  FrontendWidget *v2; // ecx
  uint32_t widget_flags; // eax
  int result; // eax
  FrontendWidget *cancel_name_button; // ecx
  uint32_t v6; // eax
  FrontendWidget *v7; // eax
  FrontendWidget *submit_name_button; // ecx
  FrontendWidget *bank_toggle_button; // ecx
  uint32_t v10; // eax
  int32_t selected_bank; // eax
  FrontendWidget *back_button; // ecx
  uint32_t v13; // eax
  int32_t mode; // eax
  void *v15; // edx
  int v16; // ebp
  int v17; // edi
  FrontendWidget *v18; // ecx
  uint32_t v19; // eax
  FrontendWidget **replay_row_widgets; // [esp+Ch] [ebp-4h]

  if ( screen->entering_name )
  {
    v2 = screen->name_row_widgets[screen->selected_rank];
    widget_flags = v2->widget_flags;
    if ( (widget_flags & 0x4000) != 0 )
    {
      BYTE1(widget_flags) &= ~0x40u;
      v2->widget_flags = widget_flags;
      destroy_high_score_screen(screen);
      kill_game_sprites();
      rstrcpy_checked_ascii(
        (char *)(*(_DWORD *)&byte_6FFAE0[(_DWORD)MEMORY[0x4DF904]] + 129728 * screen->selected_rank + 84),
        (char *)&screen->name_row_widgets[screen->selected_rank]->text_buffer);
      rstrcpy_checked_ascii(
        (char *)MEMORY[0x4DF904] + 420,
        (char *)&screen->name_row_widgets[screen->selected_rank]->text_buffer);
      rstrcpy_checked_ascii(byte_4DF978, (char *)&screen->name_row_widgets[screen->selected_rank]->text_buffer);
      return (int)exit_high_score_screen();
    }
    else
    {
      cancel_name_button = screen->cancel_name_button;
      v6 = cancel_name_button->widget_flags;
      if ( (v6 & 0x20) != 0 )
      {
        LOBYTE(v6) = v6 & 0xDF;
        cancel_name_button->widget_flags = v6;
        v7 = screen->name_row_widgets[screen->selected_rank];
        v7->widget_flags |= 0x8000000u;
      }
      submit_name_button = screen->submit_name_button;
      result = submit_name_button->widget_flags;
      if ( (result & 0x20) != 0 )
      {
        LOBYTE(result) = result & 0xDF;
        submit_name_button->widget_flags = result;
        destroy_high_score_screen(screen);
        kill_game_sprites();
        commit_high_score_entry_into_top_ten(&byte_6FFAE0[(_DWORD)MEMORY[0x4DF904]], screen->selected_rank);
        return (int)exit_high_score_screen();
      }
    }
  }
  else
  {
    bank_toggle_button = screen->bank_toggle_button;
    v10 = bank_toggle_button->widget_flags;
    if ( (v10 & 0x20) != 0 )
    {
      LOBYTE(v10) = v10 & 0xDF;
      bank_toggle_button->widget_flags = v10;
      destroy_high_score_screen(screen);
      selected_bank = screen->selected_bank;
      if ( selected_bank )
      {
        if ( selected_bank == 1 )
          screen->selected_bank = 0;
      }
      else
      {
        screen->selected_bank = 1;
      }
      unk_4DF9C0 = screen->selected_bank;
      return (int)initialize_high_score_screen((int)screen, screen->selected_bank, -1);
    }
    else
    {
      back_button = screen->back_button;
      v13 = back_button->widget_flags;
      if ( (v13 & 0x20) != 0 )
      {
        LOBYTE(v13) = v13 & 0xDF;
        back_button->widget_flags = v13;
        mode = screen->mode;
        if ( mode == 1 )
        {
          *((_DWORD *)MEMORY[0x4DF904] + 110) = 10;
          *((_BYTE *)MEMORY[0x4DF904] + 780) = 1;
          return destroy_high_score_screen(screen);
        }
        else
        {
          if ( !mode )
            *((_DWORD *)MEMORY[0x4DF904] + 110) = 4;
          return destroy_high_score_screen(screen);
        }
      }
      else
      {
        v15 = MEMORY[0x4DF904];
        v16 = 0;
        result = *(_DWORD *)((char *)&unk_6FFAE4 + (_DWORD)MEMORY[0x4DF904]);
        if ( result > 0 )
        {
          v17 = 0;
          replay_row_widgets = screen->replay_row_widgets;
          do
          {
            if ( *(_DWORD *)(*(_DWORD *)&byte_6FFAE0[(_DWORD)v15] + v17) == 1 )
            {
              v18 = *replay_row_widgets;
              if ( *replay_row_widgets )
              {
                v19 = v18->widget_flags;
                if ( (v19 & 0x20) != 0 )
                {
                  LOBYTE(v19) = v19 & 0xDF;
                  v18->widget_flags = v19;
                  *((_DWORD *)MEMORY[0x4DF904] + 110) = 10;
                  *((_BYTE *)MEMORY[0x4DF904] + 780) = 1;
                  destroy_high_score_screen(screen);
                  *((_DWORD *)MEMORY[0x4DF904] + 4299515) = v17 + *(_DWORD *)&byte_6FFAE0[(_DWORD)MEMORY[0x4DF904]];
                  *((_BYTE *)MEMORY[0x4DF904] + 17198056) = 1;
                  *((_BYTE *)MEMORY[0x4DF904] + 17198057) = 1;
                  *((_DWORD *)MEMORY[0x4DF904] + 4299516) = 18;
                  *((_DWORD *)MEMORY[0x4DF904] + 119190) = *(_DWORD *)(*((_DWORD *)MEMORY[0x4DF904] + 4299515) + 44);
                  v15 = MEMORY[0x4DF904];
                }
              }
            }
            ++v16;
            v17 += 129728;
            ++replay_row_widgets;
            result = *(_DWORD *)((char *)&unk_6FFAE4 + (_DWORD)v15);
          }
          while ( v16 < result );
        }
      }
    }
  }
  return result;
}

