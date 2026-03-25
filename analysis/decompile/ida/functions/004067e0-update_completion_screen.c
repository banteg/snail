/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_completion_screen @ 0x4067e0 */
/* selector: update_completion_screen */

// Runs the completion-screen state machine, including continue, replay, route-map return, and outbound-link actions. Cross-port Android and iOS symbols match this helper to `cRCompletion::AI()`.
int __thiscall update_completion_screen(_DWORD *this)
{
  int v2; // ecx
  int v3; // eax
  int v4; // ecx
  int v5; // eax
  int v6; // ecx
  int v7; // eax
  int v8; // ecx
  int v9; // eax
  int v10; // eax
  int v11; // ecx
  int v12; // eax
  int v13; // ecx
  int v14; // eax
  int v15; // ecx
  int v16; // eax
  int v17; // ecx
  int v18; // eax
  int v19; // ecx
  int result; // eax

  switch ( *this )
  {
    case 2:
      v8 = *(this + 5);
      v9 = *(_DWORD *)(v8 + 416);
      if ( (v9 & 0x20) != 0 )
      {
        LOBYTE(v9) = v9 & 0xDF;
        *(_DWORD *)(v8 + 416) = v9;
        complete_subgame((int)MEMORY[0x4DF904] + 476696, 1);
        if ( *((_BYTE *)MEMORY[0x4DF904] + 781) == 1 )
        {
          *(this + 2) = *((_DWORD *)MEMORY[0x4DF904] + 110);
          destroy_completion_screen((int)this);
          uninit_pause_menu((_DWORD **)MEMORY[0x4DF904] + 119179);
          *((_BYTE *)MEMORY[0x4DF904] + 476705) = 0;
          set_sprite_manager_paused(unk_790F30, 0);
          destroy_subgame((int)MEMORY[0x4DF904] + 476696);
        }
        else
        {
          destroy_completion_screen((int)this);
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
      v13 = *(this + 5);
      v14 = *(_DWORD *)(v13 + 416);
      if ( (v14 & 0x20) != 0 )
      {
        LOBYTE(v14) = v14 & 0xDF;
        *(_DWORD *)(v13 + 416) = v14;
        destroy_completion_screen((int)this);
        uninit_pause_menu((_DWORD **)MEMORY[0x4DF904] + 119179);
        *((_BYTE *)MEMORY[0x4DF904] + 476705) = 0;
        set_sprite_manager_paused(unk_790F30, 0);
        destroy_subgame((int)MEMORY[0x4DF904] + 476696);
        *((_DWORD *)MEMORY[0x4DF904] + 110) = *((_DWORD *)MEMORY[0x4DF904] + 4299516);
      }
      break;
    case 4:
      v15 = *(this + 5);
      v16 = *(_DWORD *)(v15 + 416);
      if ( (v16 & 0x20) != 0 )
      {
        LOBYTE(v16) = v16 & 0xDF;
        *(_DWORD *)(v15 + 416) = v16;
        goto LABEL_23;
      }
      break;
    case 7:
      v11 = *(this + 5);
      v12 = *(_DWORD *)(v11 + 416);
      if ( (v12 & 0x20) != 0 )
      {
        LOBYTE(v12) = v12 & 0xDF;
        *(_DWORD *)(v11 + 416) = v12;
        destroy_completion_screen((int)this);
        uninit_pause_menu((_DWORD **)MEMORY[0x4DF904] + 119179);
        *((_BYTE *)MEMORY[0x4DF904] + 476705) = 0;
        set_sprite_manager_paused(unk_790F30, 0);
        goto LABEL_24;
      }
      break;
    case 8:
      update_new_game_menu((_BYTE *)MEMORY[0x4DF904] + 324316);
      v17 = *(this + 5);
      v18 = *(_DWORD *)(v17 + 416);
      if ( (v18 & 0x20) != 0 )
      {
        LOBYTE(v18) = v18 & 0xDF;
        *(_DWORD *)(v17 + 416) = v18;
        sub_433050(aAlpha72Url);
        *((_DWORD *)MEMORY[0x4DF904] + 110) = 0;
        *((_BYTE *)MEMORY[0x4DF904] + 1384) = 0;
        destroy_completion_screen((int)this);
      }
      break;
    case 9:
      v2 = *(this + 5);
      v3 = *(_DWORD *)(v2 + 416);
      if ( (v3 & 0x20) != 0 )
      {
        LOBYTE(v3) = v3 & 0xDF;
        *(_DWORD *)(v2 + 416) = v3;
        destroy_completion_screen((int)this);
        *((_DWORD *)MEMORY[0x4DF904] + 14) = 3;
      }
      break;
    case 0xA:
      update_main_menu((_DWORD *)MEMORY[0x4DF904] + 81097);
      v4 = *(this + 5);
      v5 = *(_DWORD *)(v4 + 416);
      if ( (v5 & 0x20) != 0 )
      {
        LOBYTE(v5) = v5 & 0xDF;
        *(_DWORD *)(v4 + 416) = v5;
        destroy_completion_screen((int)this);
        destroy_main_menu();
        if ( !*((_DWORD *)MEMORY[0x4DF904] + 14) )
          *((_DWORD *)MEMORY[0x4DF904] + 14) = 1;
      }
      break;
    case 0xB:
      update_galaxy((int)MEMORY[0x4DF904] + 19744312);
      v6 = *(this + 5);
      v7 = *(_DWORD *)(v6 + 416);
      if ( (v7 & 0x20) != 0 )
      {
        LOBYTE(v7) = v7 & 0xDF;
        *(_DWORD *)(v6 + 416) = v7;
        destroy_galaxy((_DWORD **)MEMORY[0x4DF904] + 4936078);
        complete_subgame((int)MEMORY[0x4DF904] + 476696, 1);
        if ( *((_BYTE *)MEMORY[0x4DF904] + 781) == 1 )
        {
          *(this + 2) = *((_DWORD *)MEMORY[0x4DF904] + 110);
          destroy_completion_screen((int)this);
          destroy_subgame((int)MEMORY[0x4DF904] + 476696);
        }
        else
        {
LABEL_23:
          destroy_completion_screen((int)this);
LABEL_24:
          destroy_subgame((int)MEMORY[0x4DF904] + 476696);
          *((_DWORD *)MEMORY[0x4DF904] + 110) = 2;
        }
      }
      break;
    default:
      break;
  }
  v19 = *(this + 6);
  result = *(_DWORD *)(v19 + 416);
  if ( (result & 0x20) != 0 )
  {
    LOBYTE(result) = result & 0xDF;
    *(_DWORD *)(v19 + 416) = result;
    *((_DWORD *)MEMORY[0x4DF904] + 110) = *(this + 2);
    *((_BYTE *)MEMORY[0x4DF904] + 1384) = 0;
    return destroy_completion_screen((int)this);
  }
  return result;
}

