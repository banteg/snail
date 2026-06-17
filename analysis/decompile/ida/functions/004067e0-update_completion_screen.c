/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_completion_screen @ 0x4067e0 */
/* selector: update_completion_screen */

// Runs the completion-screen state machine, including continue, replay, route-map return, and outbound-link actions. Cross-port Android and iOS symbols match this helper to `cRCompletion::AI()`.
int __thiscall update_completion_screen(CompletionPrompt *prompt)
{
  FrontendWidget *v2; // ecx
  uint32_t v3; // eax
  FrontendWidget *v4; // ecx
  uint32_t v5; // eax
  FrontendWidget *v6; // ecx
  uint32_t v7; // eax
  FrontendWidget *yes_button; // ecx
  uint32_t widget_flags; // eax
  int v10; // eax
  FrontendWidget *v11; // ecx
  uint32_t v12; // eax
  FrontendWidget *v13; // ecx
  uint32_t v14; // eax
  FrontendWidget *v15; // ecx
  uint32_t v16; // eax
  FrontendWidget *v17; // ecx
  uint32_t v18; // eax
  FrontendWidget *no_button; // ecx
  int result; // eax

  switch ( prompt->state )
  {
    case 2:
      yes_button = prompt->yes_button;
      widget_flags = yes_button->widget_flags;
      if ( (widget_flags & 0x20) != 0 )
      {
        LOBYTE(widget_flags) = widget_flags & 0xDF;
        yes_button->widget_flags = widget_flags;
        complete_subgame((int)MEMORY[0x4DF904] + 476696, 1);
        if ( *((_BYTE *)MEMORY[0x4DF904] + 781) == 1 )
        {
          prompt->previous_frontend_state = *((_DWORD *)MEMORY[0x4DF904] + 110);
          destroy_completion_screen(prompt);
          uninit_pause_menu((_DWORD **)MEMORY[0x4DF904] + 119179);
          *((_BYTE *)MEMORY[0x4DF904] + 476705) = 0;
          set_sprite_manager_paused(unk_790F30, 0);
          destroy_subgame((int)MEMORY[0x4DF904] + 476696);
        }
        else
        {
          destroy_completion_screen(prompt);
          uninit_pause_menu((_DWORD **)MEMORY[0x4DF904] + 119179);
          *((_BYTE *)MEMORY[0x4DF904] + 476705) = 0;
          set_sprite_manager_paused(unk_790F30, 0);
          destroy_subgame((int)MEMORY[0x4DF904] + 476696);
          v10 = *((_DWORD *)MEMORY[0x4DF904] + 119190);
          if ( v10 == 4 || v10 == 1 )
            initialize_subgame((int)MEMORY[0x4DF904] + 476696);
          else
            *((_DWORD *)MEMORY[0x4DF904] + 110) = 2;
        }
      }
      break;
    case 3:
      v13 = prompt->yes_button;
      v14 = v13->widget_flags;
      if ( (v14 & 0x20) != 0 )
      {
        LOBYTE(v14) = v14 & 0xDF;
        v13->widget_flags = v14;
        destroy_completion_screen(prompt);
        uninit_pause_menu((_DWORD **)MEMORY[0x4DF904] + 119179);
        *((_BYTE *)MEMORY[0x4DF904] + 476705) = 0;
        set_sprite_manager_paused(unk_790F30, 0);
        destroy_subgame((int)MEMORY[0x4DF904] + 476696);
        *((_DWORD *)MEMORY[0x4DF904] + 110) = *((_DWORD *)MEMORY[0x4DF904] + 4299516);
      }
      break;
    case 4:
      v15 = prompt->yes_button;
      v16 = v15->widget_flags;
      if ( (v16 & 0x20) != 0 )
      {
        LOBYTE(v16) = v16 & 0xDF;
        v15->widget_flags = v16;
        goto LABEL_23;
      }
      break;
    case 7:
      v11 = prompt->yes_button;
      v12 = v11->widget_flags;
      if ( (v12 & 0x20) != 0 )
      {
        LOBYTE(v12) = v12 & 0xDF;
        v11->widget_flags = v12;
        destroy_completion_screen(prompt);
        uninit_pause_menu((_DWORD **)MEMORY[0x4DF904] + 119179);
        *((_BYTE *)MEMORY[0x4DF904] + 476705) = 0;
        set_sprite_manager_paused(unk_790F30, 0);
        goto LABEL_24;
      }
      break;
    case 8:
      update_new_game_menu((NewGameMenu *)((char *)MEMORY[0x4DF904] + 324316));
      v17 = prompt->yes_button;
      v18 = v17->widget_flags;
      if ( (v18 & 0x20) != 0 )
      {
        LOBYTE(v18) = v18 & 0xDF;
        v17->widget_flags = v18;
        sub_433050(aAlpha72Url);
        *((_DWORD *)MEMORY[0x4DF904] + 110) = 0;
        *((_BYTE *)MEMORY[0x4DF904] + 1384) = 0;
        destroy_completion_screen(prompt);
      }
      break;
    case 9:
      v2 = prompt->yes_button;
      v3 = v2->widget_flags;
      if ( (v3 & 0x20) != 0 )
      {
        LOBYTE(v3) = v3 & 0xDF;
        v2->widget_flags = v3;
        destroy_completion_screen(prompt);
        *((_DWORD *)MEMORY[0x4DF904] + 14) = 3;
      }
      break;
    case 0xA:
      update_main_menu((_DWORD *)MEMORY[0x4DF904] + 81097);
      v4 = prompt->yes_button;
      v5 = v4->widget_flags;
      if ( (v5 & 0x20) != 0 )
      {
        LOBYTE(v5) = v5 & 0xDF;
        v4->widget_flags = v5;
        destroy_completion_screen(prompt);
        destroy_main_menu();
        if ( !*((_DWORD *)MEMORY[0x4DF904] + 14) )
          *((_DWORD *)MEMORY[0x4DF904] + 14) = 1;
      }
      break;
    case 0xB:
      update_galaxy((int)MEMORY[0x4DF904] + 19744312);
      v6 = prompt->yes_button;
      v7 = v6->widget_flags;
      if ( (v7 & 0x20) != 0 )
      {
        LOBYTE(v7) = v7 & 0xDF;
        v6->widget_flags = v7;
        destroy_galaxy((_DWORD **)MEMORY[0x4DF904] + 4936078);
        complete_subgame((int)MEMORY[0x4DF904] + 476696, 1);
        if ( *((_BYTE *)MEMORY[0x4DF904] + 781) == 1 )
        {
          prompt->previous_frontend_state = *((_DWORD *)MEMORY[0x4DF904] + 110);
          destroy_completion_screen(prompt);
          destroy_subgame((int)MEMORY[0x4DF904] + 476696);
        }
        else
        {
LABEL_23:
          destroy_completion_screen(prompt);
LABEL_24:
          destroy_subgame((int)MEMORY[0x4DF904] + 476696);
          *((_DWORD *)MEMORY[0x4DF904] + 110) = 2;
        }
      }
      break;
    default:
      break;
  }
  no_button = prompt->no_button;
  result = no_button->widget_flags;
  if ( (result & 0x20) != 0 )
  {
    LOBYTE(result) = result & 0xDF;
    no_button->widget_flags = result;
    *((_DWORD *)MEMORY[0x4DF904] + 110) = prompt->previous_frontend_state;
    *((_BYTE *)MEMORY[0x4DF904] + 1384) = 0;
    return destroy_completion_screen(prompt);
  }
  return result;
}

