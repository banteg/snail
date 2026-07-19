/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_row_event_display @ 0x404cf0 */
/* selector: update_row_event_display */

// Exact Windows `Completion::update_row_event_display`/`cRCompletion::AI()` state machine: stages parcel sprites, drives score and widget transitions, and hands off to the completion phase. Modeling it as the authored member makes all 213 instructions exact; Android and iOS retain the same owner.
void __thiscall update_row_event_display(Completion *completion)
{
  FrontendWidget *delivered_count_widget; // ecx
  double v3; // st7
  int32_t staged_parcel_count; // eax
  Parcel *v5; // eax
  Sprite *sprite; // ecx
  int32_t parcel_target_count; // eax
  int32_t v8; // ecx
  double v9; // st7
  int32_t bonus_enabled; // eax
  GameRoot *v11; // eax
  double v12; // st7
  FrontendWidget *bonus_widget; // ecx
  int32_t delivered_parcel_count; // ecx
  float v15; // [esp+8h] [ebp-3Ch]
  float v16; // [esp+Ch] [ebp-38h]
  float v17; // [esp+Ch] [ebp-38h]
  float v18; // [esp+10h] [ebp-34h]
  float v19; // [esp+10h] [ebp-34h]
  float v20; // [esp+18h] [ebp-2Ch]
  float v21; // [esp+1Ch] [ebp-28h]
  float v22; // [esp+24h] [ebp-20h]
  float v23; // [esp+28h] [ebp-1Ch]
  float v24; // [esp+30h] [ebp-14h]
  float v25; // [esp+34h] [ebp-10h]
  float v26; // [esp+3Ch] [ebp-8h]
  float v27; // [esp+40h] [ebp-4h]

  if ( completion->state )
  {
    delivered_count_widget = completion->delivered_count_widget;
    if ( g_game_base->subgame.subgame_pause_gate )
    {
      hide_border_init(delivered_count_widget);
      hide_border_init(completion->widget_a);
      hide_border_init(completion->widget_d);
      hide_border_init(completion->bonus_widget);
      hide_border_init(completion->continue_widget);
    }
    else
    {
      unhide_border_init(delivered_count_widget);
      unhide_border_init(completion->widget_a);
      unhide_border_init(completion->widget_d);
      unhide_border_init(completion->continue_widget);
      switch ( completion->state )
      {
        case COMPLETION_STATE_INACTIVE:
          return;
        case COMPLETION_STATE_STAGING_PARCELS:
          v3 = completion->progress_step + completion->progress;
          completion->progress = v3;
          if ( v3 > 1.0 )
          {
            staged_parcel_count = completion->staged_parcel_count;
            if ( staged_parcel_count < completion->parcel_target_count )
            {
              completion->staged_parcel_count = staged_parcel_count + 1;
              v5 = spawn_track_parcel(
                     &g_game_base->subgame,
                     &g_game_base->subgame.player.presentation.snail_hotspots_world[11],
                     (Player *)((char *)&g_player_block + (_DWORD)g_game_base));
              sprite = v5->sprite;
              v5->state = PARCEL_STATE_DELIVERY_PENDING;
              sprite->size_end = 0.0;
              v5->sprite->size_start = 0.0;
            }
            parcel_target_count = completion->parcel_target_count;
            v8 = completion->staged_parcel_count;
            completion->progress = 0.0;
            if ( v8 == parcel_target_count )
            {
              if ( parcel_target_count )
              {
                completion->state = COMPLETION_STATE_WAITING_FOR_DELIVERIES;
              }
              else
              {
                completion->state = COMPLETION_STATE_EMPTY_DELIVERY_DELAY;
                completion->progress = 0.0;
                completion->progress_step = 0.0083333338;
              }
            }
          }
          goto LABEL_27;
        case COMPLETION_STATE_SUMMARY_PENDING:
          unhide_border_init(completion->continue_widget);
          bonus_enabled = completion->bonus_enabled;
          completion->gate_18 = 0;
          completion->state = COMPLETION_STATE_SUMMARY_ACTIVE;
          if ( !bonus_enabled )
            goto LABEL_18;
          unhide_border_init(completion->bonus_widget);
          if ( completion->parcel_target_count )
            goto LABEL_18;
          v11 = g_game_base;
          if ( g_game_base->subgame.level_mode == 1 )
          {
            add_subgoldy_score((Player *)((char *)&g_player_block + (_DWORD)g_game_base), 5, completion->bonus_score);
            play_sound_effect(&g_sound_effect_manager, 49);
LABEL_18:
            v11 = g_game_base;
          }
          if ( completion->bonus_enabled )
          {
            v12 = completion->bonus_blink_step + completion->bonus_blink_progress;
            completion->bonus_blink_progress = v12;
            if ( v12 > 1.0 )
            {
              bonus_widget = completion->bonus_widget;
              completion->bonus_blink_progress = 0.0;
              if ( (bonus_widget->widget_flags & 0x1000) != 0 )
                unhide_border_init(bonus_widget);
              else
                hide_border_init(bonus_widget);
            }
            v11 = g_game_base;
          }
          if ( (v11->players[0].game_input->input.pressed_buttons & 0x4000) != 0 )
          {
            completion->state = COMPLETION_STATE_CONTINUE_ACCEPTED;
            play_sound_effect(&g_sound_effect_manager, 8);
LABEL_27:
            v11 = g_game_base;
          }
          v26 = v11->players[0].body.transform.basis_forward.y * 6.0;
          v27 = v11->players[0].body.transform.basis_forward.z * 6.0;
          v22 = v11->players[0].body.transform.basis_up.y + v11->players[0].body.transform.basis_up.y;
          v23 = v11->players[0].body.transform.basis_up.z + v11->players[0].body.transform.basis_up.z;
          v16 = v11->players[0].body.transform.basis_right.y * 7.3000002;
          v18 = v11->players[0].body.transform.basis_right.z * 7.3000002;
          v20 = v16 + v11->players[0].body.transform.position.y;
          v21 = v18 + v11->players[0].body.transform.position.z;
          v24 = v20 + v22;
          v25 = v21 + v23;
          v15 = v11->players[0].body.transform.basis_up.x
              + v11->players[0].body.transform.basis_up.x
              + v11->players[0].body.transform.basis_right.x * 7.3000002
              + v11->players[0].body.transform.position.x
              + v11->players[0].body.transform.basis_forward.x * 6.0;
          completion->widget_world.x = v15;
          v17 = v24 + v26;
          completion->widget_world.y = v17;
          v19 = v25 + v27;
          completion->widget_world.z = v19;
          delivered_parcel_count = completion->delivered_parcel_count;
          if ( delivered_parcel_count >= 10 )
            completion->delivered_count_widget->text_buffer.raw[0] = delivered_parcel_count / 10 + 48;
          else
            completion->delivered_count_widget->text_buffer.raw[0] = 32;
          completion->delivered_count_widget->text_buffer.raw[1] = completion->delivered_parcel_count % 10 + 48;
          break;
        case COMPLETION_STATE_SUMMARY_ACTIVE:
          goto LABEL_18;
        case COMPLETION_STATE_EMPTY_DELIVERY_DELAY:
          v9 = completion->progress_step + completion->progress;
          completion->progress = v9;
          if ( v9 > 1.0 )
            completion->state = COMPLETION_STATE_SUMMARY_PENDING;
          goto LABEL_27;
        default:
          goto LABEL_27;
      }
    }
  }
}
