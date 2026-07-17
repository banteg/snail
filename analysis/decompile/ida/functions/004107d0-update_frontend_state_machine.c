/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_frontend_state_machine @ 0x4107d0 */
/* selector: update_frontend_state_machine */

// Runs cRPlayer::AI: dispatches the active front-end screen state, including menu, options, route map, intro, credits, high scores, gameplay handoff, the 26/27/28 subgame bridge states, and states 29/30, then snapshots the owned player transform into its cRCamera and refreshes the embedded MouseCursorState saved position from the active camera anchor.
void __thiscall update_frontend_state_machine(GamePlayer *player)
{
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
        g_game_base->intro.replay_attract_bank_cursor = 0;
        initialize_new_game_menu(&g_game_base->intro);
        break;
      case 2:
        player->frontend_state = 0;
        capture_mouse_cursor(&player->mouse_cursor);
        initialize_new_game_menu(&g_game_base->intro);
LABEL_10:
        update_new_game_menu(&g_game_base->intro);
        break;
      case 3:
        player->frontend_state = 5;
        capture_mouse_cursor(&player->mouse_cursor);
        initialize_main_menu(&g_game_base->main_menu);
        break;
      case 4:
        player->frontend_state = 5;
        capture_mouse_cursor(&player->mouse_cursor);
        initialize_main_menu(&g_game_base->main_menu);
        goto LABEL_13;
      case 5:
LABEL_13:
        update_main_menu(&g_game_base->main_menu);
        break;
      case 6:
        player->frontend_state = 7;
        initialize_options_menu(&g_game_base->options);
        goto LABEL_15;
      case 7:
LABEL_15:
        update_options_menu(&g_game_base->options);
        break;
      case 8:
        initialize_exit_prompt(&g_game_base->exit_controller);
        player->frontend_state = 9;
        goto LABEL_17;
      case 9:
LABEL_17:
        update_completion_screen(&g_game_base->exit_controller);
        break;
      case 10:
        g_game_base->subgame.current_high_score_record.score = 0;
        initialize_subgame(&g_game_base->subgame);
        player->frontend_state = 11;
        goto LABEL_4;
      case 11:
LABEL_4:
        update_subgame(&g_game_base->subgame);
        break;
      case 12:
        initialize_intro_screen(&g_game_base->logo, g_intro_intro_script_path);
        player->frontend_state = 13;
        break;
      case 13:
      case 15:
        update_intro_screen(&g_game_base->logo);
        break;
      case 14:
        initialize_intro_screen(&g_game_base->logo, g_intro_credits_script_path);
        player->frontend_state = 15;
        break;
      case 18:
        initialize_high_score_screen(&g_game_base->high_score, g_runtime_config.high_score_selected_bank, -1);
        player->frontend_state = 19;
        break;
      case 19:
      case 21:
        update_high_score_screen(&g_game_base->high_score);
        break;
      case 20:
        initialize_high_score_screen(
          &g_game_base->high_score,
          g_game_base->players[0].selected_high_score_mode,
          g_game_base->players[0].selected_high_score_rank);
        player->frontend_state = 21;
        break;
      case 25:
        g_game_base->frontend_quit_requested = 1;
        break;
      case 26:
        destroy_subgame(&g_game_base->subgame);
        goto LABEL_26;
      case 27:
        destroy_subgame(&g_game_base->subgame);
        goto LABEL_25;
      case 28:
        destroy_subgame(&g_game_base->subgame);
        g_game_base->subgame.subgame_rebuild_selector = 0;
LABEL_25:
        initialize_subgame(&g_game_base->subgame);
LABEL_26:
        saved_frontend_state = player->saved_frontend_state;
        if ( saved_frontend_state != -1 )
          player->frontend_state = saved_frontend_state;
        break;
      case 29:
        player->frontend_state = 30;
        initialize_thanks_for_playing_screen((int *)&g_game_base->subgame.thanks_screen);
        goto LABEL_29;
      case 30:
LABEL_29:
        update_thanks_for_playing_screen((int)&g_game_base->subgame.thanks_screen);
        break;
      case 31:
        player->frontend_state = 32;
        initialize_help_screen(&g_game_base->subgame.help.back_button);
        goto LABEL_31;
      case 32:
LABEL_31:
        update_help_screen(&g_game_base->subgame.help);
        break;
      default:
        break;
    }
  }
  while ( player->redispatch_requested == 1 );
  game_input = player->game_input;
  player->mouse_cursor.saved_x = game_input->input.authored_x;
  authored_y = game_input->input.authored_y;
  qmemcpy(&player->camera.body.transform, &player->body.transform, sizeof(player->camera.body.transform));
  player->mouse_cursor.saved_y = authored_y;
  invert_matrix_from_source(
    (TransformMatrix *)&player->camera.view_matrix,
    (const TransformMatrix *)&player->body.transform);
}
