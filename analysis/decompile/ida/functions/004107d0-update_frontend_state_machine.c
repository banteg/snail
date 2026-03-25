/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_frontend_state_machine @ 0x4107d0 */
/* selector: update_frontend_state_machine */

// Dispatches the active front-end screen state, including menu, options, route map, intro, credits, high scores, gameplay handoff, the 26/27/28 subgame bridge states, and the post-run Thanks For Playing owner at states 29/30.
int __thiscall sub_4107D0(int this)
{
  int v2; // eax
  int v3; // eax
  int v4; // eax
  double v5; // st7

  *(_BYTE *)(this + 488) = 1;
  do
  {
    v2 = *(_DWORD *)(this + 148);
    *(_BYTE *)(this + 488) = 0;
    switch ( v2 )
    {
      case 0:
        goto LABEL_10;
      case 1:
        *(_DWORD *)(this + 148) = 0;
        capture_mouse_cursor((float *)(this + 364));
        *((_DWORD *)MEMORY[0x4DF904] + 81079) = 0;
        initialize_new_game_menu((int *)MEMORY[0x4DF904] + 81079);
        break;
      case 2:
        *(_DWORD *)(this + 148) = 0;
        capture_mouse_cursor((float *)(this + 364));
        initialize_new_game_menu((int *)MEMORY[0x4DF904] + 81079);
LABEL_10:
        update_new_game_menu((_BYTE *)MEMORY[0x4DF904] + 324316);
        break;
      case 3:
        *(_DWORD *)(this + 148) = 5;
        capture_mouse_cursor((float *)(this + 364));
        initialize_main_menu((int *)MEMORY[0x4DF904] + 81097);
        break;
      case 4:
        *(_DWORD *)(this + 148) = 5;
        capture_mouse_cursor((float *)(this + 364));
        initialize_main_menu((int *)MEMORY[0x4DF904] + 81097);
        goto LABEL_13;
      case 5:
LABEL_13:
        update_main_menu((_DWORD *)MEMORY[0x4DF904] + 81097);
        break;
      case 6:
        *(_DWORD *)(this + 148) = 7;
        initialize_options_menu((int)MEMORY[0x4DF904] + 324488);
        goto LABEL_15;
      case 7:
LABEL_15:
        update_options_menu((int)MEMORY[0x4DF904] + 324488, 32);
        break;
      case 8:
        initialize_exit_prompt((char *)MEMORY[0x4DF904] + 324524);
        *(_DWORD *)(this + 148) = 9;
        goto LABEL_17;
      case 9:
LABEL_17:
        update_completion_screen((_DWORD *)MEMORY[0x4DF904] + 81131);
        break;
      case 10:
        *((_DWORD *)MEMORY[0x4DF904] + 4267083) = 0;
        initialize_subgame((int)MEMORY[0x4DF904] + 476696);
        *(_DWORD *)(this + 148) = 11;
        goto LABEL_4;
      case 11:
LABEL_4:
        update_subgame((int)MEMORY[0x4DF904] + 476696);
        break;
      case 12:
        initialize_intro_screen((_DWORD *)MEMORY[0x4DF904] + 81152, aIntroIntroTxt);
        *(_DWORD *)(this + 148) = 13;
        break;
      case 13:
      case 15:
        update_intro_screen((int)MEMORY[0x4DF904] + 324608);
        break;
      case 14:
        initialize_intro_screen((_DWORD *)MEMORY[0x4DF904] + 81152, aIntroCreditsTx);
        *(_DWORD *)(this + 148) = 15;
        break;
      case 18:
        initialize_high_score_screen((int)MEMORY[0x4DF904] + 19820112, unk_4DF9C0, -1);
        *(_DWORD *)(this + 148) = 19;
        break;
      case 19:
      case 21:
        update_high_score_screen((int)MEMORY[0x4DF904] + 19820112);
        break;
      case 20:
        initialize_high_score_screen(
          (int)MEMORY[0x4DF904] + 19820112,
          *((_DWORD *)MEMORY[0x4DF904] + 197),
          *((_DWORD *)MEMORY[0x4DF904] + 196));
        *(_DWORD *)(this + 148) = 21;
        break;
      case 25:
        *((_DWORD *)MEMORY[0x4DF904] + 14) = 1;
        break;
      case 26:
        destroy_subgame((int)MEMORY[0x4DF904] + 476696);
        goto LABEL_26;
      case 27:
        destroy_subgame((int)MEMORY[0x4DF904] + 476696);
        goto LABEL_25;
      case 28:
        destroy_subgame((int)MEMORY[0x4DF904] + 476696);
        *((_DWORD *)MEMORY[0x4DF904] + 4953464) = 0;
LABEL_25:
        initialize_subgame((int)MEMORY[0x4DF904] + 476696);
LABEL_26:
        v3 = *(_DWORD *)(this + 152);
        if ( v3 != -1 )
          *(_DWORD *)(this + 148) = v3;
        break;
      case 29:
        *(_DWORD *)(this + 148) = 30;
        initialize_thanks_for_playing_screen((int *)MEMORY[0x4DF904] + 4936073);
        goto LABEL_29;
      case 30:
LABEL_29:
        update_thanks_for_playing_screen((int)MEMORY[0x4DF904] + 19744292);
        break;
      case 31:
        *(_DWORD *)(this + 148) = 32;
        initialize_help_screen((int *)MEMORY[0x4DF904] + 4936072);
        goto LABEL_31;
      case 32:
LABEL_31:
        update_help_screen((char *)MEMORY[0x4DF904] + 19744288);
        break;
      default:
        break;
    }
  }
  while ( *(_BYTE *)(this + 488) == 1 );
  v4 = *(_DWORD *)(this + 360);
  *(float *)(this + 376) = *(float *)(v4 + 96);
  v5 = *(float *)(v4 + 100);
  qmemcpy((void *)(this + 216), (const void *)(this + 56), 0x40u);
  *(float *)(this + 380) = v5;
  return invert_matrix_from_source((float *)(this + 288), (float *)(this + 56));
}

