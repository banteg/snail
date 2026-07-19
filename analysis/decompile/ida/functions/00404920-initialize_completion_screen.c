/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_completion_screen @ 0x404920 */
/* selector: initialize_completion_screen */

// Builds the Delivery Complete phase of the embedded 0x50-byte `Completion`, reusing the same storage that drives the parcel display. It seeds package-count and bonus widgets and lays out the continue prompt. Android and iOS retain `cRCompletion::Init(int, bool)`.
void __thiscall initialize_completion_screen(Completion *completion, int32_t delivered_count, uint8_t perfect_delivery)
{
  int32_t level_mode; // ecx
  SubSolution *selected_level_record; // ecx
  int32_t challenge_difficulty_value; // edx
  int32_t challenge_speed_value; // ecx
  int v8; // esi
  int v9; // edx
  int32_t bonus_score; // esi
  tColour *v11; // eax
  tColour *v12; // eax
  int32_t v13; // eax
  tColour *v14; // eax
  tColour *v15; // eax
  int32_t parcel_target_count; // ecx
  tColour *v17; // [esp-Ch] [ebp-2Ch]
  tColour *v18; // [esp-Ch] [ebp-2Ch]
  tColour *v19; // [esp-Ch] [ebp-2Ch]
  tColour *v20; // [esp-Ch] [ebp-2Ch]
  struct tColour color; // [esp+10h] [ebp-10h] BYREF

  level_mode = g_game_base->subgame.level_mode;
  if ( level_mode )
  {
    if ( level_mode == 1 )
    {
      if ( g_game_base->subgame.selected_level_record_active )
      {
        selected_level_record = g_game_base->subgame.selected_level_record;
        challenge_difficulty_value = selected_level_record->challenge_difficulty_value;
        challenge_speed_value = selected_level_record->challenge_speed_value;
        v8 = challenge_difficulty_value / 20;
      }
      else
      {
        challenge_speed_value = g_runtime_config.completion_bonus_x_source;
        v8 = g_runtime_config.completion_bonus_y_source / 20;
      }
      v9 = challenge_speed_value / 20;
      if ( v8 >= 0 )
      {
        if ( v8 > 5 )
          v8 = 5;
      }
      else
      {
        v8 = 0;
      }
      if ( v9 >= 0 )
      {
        if ( v9 > 5 )
          v9 = 5;
      }
      else
      {
        v9 = 0;
      }
      if ( v8 == 5 && v9 == 5 )
        completion->bonus_score = 500000;
      else
        completion->bonus_score = g_completion_bonus_y_table[v8] + g_completion_bonus_x_table[v9];
    }
  }
  else if ( perfect_delivery )
  {
    completion->bonus_score = 50000;
  }
  else
  {
    completion->bonus_score = 0;
  }
  bonus_score = completion->bonus_score;
  completion->parcel_target_count = delivered_count;
  completion->bonus_enabled = perfect_delivery;
  completion->display_token = bonus_score + g_game_base->subgame.player.total_score + 100 * delivered_count;
  completion->widget_a = allocate_border(&g_game_base->border_manager);
  v11 = set_color_rgba(&color, 1.0, 1.0, 1.0, 1.0);
  initialize_frontend_widget(completion->widget_a, 0x20400002u, aDeliveryComple, 20, 0.0, 80.0, v11, 2, 0.0);
  completion->delivered_count_widget = allocate_border(&g_game_base->border_manager);
  if ( completion->parcel_target_count == 1 )
  {
    v17 = set_color_rgba(&color, 1.0, 1.0, 1.0, 1.0);
    initialize_frontend_widget(
      completion->delivered_count_widget,
      0x20400002u,
      a0PackageDelive,
      20,
      0.0,
      160.0,
      v17,
      2,
      0.0);
  }
  else
  {
    v18 = set_color_rgba(&color, 1.0, 1.0, 1.0, 1.0);
    initialize_frontend_widget(
      completion->delivered_count_widget,
      0x20400002u,
      a00PackagesDeli,
      20,
      0.0,
      160.0,
      v18,
      2,
      0.0);
  }
  completion->widget_d = allocate_border(&g_game_base->border_manager);
  v12 = set_color_rgba(&color, 1.0, 1.0, 1.0, 1.0);
  initialize_frontend_sprite_button(completion->widget_d, 0x400800u, 122, 100.0, 146.0, v12, 0.0, 4);
  completion->widget_d->sprite_shadow_offset = 0.0;
  completion->bonus_widget = allocate_border(&g_game_base->border_manager);
  v13 = g_game_base->subgame.level_mode;
  if ( v13 )
  {
    if ( v13 == 1 )
    {
      v15 = set_color_rgba(&color, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(completion->bonus_widget, 0x20400002u, aLevelComplete, 20, 0.0, 302.0, v15, 2, 0.0);
      border_add_text_number(completion->bonus_widget, completion->bonus_score);
      strcat((char *)&completion->bonus_widget->text_buffer, aBonusPoints);
    }
  }
  else
  {
    v14 = set_color_rgba(&color, 1.0, 1.0, 1.0, 1.0);
    initialize_frontend_widget(completion->bonus_widget, 0x20400002u, aPerfectScore50, 20, 0.0, 302.0, v14, 2, 0.0);
  }
  hide_border_init(completion->bonus_widget);
  completion->bonus_blink_progress = 0.0;
  completion->bonus_blink_step = 0.041666668;
  completion->continue_widget = allocate_border(&g_game_base->border_manager);
  if ( completion->bonus_enabled )
  {
    v19 = set_color_rgba(&color, 1.0, 1.0, 1.0, 1.0);
    initialize_frontend_widget(
      completion->continue_widget,
      0x20400002u,
      g_click_to_continue_text,
      20,
      0.0,
      400.0,
      v19,
      2,
      0.0);
  }
  else
  {
    v20 = set_color_rgba(&color, 1.0, 1.0, 1.0, 1.0);
    initialize_frontend_widget(
      completion->continue_widget,
      0x20400002u,
      g_click_to_continue_text,
      20,
      0.0,
      320.0,
      v20,
      2,
      0.0);
  }
  hide_border_init(completion->continue_widget);
  parcel_target_count = completion->parcel_target_count;
  completion->staged_parcel_count = 0;
  completion->delivered_parcel_count = 0;
  completion->state = COMPLETION_STATE_STAGING_PARCELS;
  completion->progress = 0.83333331;
  completion->gate_18 = 1;
  completion->progress_step = 1.0 / (3.4000001 / (double)(parcel_target_count + 1) * 60.0);
}
