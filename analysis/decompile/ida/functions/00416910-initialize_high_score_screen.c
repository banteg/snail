/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_high_score_screen @ 0x416910 */
/* selector: initialize_high_score_screen */

// Void `cRHighScore::Init(int, int)`: builds the postal or challenge high-score screen, optionally enables inline name entry, and lays out five owned ten-handle row banks. Android AI tail-branches among the void lifecycle peers; all three Windows callers discard EAX.
void __thiscall initialize_high_score_screen(HighScore *high_score, int selected_bank, int selected_rank)
{
  int landscape_script_by_name; // eax
  int32_t v5; // eax
  tColour *v6; // eax
  tColour *v7; // eax
  int v8; // ebx
  int v9; // eax
  FrontendWidget **name_row_widgets; // esi
  int v11; // edi
  int32_t v12; // eax
  tColour *v13; // eax
  tColour *v14; // eax
  tColour *v15; // eax
  uint32_t widget_flags; // ecx
  tColour *v17; // eax
  tColour *v18; // eax
  tColour *v19; // eax
  tColour *v20; // eax
  tColour *v21; // eax
  uint32_t v22; // ecx
  tColour *v23; // eax
  tColour *v24; // eax
  bool v25; // cc
  uint8_t entering_name; // al
  tColour *v27; // eax
  float v28; // esi
  tColour *v29; // eax
  tColour *v30; // eax
  float v31; // esi
  int32_t v32; // eax
  CompletionResultScreen v33; // [esp-Ch] [ebp-E4h] BYREF
  Color4f v34; // [esp+48h] [ebp-90h] BYREF
  Color4f v35; // [esp+58h] [ebp-80h] BYREF
  Color4f v36; // [esp+68h] [ebp-70h] BYREF
  Color4f v37; // [esp+78h] [ebp-60h] BYREF
  Color4f v38; // [esp+88h] [ebp-50h] BYREF
  Color4f v39; // [esp+98h] [ebp-40h] BYREF
  Color4f v40; // [esp+A8h] [ebp-30h] BYREF
  Color4f v41; // [esp+B8h] [ebp-20h] BYREF
  Color4f v42; // [esp+C8h] [ebp-10h] BYREF

  high_score->selected_bank = selected_bank;
  high_score->selected_rank = selected_rank;
  high_score->entering_name = selected_rank != -1;
  hide_star_field((StarManager *)((char *)g_game_base + 324412));
  hide_gameplay_scores((_DWORD *)g_game_base + 119174);
  v33.bonus_summary_widget = (FrontendWidget *)g_blank_text;
  v33.delivered_count_widget = nullptr;
  v33.title_widget = (FrontendWidget *)g_main_menu_music_path;
  cache_music_file(v33);
  landscape_script_by_name = load_landscape_script_by_name(
                               (char *)g_game_base + 17220120,
                               g_menu_background_script_path);
  change_backdrop((int)g_game_base + 322576, (int)g_game_base + 292 * landscape_script_by_name + 17221564, 0);
  set_border_justify_centre((_DWORD *)g_game_base + 723, 1103626240);
  capture_mouse_cursor((MouseCursorState *)((char *)g_game_base + 656));
  high_score->title_widget = (FrontendWidget *)allocate_border((_DWORD *)g_game_base + 723);
  v5 = high_score->selected_bank;
  if ( !v5 )
  {
    v7 = set_color_rgba((tColour *)v33._pad_34, 1.0, 1.0, 1.0, 1.0);
    initialize_frontend_widget(high_score->title_widget, 0, aPostalHighScor, 23, 0.0, 64.0, v7, 2, 0.0);
    *(_DWORD *)&byte_6FFAE0[(_DWORD)g_game_base] = (char *)&unk_6FFAE8 + (_DWORD)g_game_base;
    *(_DWORD *)((char *)&unk_6FFAE4 + (_DWORD)g_game_base) = 10;
    goto LABEL_8;
  }
  if ( v5 == 1 )
  {
    v6 = set_color_rgba((tColour *)&v33.bonus_progress_step, 1.0, 1.0, 1.0, 1.0);
    initialize_frontend_widget(high_score->title_widget, 0, aChallengeHighS, 23, 0.0, 64.0, v6, 2, 0.0);
    *(_DWORD *)&byte_6FFAE0[(_DWORD)g_game_base] = (char *)g_game_base + 8765736;
    *(_DWORD *)((char *)&unk_6FFAE4 + (_DWORD)g_game_base) = 10;
LABEL_8:
    v33.perfect_delivery = 1104674816;
  }
  if ( high_score->entering_name )
  {
    rstrcpy_checked_ascii((char *)&high_score->title_widget->text_buffer, aEnterYourNameH);
    layout_frontend_widget(high_score->title_widget);
  }
  v8 = 0;
  v9 = 0;
  *(_DWORD *)&v33.continue_visible = 0;
  v33.delivered_count = 0;
  name_row_widgets = high_score->name_row_widgets;
  do
  {
    name_row_widgets[20] = nullptr;
    v11 = v8 != high_score->selected_rank ? 0 : 2;
    if ( *(_DWORD *)(*(_DWORD *)&byte_6FFAE0[(_DWORD)g_game_base] + v9) != 1 )
      goto LABEL_25;
    v12 = high_score->selected_bank;
    if ( v12 )
    {
      if ( v12 != 1 )
        goto LABEL_23;
      *(float *)&v33.continue_state = (double)*(int *)&v33.continue_visible * *(float *)&v33.perfect_delivery + 111.0;
      v33.title_widget = (FrontendWidget *)-1016856576;
      *(name_row_widgets - 20) = (FrontendWidget *)allocate_border((_DWORD *)g_game_base + 723);
      v13 = set_color_rgba((tColour *)v33._pad_34, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(
        *(name_row_widgets - 20),
        v11 | 0x20000000,
        asc_4A3830,
        22,
        0.0,
        *(float *)&v33.continue_state,
        v13,
        1,
        *(float *)&v33.title_widget);
      v33.title_widget = (FrontendWidget *)-1017249792;
      *(name_row_widgets - 10) = (FrontendWidget *)allocate_border((_DWORD *)g_game_base + 723);
      v14 = set_color_rgba((tColour *)&v33.bonus_progress_step, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(
        *(name_row_widgets - 10),
        v11 | 0x20400000,
        (char *)g_blank_text,
        22,
        0.0,
        *(float *)&v33.continue_state,
        v14,
        1,
        *(float *)&v33.title_widget);
      border_add_text_number(*(name_row_widgets - 10), *(_DWORD *)&v33.continue_visible + 1);
      layout_frontend_widget(*(name_row_widgets - 10));
      v33.title_widget = (FrontendWidget *)-1020002304;
      *name_row_widgets = (FrontendWidget *)allocate_border((_DWORD *)g_game_base + 723);
      v15 = set_color_rgba((tColour *)&v40, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(
        *name_row_widgets,
        v11 | 0x20400000,
        (char *)(*(_DWORD *)&byte_6FFAE0[(_DWORD)g_game_base] + v33.delivered_count + 84),
        22,
        0.0,
        *(float *)&v33.continue_state,
        v15,
        1,
        *(float *)&v33.title_widget);
      if ( *(_DWORD *)&v33.continue_visible == high_score->selected_rank )
      {
        border_input_text_init((int)*name_row_widgets, 16, g_last_entered_player_name, 16);
        widget_flags = (*name_row_widgets)->widget_flags;
        BYTE1(widget_flags) |= 0x20u;
        (*name_row_widgets)->widget_flags = widget_flags;
      }
      layout_frontend_widget(*name_row_widgets);
      v33.title_widget = (FrontendWidget *)1123680256;
      name_row_widgets[10] = (FrontendWidget *)allocate_border((_DWORD *)g_game_base + 723);
      v17 = set_color_rgba((tColour *)&v35, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(
        name_row_widgets[10],
        v11 | 0x20400000,
        (char *)g_blank_text,
        22,
        0.0,
        *(float *)&v33.continue_state,
        v17,
        3,
        *(float *)&v33.title_widget);
      border_add_text_number(
        name_row_widgets[10],
        *(_DWORD *)(*(_DWORD *)&byte_6FFAE0[(_DWORD)g_game_base] + v33.delivered_count + 4));
      layout_frontend_widget(name_row_widgets[10]);
      v33.title_widget = (FrontendWidget *)1126825984;
      name_row_widgets[20] = (FrontendWidget *)allocate_border((_DWORD *)g_game_base + 723);
      v18 = set_color_rgba((tColour *)&v42, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(
        name_row_widgets[20],
        v11 | 0x20000014,
        aReplay,
        22,
        0.0,
        *(float *)&v33.continue_state,
        v18,
        2,
        *(float *)&v33.title_widget);
      if ( !high_score->entering_name )
        goto LABEL_23;
    }
    else
    {
      *(float *)&v33.continue_state = (double)*(int *)&v33.continue_visible * *(float *)&v33.perfect_delivery + 111.0;
      v33.title_widget = (FrontendWidget *)-1016856576;
      *(name_row_widgets - 20) = (FrontendWidget *)allocate_border((_DWORD *)g_game_base + 723);
      v19 = set_color_rgba((tColour *)&v37, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(
        *(name_row_widgets - 20),
        v11 | 0x20000000,
        asc_4A37F8,
        22,
        0.0,
        *(float *)&v33.continue_state,
        v19,
        1,
        *(float *)&v33.title_widget);
      v33.title_widget = (FrontendWidget *)-1017249792;
      *(name_row_widgets - 10) = (FrontendWidget *)allocate_border((_DWORD *)g_game_base + 723);
      v20 = set_color_rgba((tColour *)&v41, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(
        *(name_row_widgets - 10),
        v11 | 0x20400000,
        (char *)g_blank_text,
        22,
        0.0,
        *(float *)&v33.continue_state,
        v20,
        1,
        *(float *)&v33.title_widget);
      border_add_text_number(*(name_row_widgets - 10), *(_DWORD *)&v33.continue_visible + 1);
      layout_frontend_widget(*(name_row_widgets - 10));
      v33.title_widget = (FrontendWidget *)-1020002304;
      *name_row_widgets = (FrontendWidget *)allocate_border((_DWORD *)g_game_base + 723);
      v21 = set_color_rgba((tColour *)&v39, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(
        *name_row_widgets,
        v11 | 0x20400000,
        (char *)(*(_DWORD *)&byte_6FFAE0[(_DWORD)g_game_base] + v33.delivered_count + 84),
        22,
        0.0,
        *(float *)&v33.continue_state,
        v21,
        1,
        *(float *)&v33.title_widget);
      if ( *(_DWORD *)&v33.continue_visible == high_score->selected_rank )
      {
        border_input_text_init((int)*name_row_widgets, 16, g_last_entered_player_name, 16);
        v22 = (*name_row_widgets)->widget_flags;
        BYTE1(v22) |= 0x20u;
        (*name_row_widgets)->widget_flags = v22;
      }
      layout_frontend_widget(*name_row_widgets);
      v33.title_widget = (FrontendWidget *)1126170624;
      name_row_widgets[10] = (FrontendWidget *)allocate_border((_DWORD *)g_game_base + 723);
      v23 = set_color_rgba((tColour *)&v36, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(
        name_row_widgets[10],
        v11 | 0x20400000,
        (char *)g_blank_text,
        22,
        0.0,
        *(float *)&v33.continue_state,
        v23,
        3,
        *(float *)&v33.title_widget);
      border_add_text_number(
        name_row_widgets[10],
        *(_DWORD *)(*(_DWORD *)&byte_6FFAE0[(_DWORD)g_game_base] + v33.delivered_count + 4));
      layout_frontend_widget(name_row_widgets[10]);
      v33.title_widget = (FrontendWidget *)1123680256;
      name_row_widgets[20] = (FrontendWidget *)allocate_border((_DWORD *)g_game_base + 723);
      v24 = set_color_rgba((tColour *)&v38, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(
        name_row_widgets[20],
        v11 | 0x20000014,
        aReplay,
        22,
        0.0,
        *(float *)&v33.continue_state,
        v24,
        2,
        *(float *)&v33.title_widget);
    }
    hide_border_init(name_row_widgets[20]);
LABEL_23:
    v8 = *(_DWORD *)&v33.continue_visible;
    if ( (v33.continue_visible & 1) != 0 )
    {
      (*(name_row_widgets - 20))->idle_fill_color = *set_color_rgba(
                                                       (tColour *)&v34,
                                                       0.32941177,
                                                       0.18431373,
                                                       0.41960785,
                                                       0.69999999);
      name_row_widgets[20]->idle_fill_color = *set_color_rgba(
                                                 (tColour *)&v33.delivered_count_progress,
                                                 0.32941177,
                                                 0.18431373,
                                                 0.41960785,
                                                 0.69999999);
    }
LABEL_25:
    ++v8;
    v9 = v33.delivered_count + 129728;
    ++name_row_widgets;
    v25 = v33.delivered_count + 129728 < 1297280;
    *(_DWORD *)&v33.continue_visible = v8;
    v33.delivered_count += 129728;
  }
  while ( v25 );
  entering_name = high_score->entering_name;
  *(float *)&v33.continue_state = *(float *)&v33.perfect_delivery * 10.0 + 111.0;
  if ( entering_name )
  {
    v33.bonus_summary_widget = (FrontendWidget *)-1025769472;
    v33.delivered_count_widget = (FrontendWidget *)2;
    high_score->cancel_name_button = (FrontendWidget *)allocate_border((_DWORD *)g_game_base + 723);
    v27 = set_color_rgba((tColour *)&v33.delivered_count_progress, 1.0, 1.0, 1.0, 1.0);
    v28 = *(float *)&v33.continue_state;
    initialize_frontend_widget(
      high_score->cancel_name_button,
      0x20000014u,
      aCancel,
      23,
      0.0,
      *(float *)&v33.continue_state,
      v27,
      (int32_t)v33.delivered_count_widget,
      *(float *)&v33.bonus_summary_widget);
    set_frontend_widget_shortcut_key(high_score->cancel_name_button, 11);
    v33.bonus_summary_widget = (FrontendWidget *)1113325568;
    v33.delivered_count_widget = (FrontendWidget *)2;
    high_score->submit_name_button = (FrontendWidget *)allocate_border((_DWORD *)g_game_base + 723);
    v29 = set_color_rgba((tColour *)&v33.delivered_count_progress, 1.0, 1.0, 1.0, 1.0);
    initialize_frontend_widget(
      high_score->submit_name_button,
      0x20000014u,
      aSubmit,
      23,
      0.0,
      v28,
      v29,
      (int32_t)v33.delivered_count_widget,
      *(float *)&v33.bonus_summary_widget);
    set_frontend_widget_shortcut_key(high_score->submit_name_button, 5);
  }
  else
  {
    v33.bonus_summary_widget = (FrontendWidget *)-1023148032;
    v33.delivered_count_widget = (FrontendWidget *)2;
    high_score->back_button = (FrontendWidget *)allocate_border((_DWORD *)g_game_base + 723);
    v30 = set_color_rgba((tColour *)&v33.delivered_count_progress, 1.0, 1.0, 1.0, 1.0);
    v31 = *(float *)&v33.continue_state;
    initialize_frontend_widget(
      high_score->back_button,
      0x20000014u,
      g_back_text,
      23,
      0.0,
      *(float *)&v33.continue_state,
      v30,
      (int32_t)v33.delivered_count_widget,
      *(float *)&v33.bonus_summary_widget);
    high_score->bank_toggle_button = (FrontendWidget *)allocate_border((_DWORD *)g_game_base + 723);
    v32 = high_score->selected_bank;
    if ( v32 )
    {
      if ( v32 == 1 )
      {
        v33.title_widget = (FrontendWidget *)set_color_rgba(
                                               (tColour *)&v33.delivered_count_progress,
                                               1.0,
                                               1.0,
                                               1.0,
                                               1.0);
        initialize_frontend_widget(
          high_score->bank_toggle_button,
          0x20000014u,
          aPostalScores,
          23,
          0.0,
          v31,
          (tColour *)v33.title_widget,
          2,
          33.0);
      }
    }
    else
    {
      v33.title_widget = (FrontendWidget *)set_color_rgba((tColour *)&v34, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(
        high_score->bank_toggle_button,
        0x20000014u,
        aChallengeScore,
        23,
        0.0,
        v31,
        (tColour *)v33.title_widget,
        2,
        33.0);
    }
  }
}

