/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_new_game_menu @ 0x417eb0 */
/* selector: update_new_game_menu */

// Exact Windows cRIntro::AI(): dispatches Tutorial, Postal Mode, Time Trial, Challenge Mode, Help, and Back through the shared front-end state machine, then drives the Intro-owned replay-attract lane. It rotates cursor 0..4, probes replay banks 0/1/3, gives up after 1000 attempts, and seeds the replay-launch handoff with return state 2.
void __thiscall update_new_game_menu(NewGameMenu *menu)
{
  uint8_t hide_for_replay_latch; // al
  FrontendWidget *postal_button; // ecx
  uint32_t widget_flags; // eax
  FrontendWidget *challenge_button; // ecx
  uint32_t v6; // eax
  FrontendWidget *tutorial_button; // ecx
  uint32_t v8; // eax
  FrontendWidget *time_trial_button; // ecx
  uint32_t v10; // eax
  FrontendWidget *back_button; // ecx
  uint32_t v12; // eax
  FrontendWidget *help_button; // ecx
  uint32_t v14; // eax
  double v15; // st7
  int v16; // edi
  _DWORD *v17; // eax
  _DWORD *v18; // eax
  _DWORD *v19; // eax
  int32_t v20; // eax

  if ( read_pressed_text_input_key_code() || (*(_DWORD *)(*((_DWORD *)MEMORY[0x4DF904] + 163) + 60) & 0x4000) != 0 )
  {
    hide_for_replay_latch = menu->hide_for_replay_latch;
    menu->replay_probe_progress = 0.0;
    if ( hide_for_replay_latch == 1 )
    {
      unhide_border_init(menu->postal_button->_pad_00);
      unhide_border_init(menu->tutorial_button->_pad_00);
      unhide_border_init(menu->challenge_button->_pad_00);
      unhide_border_init(menu->time_trial_button->_pad_00);
      unhide_border_init(menu->help_button->_pad_00);
      unhide_border_init(menu->back_button->_pad_00);
      capture_mouse_cursor((float *)MEMORY[0x4DF904] + 164);
      menu->hide_for_replay_latch = 0;
    }
  }
  postal_button = menu->postal_button;
  widget_flags = postal_button->widget_flags;
  if ( (widget_flags & 0x20) != 0 )
  {
    LOBYTE(widget_flags) = widget_flags & 0xDF;
    postal_button->widget_flags = widget_flags;
    destroy_main_menu();
    *((_DWORD *)MEMORY[0x4DF904] + 110) = 10;
    *((_BYTE *)MEMORY[0x4DF904] + 780) = 1;
    *((_DWORD *)MEMORY[0x4DF904] + 119190) = 0;
    *((_DWORD *)MEMORY[0x4DF904] + 4953464) = 2;
  }
  else
  {
    challenge_button = menu->challenge_button;
    v6 = challenge_button->widget_flags;
    if ( (v6 & 0x20) != 0 )
    {
      LOBYTE(v6) = v6 & 0xDF;
      challenge_button->widget_flags = v6;
      destroy_main_menu();
      *((_DWORD *)MEMORY[0x4DF904] + 110) = 10;
      *((_BYTE *)MEMORY[0x4DF904] + 780) = 1;
      *((_DWORD *)MEMORY[0x4DF904] + 119190) = 4;
    }
    else
    {
      tutorial_button = menu->tutorial_button;
      v8 = tutorial_button->widget_flags;
      if ( (v8 & 0x20) != 0 )
      {
        LOBYTE(v8) = v8 & 0xDF;
        tutorial_button->widget_flags = v8;
        destroy_main_menu();
        *((_DWORD *)MEMORY[0x4DF904] + 110) = 10;
        *((_BYTE *)MEMORY[0x4DF904] + 780) = 1;
        *((_DWORD *)MEMORY[0x4DF904] + 119190) = 7;
        initialize_tutorial((TutorialController *)MEMORY[0x4DF904] + 32487);
        unk_4DF9D8 = 1;
      }
      else
      {
        time_trial_button = menu->time_trial_button;
        v10 = time_trial_button->widget_flags;
        if ( (v10 & 0x20) != 0 )
        {
          LOBYTE(v10) = v10 & 0xDF;
          time_trial_button->widget_flags = v10;
          destroy_main_menu();
          *((_DWORD *)MEMORY[0x4DF904] + 110) = 10;
          *((_BYTE *)MEMORY[0x4DF904] + 780) = 1;
          *((_DWORD *)MEMORY[0x4DF904] + 119190) = 1;
        }
        else
        {
          back_button = menu->back_button;
          v12 = back_button->widget_flags;
          if ( (v12 & 0x20) != 0 )
          {
            LOBYTE(v12) = v12 & 0xDF;
            back_button->widget_flags = v12;
            destroy_main_menu();
            *((_DWORD *)MEMORY[0x4DF904] + 110) = 4;
            *((_BYTE *)MEMORY[0x4DF904] + 780) = 1;
          }
          else
          {
            help_button = menu->help_button;
            v14 = help_button->widget_flags;
            if ( (v14 & 0x20) != 0 )
            {
              LOBYTE(v14) = v14 & 0xDF;
              help_button->widget_flags = v14;
              destroy_main_menu();
              *((_DWORD *)MEMORY[0x4DF904] + 110) = 31;
              *((_BYTE *)MEMORY[0x4DF904] + 780) = 1;
            }
          }
          v15 = menu->replay_probe_step + menu->replay_probe_progress;
          menu->replay_probe_progress = v15;
          if ( v15 > 1.0 )
          {
            menu->replay_probe_progress = 0.0;
            v16 = 0;
            *((_DWORD *)MEMORY[0x4DF904] + 4299515) = 0;
            while ( 1 )
            {
              ++v16;
              if ( menu->replay_attract_bank_cursor )
              {
                if ( menu->replay_attract_bank_cursor == 1 )
                {
                  v18 = (char *)MEMORY[0x4DF904]
                      + 129728 * (__int64)((double)next_math_random_value() * 0.00012207031)
                      + 8765736;
                  if ( *v18 == 1 )
                  {
                    *((_DWORD *)MEMORY[0x4DF904] + 4299515) = v18;
                    *((_DWORD *)MEMORY[0x4DF904] + 119190) = 1;
                  }
                }
                else if ( menu->replay_attract_bank_cursor == 3 )
                {
                  v17 = (char *)MEMORY[0x4DF904]
                      + 129728 * (__int64)((double)next_math_random_value() * 0.0015563965)
                      + 10192744;
                  if ( *v17 == 1 )
                  {
                    *((_DWORD *)MEMORY[0x4DF904] + 4299515) = v17;
                    *((_DWORD *)MEMORY[0x4DF904] + 119190) = 4;
                  }
                }
              }
              else
              {
                v19 = (_DWORD *)((char *)&unk_6FFAE8
                               + (_DWORD)MEMORY[0x4DF904]
                               + 129728 * (__int64)((double)next_math_random_value() * 0.00012207031));
                if ( *v19 == 1 )
                {
                  *((_DWORD *)MEMORY[0x4DF904] + 4299515) = v19;
                  *((_DWORD *)MEMORY[0x4DF904] + 119190) = 0;
                }
              }
              v20 = menu->replay_attract_bank_cursor + 1;
              menu->replay_attract_bank_cursor = v20;
              if ( v20 == 5 )
                menu->replay_attract_bank_cursor = 0;
              if ( *((_DWORD *)MEMORY[0x4DF904] + 4299515) )
                break;
              if ( v16 >= 1000 )
                goto LABEL_32;
            }
            if ( v16 >= 1000 )
            {
LABEL_32:
              menu->attract_reset_progress = 0.0;
              menu->attract_reset_step = 0.00027777778;
              return;
            }
            menu->hide_for_replay_latch = 1;
            *((_DWORD *)MEMORY[0x4DF904] + 110) = 10;
            *((_BYTE *)MEMORY[0x4DF904] + 780) = 1;
            *((_BYTE *)MEMORY[0x4DF904] + 17198056) = 1;
            *((_DWORD *)MEMORY[0x4DF904] + 4299516) = 2;
            *((_BYTE *)MEMORY[0x4DF904] + 17198057) = 1;
            menu->attract_reset_progress = 0.0;
            menu->attract_reset_step = 0.00027777778;
            destroy_main_menu();
          }
        }
      }
    }
  }
}
