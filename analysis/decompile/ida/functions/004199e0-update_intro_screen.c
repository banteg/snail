/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_intro_screen @ 0x4199e0 */
/* selector: update_intro_screen */

// Exact Windows `cRLogo::AI()`: advances the normalized intro or credits crawl, tears down its LogoLetters once scrolling completes, and exits early on skip input.
void __thiscall update_intro_screen(Logo *logo)
{
  int32_t state; // eax
  double v3; // st7
  double v4; // st7

  if ( !g_game_base->fade.state
    && ((g_game_base->players[0].game_input->input.pressed_buttons & 0x4000) != 0
     || read_pressed_text_input_key_code() == 11) )
  {
    begin_frontend_fade_out(&g_game_base->fade.state, 0);
  }
  if ( g_game_base->fade.state == 4 )
    destroy_intro_screen(logo);
  state = logo->state;
  if ( state )
  {
    if ( state == 1 )
    {
      v3 = logo->progress_step + logo->progress;
      logo->progress = v3;
      if ( v3 > 1.0 )
      {
        begin_frontend_fade_out(&g_game_base->fade.state, 0);
        ++logo->state;
      }
    }
  }
  else
  {
    v4 = logo->duration_seconds * 60.0;
    logo->progress = 0.0;
    logo->state = 1;
    logo->progress_step = 1.0 / v4;
  }
}
