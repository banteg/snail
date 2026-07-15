/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_completion_screen @ 0x4067e0 */
/* selector: update_completion_screen */

// Exact void Windows `Exit::update_completion_screen` state machine for continue, replay, route-map return, and outbound-link actions. Android and iOS retain `cRExit::AI()`; it is distinct from embedded `cRCompletion::AI()` at 0x404cf0.
void __thiscall update_completion_screen(Exit *exit_controller)
{
  FrontendWidget *v2; // ecx
  FrontendWidgetFlag v3; // eax
  FrontendWidget *v4; // ecx
  FrontendWidgetFlag v5; // eax
  FrontendWidget *v6; // ecx
  FrontendWidgetFlag v7; // eax
  FrontendWidget *yes_button; // ecx
  FrontendWidgetFlag widget_flags; // eax
  int32_t level_mode; // eax
  FrontendWidget *v11; // ecx
  FrontendWidgetFlag v12; // eax
  FrontendWidget *v13; // ecx
  FrontendWidgetFlag v14; // eax
  FrontendWidget *v15; // ecx
  FrontendWidgetFlag v16; // eax
  FrontendWidget *v17; // ecx
  FrontendWidgetFlag v18; // eax
  FrontendWidget *no_button; // ecx
  FrontendWidgetFlag v20; // eax

  switch ( exit_controller->state )
  {
    case 2:
      yes_button = exit_controller->yes_button;
      widget_flags = yes_button->widget_flags;
      if ( (widget_flags & 0x20) != 0 )
      {
        LOBYTE(widget_flags) = widget_flags & 0xDF;
        yes_button->widget_flags = widget_flags;
        complete_subgame(&g_game_base->subgame, 1u);
        if ( g_game_base->players[0].high_score_entry_pending == 1 )
        {
          exit_controller->previous_frontend_state = g_game_base->players[0].frontend_state;
          destroy_completion_screen(exit_controller);
          uninit_pause_menu(&g_game_base->subgame.sub_pause);
          g_game_base->subgame.subgame_pause_gate = 0;
          set_sprite_manager_paused(g_sprite_manager, 0);
          destroy_subgame(&g_game_base->subgame);
        }
        else
        {
          destroy_completion_screen(exit_controller);
          uninit_pause_menu(&g_game_base->subgame.sub_pause);
          g_game_base->subgame.subgame_pause_gate = 0;
          set_sprite_manager_paused(g_sprite_manager, 0);
          destroy_subgame(&g_game_base->subgame);
          level_mode = g_game_base->subgame.level_mode;
          if ( level_mode == 4 || level_mode == 1 )
            initialize_subgame(&g_game_base->subgame);
          else
            g_game_base->players[0].frontend_state = 2;
        }
      }
      break;
    case 3:
      v13 = exit_controller->yes_button;
      v14 = v13->widget_flags;
      if ( (v14 & 0x20) != 0 )
      {
        LOBYTE(v14) = v14 & 0xDF;
        v13->widget_flags = v14;
        destroy_completion_screen(exit_controller);
        uninit_pause_menu(&g_game_base->subgame.sub_pause);
        g_game_base->subgame.subgame_pause_gate = 0;
        set_sprite_manager_paused(g_sprite_manager, 0);
        destroy_subgame(&g_game_base->subgame);
        g_game_base->players[0].frontend_state = g_game_base->subgame.selected_level_record_cursor;
      }
      break;
    case 4:
      v15 = exit_controller->yes_button;
      v16 = v15->widget_flags;
      if ( (v16 & 0x20) != 0 )
      {
        LOBYTE(v16) = v16 & 0xDF;
        v15->widget_flags = v16;
        goto LABEL_23;
      }
      break;
    case 7:
      v11 = exit_controller->yes_button;
      v12 = v11->widget_flags;
      if ( (v12 & 0x20) != 0 )
      {
        LOBYTE(v12) = v12 & 0xDF;
        v11->widget_flags = v12;
        destroy_completion_screen(exit_controller);
        uninit_pause_menu(&g_game_base->subgame.sub_pause);
        g_game_base->subgame.subgame_pause_gate = 0;
        set_sprite_manager_paused(g_sprite_manager, 0);
        goto LABEL_24;
      }
      break;
    case 8:
      update_new_game_menu(&g_game_base->intro);
      v17 = exit_controller->yes_button;
      v18 = v17->widget_flags;
      if ( (v18 & 0x20) != 0 )
      {
        LOBYTE(v18) = v18 & 0xDF;
        v17->widget_flags = v18;
        launch_alpha72_url(aAlpha72Url);
        g_game_base->players[0].frontend_state = 0;
        g_game_base->unknown_000521[71] = 0;
        destroy_completion_screen(exit_controller);
      }
      break;
    case 9:
      v2 = exit_controller->yes_button;
      v3 = v2->widget_flags;
      if ( (v3 & 0x20) != 0 )
      {
        LOBYTE(v3) = v3 & 0xDF;
        v2->widget_flags = v3;
        destroy_completion_screen(exit_controller);
        g_game_base->frontend_quit_requested = 3;
      }
      break;
    case 0xA:
      update_main_menu(&g_game_base->main_menu);
      v4 = exit_controller->yes_button;
      v5 = v4->widget_flags;
      if ( (v5 & 0x20) != 0 )
      {
        LOBYTE(v5) = v5 & 0xDF;
        v4->widget_flags = v5;
        destroy_completion_screen(exit_controller);
        destroy_main_menu(&g_game_base->main_menu);
        if ( !g_game_base->frontend_quit_requested )
          g_game_base->frontend_quit_requested = 1;
      }
      break;
    case 0xB:
      update_galaxy((char *)&g_game_base->subgame.galaxy);
      v6 = exit_controller->yes_button;
      v7 = v6->widget_flags;
      if ( (v7 & 0x20) != 0 )
      {
        LOBYTE(v7) = v7 & 0xDF;
        v6->widget_flags = v7;
        destroy_galaxy(&g_game_base->subgame.galaxy);
        complete_subgame(&g_game_base->subgame, 1u);
        if ( g_game_base->players[0].high_score_entry_pending == 1 )
        {
          exit_controller->previous_frontend_state = g_game_base->players[0].frontend_state;
          destroy_completion_screen(exit_controller);
          destroy_subgame(&g_game_base->subgame);
        }
        else
        {
LABEL_23:
          destroy_completion_screen(exit_controller);
LABEL_24:
          destroy_subgame(&g_game_base->subgame);
          g_game_base->players[0].frontend_state = 2;
        }
      }
      break;
    default:
      break;
  }
  no_button = exit_controller->no_button;
  v20 = no_button->widget_flags;
  if ( (v20 & 0x20) != 0 )
  {
    LOBYTE(v20) = v20 & 0xDF;
    no_button->widget_flags = v20;
    g_game_base->players[0].frontend_state = exit_controller->previous_frontend_state;
    g_game_base->unknown_000521[71] = 0;
    destroy_completion_screen(exit_controller);
  }
}
