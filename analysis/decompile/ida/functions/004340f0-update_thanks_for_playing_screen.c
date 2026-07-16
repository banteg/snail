/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_thanks_for_playing_screen @ 0x4340f0 */
/* selector: update_thanks_for_playing_screen */

// Runs the post-run Thanks For Playing message sequence, including the Challenge Mode and Time Trial prompts, Click to Continue, and the fade-out handoff back through the saved front-end return state.
void __thiscall update_thanks_for_playing_screen(int this)
{
  double v2; // st7
  int v3; // eax
  FrontendWidget *v4; // ecx
  int v5; // edx
  FrontendWidget *v6; // ecx
  int v7; // eax
  FrontendWidget *v8; // ecx
  int v9; // ecx

  if ( ((g_game_base->players[0].game_input->input.pressed_buttons & 0x4000) != 0
     || read_pressed_text_input_key_code() == 11)
    && *(int *)(this + 8) >= 2
    && !g_game_base->fade.state )
  {
    play_sound_effect(8);
    begin_frontend_fade_out(&g_game_base->fade.state, 0);
  }
  if ( g_game_base->fade.state == 4 )
    uninit_thanks_screen((_DWORD **)this);
  v2 = *(float *)(this + 12) + *(float *)(this + 16);
  *(float *)(this + 12) = v2;
  if ( v2 > 1.0 )
  {
    v3 = *(_DWORD *)(this + 8);
    *(_DWORD *)(this + 12) = 0;
    switch ( v3 )
    {
      case 0:
        v4 = *(FrontendWidget **)(this + 4);
        *(_DWORD *)(this + 8) = 1;
        *(_DWORD *)(this + 16) = 1023969417;
        hide_border_init(v4);
        return;
      case 1:
        v5 = *(_DWORD *)(this + 4);
        *(_DWORD *)(this + 8) = 2;
        *(_DWORD *)(this + 16) = 998803593;
        rstrcpy_checked_ascii((char *)(v5 + 716), aTestYourReflex);
        goto LABEL_16;
      case 2:
        v6 = *(FrontendWidget **)(this + 4);
        *(_DWORD *)(this + 8) = 3;
        *(_DWORD *)(this + 16) = 1023969417;
        hide_border_init(v6);
        return;
      case 3:
        v7 = *(_DWORD *)(this + 4);
        *(_DWORD *)(this + 8) = 4;
        *(_DWORD *)(this + 16) = 998803593;
        rstrcpy_checked_ascii((char *)(v7 + 716), aImproveYourSki);
        goto LABEL_16;
      case 4:
        v8 = *(FrontendWidget **)(this + 4);
        *(_DWORD *)(this + 8) = 5;
        *(_DWORD *)(this + 16) = 1023969417;
        hide_border_init(v8);
        return;
      case 5:
        v9 = *(_DWORD *)(this + 4);
        *(_DWORD *)(this + 8) = 6;
        *(_DWORD *)(this + 16) = 998803593;
        rstrcpy_checked_ascii((char *)(v9 + 716), g_click_to_continue_text);
LABEL_16:
        unhide_border_init(*(FrontendWidget **)(this + 4));
        return;
      case 6:
        *(_DWORD *)(this + 8) = 7;
        goto LABEL_18;
      case 7:
LABEL_18:
        *(_DWORD *)(this + 16) = 0;
        break;
      default:
        return;
    }
  }
}
