/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_warning @ 0x446f80 */
/* selector: update_warning */

// Advances Player's embedded cRWarning phase and warning-border alpha while gameplay is unpaused, alternating its solid and fade states and replaying the warning cue. Android and iOS retain the same owner role as cRWarning::AI().
void __thiscall update_warning(Warning *warning)
{
  double v1; // st7
  double v2; // st7

  if ( !g_game_base->subgame.subgame_pause_gate && warning->state )
  {
    if ( warning->state == WARNING_STATE_OPAQUE )
    {
      warning->border->hot_text_color.a = 0.99900001;
      v2 = warning->phase_step + warning->phase;
      warning->phase = v2;
      if ( v2 > 1.0 )
      {
        warning->phase = 0.0;
        warning->state = WARNING_STATE_FADING;
      }
    }
    else if ( warning->state == WARNING_STATE_FADING )
    {
      if ( warning->phase >= 0.5 )
        warning->border->hot_text_color.a = 0.0;
      else
        warning->border->hot_text_color.a = 1.0 - (warning->phase + warning->phase);
      v1 = warning->phase_step + warning->phase;
      warning->phase = v1;
      if ( v1 > 1.0 )
      {
        warning->phase = 0.0;
        warning->state = WARNING_STATE_OPAQUE;
        play_sound_effect(&g_sound_effect_manager, 50);
      }
    }
  }
}
