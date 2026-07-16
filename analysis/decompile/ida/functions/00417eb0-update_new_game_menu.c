/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_new_game_menu @ 0x417eb0 */
/* selector: update_new_game_menu */

// Exact Windows `cRIntro::AI()`: dispatches Tutorial, Postal Mode, Time Trial, Challenge Mode, Help, and Back through the shared front-end state machine, then drives the Intro-owned replay-attract lane. It rotates cursor `0..4`, probes replay banks `0/1/3`, gives up after 1000 attempts, and seeds the replay-launch handoff with return state `2`.
void __thiscall update_new_game_menu(Intro *intro)
{
  uint8_t hide_for_replay_latch; // al
  FrontendWidget *postal_button; // ecx
  FrontendWidgetFlag widget_flags; // eax
  FrontendWidget *time_trial_button; // ecx
  FrontendWidgetFlag v6; // eax
  FrontendWidget *tutorial_button; // ecx
  FrontendWidgetFlag v8; // eax
  FrontendWidget *challenge_button; // ecx
  FrontendWidgetFlag v10; // eax
  FrontendWidget *back_button; // ecx
  FrontendWidgetFlag v12; // eax
  FrontendWidget *help_button; // ecx
  FrontendWidgetFlag v14; // eax
  double v15; // st7
  int v16; // edi
  SubSolution *v17; // eax
  SubSolution *v18; // eax
  SubSolution *v19; // eax
  int32_t v20; // eax

  if ( read_pressed_text_input_key_code() || (g_game_base->players[0].game_input->input.pressed_buttons & 0x4000) != 0 )
  {
    hide_for_replay_latch = intro->hide_for_replay_latch;
    intro->replay_probe_progress = 0.0;
    if ( hide_for_replay_latch == 1 )
    {
      unhide_border_init(intro->postal_button);
      unhide_border_init(intro->tutorial_button);
      unhide_border_init(intro->time_trial_button);
      unhide_border_init(intro->challenge_button);
      unhide_border_init(intro->help_button);
      unhide_border_init(intro->back_button);
      capture_mouse_cursor(&g_game_base->players[0].mouse_cursor);
      intro->hide_for_replay_latch = 0;
    }
  }
  postal_button = intro->postal_button;
  widget_flags = postal_button->widget_flags;
  if ( (widget_flags & 0x20) != 0 )
  {
    LOBYTE(widget_flags) = widget_flags & 0xDF;
    postal_button->widget_flags = widget_flags;
    destroy_main_menu((MainMenu *)intro);
    g_game_base->players[0].frontend_state = 10;
    g_game_base->players[0].redispatch_requested = 1;
    g_game_base->subgame.level_mode = 0;
    g_game_base->subgame.subgame_rebuild_selector = 2;
  }
  else
  {
    time_trial_button = intro->time_trial_button;
    v6 = time_trial_button->widget_flags;
    if ( (v6 & 0x20) != 0 )
    {
      LOBYTE(v6) = v6 & 0xDF;
      time_trial_button->widget_flags = v6;
      destroy_main_menu((MainMenu *)intro);
      g_game_base->players[0].frontend_state = 10;
      g_game_base->players[0].redispatch_requested = 1;
      g_game_base->subgame.level_mode = 4;
    }
    else
    {
      tutorial_button = intro->tutorial_button;
      v8 = tutorial_button->widget_flags;
      if ( (v8 & 0x20) != 0 )
      {
        LOBYTE(v8) = v8 & 0xDF;
        tutorial_button->widget_flags = v8;
        destroy_main_menu((MainMenu *)intro);
        g_game_base->players[0].frontend_state = 10;
        g_game_base->players[0].redispatch_requested = 1;
        g_game_base->subgame.level_mode = 7;
        initialize_tutorial(&g_game_base->subgame.tutorial);
        g_runtime_config.new_game_tutorial_started = 1;
      }
      else
      {
        challenge_button = intro->challenge_button;
        v10 = challenge_button->widget_flags;
        if ( (v10 & 0x20) != 0 )
        {
          LOBYTE(v10) = v10 & 0xDF;
          challenge_button->widget_flags = v10;
          destroy_main_menu((MainMenu *)intro);
          g_game_base->players[0].frontend_state = 10;
          g_game_base->players[0].redispatch_requested = 1;
          g_game_base->subgame.level_mode = 1;
        }
        else
        {
          back_button = intro->back_button;
          v12 = back_button->widget_flags;
          if ( (v12 & 0x20) != 0 )
          {
            LOBYTE(v12) = v12 & 0xDF;
            back_button->widget_flags = v12;
            destroy_main_menu((MainMenu *)intro);
            g_game_base->players[0].frontend_state = 4;
            g_game_base->players[0].redispatch_requested = 1;
          }
          else
          {
            help_button = intro->help_button;
            v14 = help_button->widget_flags;
            if ( (v14 & 0x20) != 0 )
            {
              LOBYTE(v14) = v14 & 0xDF;
              help_button->widget_flags = v14;
              destroy_main_menu((MainMenu *)intro);
              g_game_base->players[0].frontend_state = 31;
              g_game_base->players[0].redispatch_requested = 1;
            }
          }
          v15 = intro->replay_probe_step + intro->replay_probe_progress;
          intro->replay_probe_progress = v15;
          if ( v15 > 1.0 )
          {
            intro->replay_probe_progress = 0.0;
            v16 = 0;
            g_game_base->subgame.selected_level_record = nullptr;
            while ( 1 )
            {
              ++v16;
              if ( intro->replay_attract_bank_cursor )
              {
                if ( intro->replay_attract_bank_cursor == 1 )
                {
                  v18 = &g_game_base->subgame.sub_high_score.survival_records[(__int64)((double)next_math_random_value()
                                                                                      * 0.00012207031)];
                  if ( v18->active == 1 )
                  {
                    g_game_base->subgame.selected_level_record = v18;
                    g_game_base->subgame.level_mode = 1;
                  }
                }
                else if ( intro->replay_attract_bank_cursor == 3 )
                {
                  v17 = &g_game_base->subgame.sub_high_score.time_trial_route_records[(__int64)((double)next_math_random_value()
                                                                                              * 0.0015563965)];
                  if ( v17->active == 1 )
                  {
                    g_game_base->subgame.selected_level_record = v17;
                    g_game_base->subgame.level_mode = 4;
                  }
                }
              }
              else
              {
                v19 = (SubSolution *)((int)&g_parcel_set_buckets[1431].candidates[30].position.z
                                    + (_DWORD)g_game_base
                                    + 129728 * (__int64)((double)next_math_random_value() * 0.00012207031));
                if ( v19->active == 1 )
                {
                  g_game_base->subgame.selected_level_record = v19;
                  g_game_base->subgame.level_mode = 0;
                }
              }
              v20 = intro->replay_attract_bank_cursor + 1;
              intro->replay_attract_bank_cursor = v20;
              if ( v20 == 5 )
                intro->replay_attract_bank_cursor = 0;
              if ( g_game_base->subgame.selected_level_record )
                break;
              if ( v16 >= 1000 )
                goto LABEL_32;
            }
            if ( v16 >= 1000 )
            {
LABEL_32:
              intro->attract_reset_progress = 0.0;
              intro->attract_reset_step = 0.00027777778;
              return;
            }
            intro->hide_for_replay_latch = 1;
            g_game_base->players[0].frontend_state = 10;
            g_game_base->players[0].redispatch_requested = 1;
            g_game_base->subgame.selected_level_record_active = 1;
            g_game_base->subgame.selected_level_record_cursor = 2;
            g_game_base->subgame.selected_level_record_persistent = 1;
            intro->attract_reset_progress = 0.0;
            intro->attract_reset_step = 0.00027777778;
            destroy_main_menu((MainMenu *)intro);
          }
        }
      }
    }
  }
}
