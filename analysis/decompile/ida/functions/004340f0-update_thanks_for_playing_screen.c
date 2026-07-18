/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_thanks_for_playing_screen @ 0x4340f0 */
/* selector: update_thanks_for_playing_screen */

// Runs the post-run Thanks For Playing message sequence, including the Challenge Mode and Time Trial prompts, Click to Continue, and the fade-out handoff back through the saved front-end return state.
void __thiscall update_thanks_for_playing_screen(ThanksScreen *thanks_screen)
{
  double v2; // st7
  int32_t message_state; // eax
  FrontendWidget *message_widget; // ecx
  FrontendWidget *v5; // edx
  FrontendWidget *v6; // ecx
  FrontendWidget *v7; // eax
  FrontendWidget *v8; // ecx
  FrontendWidget *v9; // ecx

  if ( ((g_game_base->players[0].game_input->input.pressed_buttons & 0x4000) != 0
     || read_pressed_text_input_key_code() == 11)
    && thanks_screen->message_state >= 2
    && !g_game_base->fade.state )
  {
    play_sound_effect(&g_sound_effect_manager, 8);
    begin_frontend_fade_out(&g_game_base->fade.state, 0);
  }
  if ( g_game_base->fade.state == 4 )
    uninit_thanks_screen(thanks_screen);
  v2 = thanks_screen->message_progress + thanks_screen->message_progress_step;
  thanks_screen->message_progress = v2;
  if ( v2 > 1.0 )
  {
    message_state = thanks_screen->message_state;
    thanks_screen->message_progress = 0.0;
    switch ( message_state )
    {
      case 0:
        message_widget = thanks_screen->message_widget;
        thanks_screen->message_state = 1;
        thanks_screen->message_progress_step = 0.033333335;
        hide_border_init(message_widget);
        return;
      case 1:
        v5 = thanks_screen->message_widget;
        thanks_screen->message_state = 2;
        thanks_screen->message_progress_step = 0.0041666669;
        rstrcpy_checked_ascii((char *)&v5->text_buffer, aTestYourReflex);
        goto LABEL_16;
      case 2:
        v6 = thanks_screen->message_widget;
        thanks_screen->message_state = 3;
        thanks_screen->message_progress_step = 0.033333335;
        hide_border_init(v6);
        return;
      case 3:
        v7 = thanks_screen->message_widget;
        thanks_screen->message_state = 4;
        thanks_screen->message_progress_step = 0.0041666669;
        rstrcpy_checked_ascii((char *)&v7->text_buffer, aImproveYourSki);
        goto LABEL_16;
      case 4:
        v8 = thanks_screen->message_widget;
        thanks_screen->message_state = 5;
        thanks_screen->message_progress_step = 0.033333335;
        hide_border_init(v8);
        return;
      case 5:
        v9 = thanks_screen->message_widget;
        thanks_screen->message_state = 6;
        thanks_screen->message_progress_step = 0.0041666669;
        rstrcpy_checked_ascii((char *)&v9->text_buffer, g_click_to_continue_text);
LABEL_16:
        unhide_border_init(thanks_screen->message_widget);
        return;
      case 6:
        thanks_screen->message_state = 7;
        goto LABEL_18;
      case 7:
LABEL_18:
        thanks_screen->message_progress_step = 0.0;
        break;
      default:
        return;
    }
  }
}
