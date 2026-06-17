/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_completion_screen @ 0x404920 */
/* selector: initialize_completion_screen */

// Builds the Delivery Complete screen, seeds its package-count and bonus summary widgets, and lays out the continue prompt. Cross-port Android and iOS symbols match this helper to `cRCompletion::Init(int, bool)`.
void __thiscall initialize_completion_screen(
        CompletionResultScreen *screen,
        int delivered_count,
        unsigned __int8 perfect_delivery)
{
  int v4; // ecx
  int v5; // ecx
  int v6; // edx
  int v7; // ecx
  int v8; // esi
  int v9; // edx
  int32_t bonus_score; // esi
  Color4f *v11; // eax
  Color4f *v12; // eax
  int v13; // eax
  Color4f *v14; // eax
  Color4f *v15; // eax
  int32_t v16; // ecx
  Color4f *v17; // [esp-Ch] [ebp-2Ch]
  Color4f *v18; // [esp-Ch] [ebp-2Ch]
  Color4f *v19; // [esp-Ch] [ebp-2Ch]
  Color4f *v20; // [esp-Ch] [ebp-2Ch]
  Color4f color; // [esp+10h] [ebp-10h] BYREF

  v4 = *((_DWORD *)MEMORY[0x4DF904] + 119190);
  if ( v4 )
  {
    if ( v4 == 1 )
    {
      if ( *((_BYTE *)MEMORY[0x4DF904] + 17198056) )
      {
        v5 = *((_DWORD *)MEMORY[0x4DF904] + 4299515);
        v6 = *(_DWORD *)(v5 + 80);
        v7 = *(_DWORD *)(v5 + 76);
        v8 = v6 / 20;
      }
      else
      {
        v7 = unk_4DF958;
        v8 = unk_4DF960 / 20;
      }
      v9 = v7 / 20;
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
        screen->bonus_score = 500000;
      else
        screen->bonus_score = dword_4A1194[v8] + dword_4A11AC[v9];
    }
  }
  else if ( perfect_delivery )
  {
    screen->bonus_score = 50000;
  }
  else
  {
    screen->bonus_score = 0;
  }
  bonus_score = screen->bonus_score;
  screen->delivered_count = delivered_count;
  screen->perfect_delivery = perfect_delivery;
  screen->total_score = bonus_score + *((_DWORD *)MEMORY[0x4DF904] + 1097752) + 100 * delivered_count;
  screen->title_widget = (FrontendWidget *)allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  v11 = set_color_rgba(&color, 1.0, 1.0, 1.0, 1.0);
  initialize_frontend_widget(screen->title_widget, 0x20400002u, aDeliveryComple, 20, 0.0, 80.0, v11, 2, 0.0);
  screen->delivered_count_widget = (FrontendWidget *)allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  if ( screen->delivered_count == 1 )
  {
    v17 = set_color_rgba(&color, 1.0, 1.0, 1.0, 1.0);
    initialize_frontend_widget(
      screen->delivered_count_widget,
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
      screen->delivered_count_widget,
      0x20400002u,
      a00PackagesDeli,
      20,
      0.0,
      160.0,
      v18,
      2,
      0.0);
  }
  screen->bonus_icon_widget = (FrontendWidget *)allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  v12 = set_color_rgba(&color, 1.0, 1.0, 1.0, 1.0);
  initialize_frontend_sprite_button((int)screen->bonus_icon_widget, 4196352, 122, 1120403456, 1125253120, v12, 0.0, 4);
  *(_DWORD *)&screen->bonus_icon_widget->_pad_80[248] = 0;
  screen->bonus_summary_widget = (FrontendWidget *)allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  v13 = *((_DWORD *)MEMORY[0x4DF904] + 119190);
  if ( v13 )
  {
    if ( v13 == 1 )
    {
      v15 = set_color_rgba(&color, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(screen->bonus_summary_widget, 0x20400002u, aLevelComplete, 20, 0.0, 302.0, v15, 2, 0.0);
      border_add_text_number(screen->bonus_summary_widget->_pad_00, screen->bonus_score);
      strcat((char *)&screen->bonus_summary_widget->text_buffer, aBonusPoints);
    }
  }
  else
  {
    v14 = set_color_rgba(&color, 1.0, 1.0, 1.0, 1.0);
    initialize_frontend_widget(screen->bonus_summary_widget, 0x20400002u, aPerfectScore50, 20, 0.0, 302.0, v14, 2, 0.0);
  }
  hide_border_init(screen->bonus_summary_widget->_pad_00);
  screen->bonus_progress = 0.0;
  screen->bonus_progress_step = 0.041666668;
  screen->continue_widget = (FrontendWidget *)allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  if ( screen->perfect_delivery )
  {
    v19 = set_color_rgba(&color, 1.0, 1.0, 1.0, 1.0);
    initialize_frontend_widget(screen->continue_widget, 0x20400002u, aClickToContinu, 20, 0.0, 400.0, v19, 2, 0.0);
  }
  else
  {
    v20 = set_color_rgba(&color, 1.0, 1.0, 1.0, 1.0);
    initialize_frontend_widget(screen->continue_widget, 0x20400002u, aClickToContinu, 20, 0.0, 320.0, v20, 2, 0.0);
  }
  hide_border_init(screen->continue_widget->_pad_00);
  v16 = screen->delivered_count;
  screen->delivered_count_progress = 0;
  screen->delivered_count_display = 0;
  screen->continue_state = 1;
  screen->delivered_count_progress_limit = 0.83333331;
  screen->continue_visible = 1;
  screen->delivered_count_progress_step = 1.0 / (3.4000001 / (double)(v16 + 1) * 60.0);
}

