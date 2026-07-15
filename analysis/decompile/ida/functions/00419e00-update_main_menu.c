/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_main_menu @ 0x419e00 */
/* selector: update_main_menu */

// Handles main-menu selection, front-end screen transitions, and the tutorial launch handoff. Cross-port Android and iOS symbols match this helper to `cRMainMenu::AI()`.
void __thiscall update_main_menu(MainMenu *menu)
{
  FrontendWidgetFlag widget_flags; // eax
  FrontendWidget *credits_widget; // edx
  FrontendWidgetFlag v3; // eax
  FrontendWidget *exit_widget; // edx
  FrontendWidgetFlag v5; // eax
  FrontendWidget *options_widget; // edx
  FrontendWidgetFlag v7; // eax
  FrontendWidget *high_scores_widget; // edx
  FrontendWidgetFlag v9; // eax

  widget_flags = menu->new_game_widget->widget_flags;
  if ( (widget_flags & 0x20) != 0 )
  {
    LOBYTE(widget_flags) = widget_flags & 0xDF;
    menu->new_game_widget->widget_flags = widget_flags;
    destroy_main_menu(menu);
    g_game_base->players[0].frontend_state = 2;
    g_game_base->players[0].redispatch_requested = 1;
  }
  else
  {
    credits_widget = menu->credits_widget;
    v3 = credits_widget->widget_flags;
    if ( (v3 & 0x20) != 0 )
    {
      LOBYTE(v3) = v3 & 0xDF;
      credits_widget->widget_flags = v3;
      destroy_main_menu(menu);
      g_game_base->players[0].frontend_state = 14;
      g_game_base->players[0].redispatch_requested = 1;
    }
    else
    {
      exit_widget = menu->exit_widget;
      v5 = exit_widget->widget_flags;
      if ( (v5 & 0x20) != 0 )
      {
        LOBYTE(v5) = v5 & 0xDF;
        exit_widget->widget_flags = v5;
        g_game_base->exit_controller.previous_frontend_state = g_game_base->players[0].frontend_state;
        g_game_base->exit_controller.prompt_y = menu->exit_widget->layout_top;
        g_game_base->exit_controller.state = 10;
        g_game_base->players[0].frontend_state = 8;
      }
      else
      {
        options_widget = menu->options_widget;
        v7 = options_widget->widget_flags;
        if ( (v7 & 0x20) != 0 )
        {
          LOBYTE(v7) = v7 & 0xDF;
          options_widget->widget_flags = v7;
          g_game_base->options.active = 1;
          g_game_base->options.previous_frontend_state = g_game_base->players[0].frontend_state;
          g_game_base->players[0].frontend_state = 6;
        }
        else
        {
          high_scores_widget = menu->high_scores_widget;
          v9 = high_scores_widget->widget_flags;
          if ( (v9 & 0x20) != 0 )
          {
            LOBYTE(v9) = v9 & 0xDF;
            high_scores_widget->widget_flags = v9;
            destroy_main_menu(menu);
            g_game_base->players[0].frontend_state = 18;
            g_game_base->high_score.mode = 0;
          }
        }
      }
    }
  }
}
