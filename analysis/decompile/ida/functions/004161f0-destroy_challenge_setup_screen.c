/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: destroy_challenge_setup_screen @ 0x4161f0 */
/* selector: destroy_challenge_setup_screen */

// Implements `cRGUI::UnInit()`: tears down the cRGUI widget set selected by gameplay mode 0, 1, or 4, including optional replay and challenge slider controls.
void __thiscall destroy_challenge_setup_screen(GUI *gui)
{
  int32_t level_mode; // eax
  int v3; // eax

  level_mode = gui->game->level_mode;
  if ( level_mode )
  {
    v3 = level_mode - 1;
    if ( v3 )
    {
      if ( v3 == 3 )
      {
        kill_border(&g_game_base->border_manager, gui->next_level_button);
        kill_border(&g_game_base->border_manager, gui->previous_level_button);
        kill_border(&g_game_base->border_manager, gui->level_name_widget);
        kill_border(&g_game_base->border_manager, gui->play_button);
        kill_border(&g_game_base->border_manager, gui->back_button);
        kill_border(&g_game_base->border_manager, gui->replay_button);
      }
    }
    else
    {
      kill_border(&g_game_base->border_manager, gui->play_button);
      kill_border(&g_game_base->border_manager, gui->back_button);
      kill_border(&g_game_base->border_manager, gui->speed_slider);
      kill_border(&g_game_base->border_manager, gui->difficulty_slider);
      kill_border(&g_game_base->border_manager, gui->replay_button);
    }
  }
  else
  {
    kill_border(&g_game_base->border_manager, gui->next_level_button);
    kill_border(&g_game_base->border_manager, gui->previous_level_button);
    kill_border(&g_game_base->border_manager, gui->level_name_widget);
    kill_border(&g_game_base->border_manager, gui->play_button);
    kill_border(&g_game_base->border_manager, gui->back_button);
  }
}
