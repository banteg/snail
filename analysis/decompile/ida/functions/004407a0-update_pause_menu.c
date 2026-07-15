/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_pause_menu @ 0x4407a0 */
/* selector: update_pause_menu */

// Dispatches Options, Resume, and End Game clicks from the embedded cRSubPause owner. Cross-port iOS and Android symbols identify the side-effect-only method as cRSubPause::AI(); the Windows reconstruction is exact at 55/55 instructions.
void __thiscall update_pause_menu(SubPause *pause)
{
  FrontendWidgetFlag widget_flags; // eax
  FrontendWidget *resume_widget; // edx
  FrontendWidgetFlag v3; // eax
  FrontendWidget *end_game_widget; // ecx
  FrontendWidgetFlag v5; // eax

  widget_flags = pause->options_widget->widget_flags;
  if ( (widget_flags & 0x20) != 0 )
  {
    LOBYTE(widget_flags) = widget_flags & 0xDF;
    pause->options_widget->widget_flags = widget_flags;
    g_game_base->unknown_000b48[321604] = 0;
    *(_DWORD *)&g_game_base->unknown_000b48[321600] = g_game_base->players[0].frontend_state;
    g_game_base->players[0].frontend_state = 6;
  }
  else
  {
    resume_widget = pause->resume_widget;
    v3 = resume_widget->widget_flags;
    if ( (v3 & 0x20) != 0 )
    {
      LOBYTE(v3) = v3 & 0xDF;
      resume_widget->widget_flags = v3;
      uninit_pause_menu(pause);
      g_game_base->subgame.subgame_state = 2;
      g_game_base->subgame.resume_requested = 1;
    }
    else
    {
      end_game_widget = pause->end_game_widget;
      v5 = end_game_widget->widget_flags;
      if ( (v5 & 0x20) != 0 )
      {
        LOBYTE(v5) = v5 & 0xDF;
        end_game_widget->widget_flags = v5;
        *(_DWORD *)&g_game_base->unknown_000b48[321644] = g_game_base->players[0].frontend_state;
        if ( g_game_base->subgame.level_mode == 7 )
        {
          *(_DWORD *)&g_game_base->unknown_000b48[321636] = 7;
        }
        else if ( g_game_base->subgame.unknown_000044[16721293] == 1 )
        {
          *(_DWORD *)&g_game_base->unknown_000b48[321636] = 3;
        }
        else
        {
          *(_DWORD *)&g_game_base->unknown_000b48[321636] = 2;
        }
        *(_DWORD *)&g_game_base->subgame.unknown_000044[19337092] = 2;
        g_game_base->players[0].frontend_state = 8;
      }
    }
  }
}
