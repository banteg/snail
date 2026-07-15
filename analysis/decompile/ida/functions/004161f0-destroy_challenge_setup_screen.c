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
        kill_border(&gui->next_level_button->list_kind);
        kill_border(&gui->previous_level_button->list_kind);
        kill_border(&gui->level_name_widget->list_kind);
        kill_border(&gui->play_button->list_kind);
        kill_border(&gui->back_button->list_kind);
        kill_border(&gui->replay_button->list_kind);
      }
    }
    else
    {
      kill_border(&gui->play_button->list_kind);
      kill_border(&gui->back_button->list_kind);
      kill_border(&gui->speed_slider->list_kind);
      kill_border(&gui->difficulty_slider->list_kind);
      kill_border(&gui->replay_button->list_kind);
    }
  }
  else
  {
    kill_border(&gui->next_level_button->list_kind);
    kill_border(&gui->previous_level_button->list_kind);
    kill_border(&gui->level_name_widget->list_kind);
    kill_border(&gui->play_button->list_kind);
    kill_border(&gui->back_button->list_kind);
  }
}
