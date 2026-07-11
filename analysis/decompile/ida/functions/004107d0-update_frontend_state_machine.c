/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_frontend_state_machine @ 0x4107d0 */
/* selector: update_frontend_state_machine */

// Dispatches the active front-end screen state, including menu, options, route map, intro, credits, high scores, gameplay handoff, the 26/27/28 subgame bridge states, and the post-run Thanks For Playing owner at states 29/30.
int __thiscall update_frontend_state_machine(GamePlayer *player)
{
  TransformMatrix *v1; // edx
  int32_t frontend_state; // eax
  int32_t saved_frontend_state; // eax
  GameInput *game_input; // eax
  double authored_y; // st7

  player->redispatch_requested = 1;
  do
  {
    frontend_state = player->frontend_state;
    player->redispatch_requested = 0;
    switch ( frontend_state )
    {
      case 0:
        goto LABEL_10;
      case 1:
        player->frontend_state = 0;
        capture_mouse_cursor(&player->mouse_cursor);
        *((_DWORD *)g_game_base + 81079) = 0;
        initialize_new_game_menu((NewGameMenu *)((char *)g_game_base + 324316));
        break;
      case 2:
        player->frontend_state = 0;
        capture_mouse_cursor(&player->mouse_cursor);
        initialize_new_game_menu((NewGameMenu *)((char *)g_game_base + 324316));
LABEL_10:
        update_new_game_menu((NewGameMenu *)((char *)g_game_base + 324316));
        break;
      case 3:
        player->frontend_state = 5;
        capture_mouse_cursor(&player->mouse_cursor);
        initialize_main_menu((int *)g_game_base + 81097);
        break;
      case 4:
        player->frontend_state = 5;
        capture_mouse_cursor(&player->mouse_cursor);
        initialize_main_menu((int *)g_game_base + 81097);
        goto LABEL_13;
      case 5:
LABEL_13:
        update_main_menu((_DWORD *)g_game_base + 81097);
        break;
      case 6:
        player->frontend_state = 7;
        initialize_options_menu((int)g_game_base + 324488);
        goto LABEL_15;
      case 7:
LABEL_15:
        update_options_menu((int)g_game_base + 324488, 32);
        break;
      case 8:
        initialize_exit_prompt((CompletionPrompt *)((char *)g_game_base + 324524));
        player->frontend_state = 9;
        goto LABEL_17;
      case 9:
LABEL_17:
        update_completion_screen((CompletionPrompt *)((char *)g_game_base + 324524));
        break;
      case 10:
        *((_DWORD *)g_game_base + 4267083) = 0;
        initialize_subgame((int)g_game_base + 476696);
        player->frontend_state = 11;
        goto LABEL_4;
      case 11:
LABEL_4:
        update_subgame((int)g_game_base + 476696);
        break;
      case 12:
        initialize_intro_screen((float *)g_game_base + 81152, g_intro_intro_script_path);
        player->frontend_state = 13;
        break;
      case 13:
      case 15:
        update_intro_screen((int)g_game_base + 324608);
        break;
      case 14:
        initialize_intro_screen((float *)g_game_base + 81152, g_intro_credits_script_path);
        player->frontend_state = 15;
        break;
      case 18:
        initialize_high_score_screen((int)g_game_base + 19820112, g_high_score_selected_bank, -1);
        player->frontend_state = 19;
        break;
      case 19:
      case 21:
        update_high_score_screen((HighScoreScreen *)g_game_base + 95289);
        break;
      case 20:
        initialize_high_score_screen(
          (int)g_game_base + 19820112,
          *((_DWORD *)g_game_base + 197),
          *((_DWORD *)g_game_base + 196));
        player->frontend_state = 21;
        break;
      case 25:
        *((_DWORD *)g_game_base + 14) = 1;
        break;
      case 26:
        destroy_subgame((int)g_game_base + 476696);
        goto LABEL_26;
      case 27:
        destroy_subgame((int)g_game_base + 476696);
        goto LABEL_25;
      case 28:
        destroy_subgame((int)g_game_base + 476696);
        *((_DWORD *)g_game_base + 4953464) = 0;
LABEL_25:
        initialize_subgame((int)g_game_base + 476696);
LABEL_26:
        saved_frontend_state = player->saved_frontend_state;
        if ( saved_frontend_state != -1 )
          player->frontend_state = saved_frontend_state;
        break;
      case 29:
        player->frontend_state = 30;
        initialize_thanks_for_playing_screen((int *)g_game_base + 4936073);
        goto LABEL_29;
      case 30:
LABEL_29:
        update_thanks_for_playing_screen((int)g_game_base + 19744292);
        break;
      case 31:
        player->frontend_state = 32;
        initialize_help_screen((FrontendWidget **)g_game_base + 4936072);
        goto LABEL_31;
      case 32:
LABEL_31:
        update_help_screen((char *)g_game_base + 19744288);
        break;
      default:
        break;
    }
  }
  while ( player->redispatch_requested == 1 );
  game_input = player->game_input;
  player->mouse_cursor.saved_x = game_input->input.authored_x;
  authored_y = game_input->input.authored_y;
  qmemcpy(&player->camera.transform, &player->transform, sizeof(player->camera.transform));
  player->mouse_cursor.saved_y = authored_y;
  return (int)invert_matrix_from_source((TransformMatrix *)&player->camera.view_matrix, v1);
}

