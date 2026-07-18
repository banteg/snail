/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_high_score_screen @ 0x416910 */
/* selector: initialize_high_score_screen */

// Void `cRHighScore::Init(int, int)`: builds the postal or challenge high-score screen, optionally enables inline name entry, and lays out five owned ten-handle row banks. Android AI tail-branches among the void lifecycle peers; all three Windows callers discard EAX.
void __thiscall initialize_high_score_screen(HighScore *high_score, int selected_bank, int selected_rank)
{
  int32_t landscape_script_by_name; // eax
  int32_t v5; // eax
  tColour *v6; // eax
  tColour *v7; // eax
  int row; // ebx
  int record_offset_bytes; // eax
  FrontendWidget **name_widget_cursor; // esi
  int v11; // edi
  int32_t v12; // eax
  tColour *v13; // eax
  tColour *v14; // eax
  tColour *v15; // eax
  FrontendWidgetFlag widget_flags; // ecx
  tColour *v17; // eax
  tColour *v18; // eax
  tColour *v19; // eax
  tColour *v20; // eax
  tColour *v21; // eax
  FrontendWidgetFlag v22; // ecx
  tColour *v23; // eax
  tColour *v24; // eax
  bool v25; // cc
  tColour *v26; // eax
  tColour *v27; // eax
  tColour *v28; // eax
  int32_t v29; // eax
  tColour *v30; // [esp-Ch] [ebp-E4h]
  tColour *v31; // [esp-Ch] [ebp-E4h]
  float y; // [esp+8h] [ebp-D0h]
  float ya; // [esp+8h] [ebp-D0h]
  float yb; // [esp+8h] [ebp-D0h]
  int saved_row; // [esp+Ch] [ebp-CCh]
  int record_index; // [esp+10h] [ebp-C8h]
  float v37; // [esp+14h] [ebp-C4h]
  Color4f v38; // [esp+18h] [ebp-C0h] BYREF
  Color4f v39; // [esp+28h] [ebp-B0h] BYREF
  Color4f color; // [esp+38h] [ebp-A0h] BYREF
  Color4f v41; // [esp+48h] [ebp-90h] BYREF
  Color4f v42; // [esp+58h] [ebp-80h] BYREF
  Color4f v43; // [esp+68h] [ebp-70h] BYREF
  Color4f v44; // [esp+78h] [ebp-60h] BYREF
  Color4f v45; // [esp+88h] [ebp-50h] BYREF
  Color4f v46; // [esp+98h] [ebp-40h] BYREF
  Color4f v47; // [esp+A8h] [ebp-30h] BYREF
  Color4f v48; // [esp+B8h] [ebp-20h] BYREF
  Color4f v49; // [esp+C8h] [ebp-10h] BYREF

  high_score->selected_bank = selected_bank;
  high_score->selected_rank = selected_rank;
  high_score->entering_name = selected_rank != -1;
  hide_star_field(&g_game_base->star_manager);
  hide_gameplay_scores((FrontendWidget **)&g_game_base->subgame);
  cache_music_file(g_main_menu_music_path, 0, (char *)g_blank_text);
  landscape_script_by_name = load_landscape_script_by_name(
                               &g_game_base->subgame.landscape_manager,
                               g_menu_background_script_path);
  change_backdrop(&g_game_base->backdrop, &g_game_base->subgame.landscape_manager.scripts[landscape_script_by_name], 0);
  set_border_justify_centre(&g_game_base->border_manager, 25.0);
  capture_mouse_cursor(&g_game_base->players[0].mouse_cursor);
  high_score->title_widget = allocate_border(&g_game_base->border_manager);
  v5 = high_score->selected_bank;
  if ( !v5 )
  {
    v7 = set_color_rgba((tColour *)&v39, 1.0, 1.0, 1.0, 1.0);
    initialize_frontend_widget(high_score->title_widget, 0, aPostalHighScor, 23, 0.0, 64.0, v7, 2, 0.0);
    g_game_base->subgame.sub_high_score.active_record_bank = g_game_base->subgame.sub_high_score.postal_records;
    g_game_base->subgame.sub_high_score.active_record_count = 10;
    goto LABEL_8;
  }
  if ( v5 == 1 )
  {
    v6 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
    initialize_frontend_widget(high_score->title_widget, 0, aChallengeHighS, 23, 0.0, 64.0, v6, 2, 0.0);
    g_game_base->subgame.sub_high_score.active_record_bank = g_game_base->subgame.sub_high_score.survival_records;
    g_game_base->subgame.sub_high_score.active_record_count = 10;
LABEL_8:
    v37 = 27.0;
  }
  if ( high_score->entering_name )
  {
    rstrcpy_checked_ascii((char *)&high_score->title_widget->text_buffer, aEnterYourNameH);
    layout_frontend_widget(high_score->title_widget);
  }
  row = 0;
  record_offset_bytes = 0;
  saved_row = 0;
  record_index = 0;
  name_widget_cursor = high_score->name_row_widgets;
  do
  {
    name_widget_cursor[20] = nullptr;
    v11 = row != high_score->selected_rank ? 0 : 2;
    if ( *(int32_t *)((char *)&g_game_base->subgame.sub_high_score.active_record_bank->active + record_offset_bytes) != 1 )
      goto LABEL_25;
    v12 = high_score->selected_bank;
    if ( v12 )
    {
      if ( v12 != 1 )
        goto LABEL_23;
      y = (double)saved_row * v37 + 111.0;
      *(name_widget_cursor - 20) = allocate_border(&g_game_base->border_manager);
      v13 = set_color_rgba((tColour *)&v39, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(*(name_widget_cursor - 20), v11 | 0x20000000, asc_4A3830, 22, 0.0, y, v13, 1, -228.0);
      *(name_widget_cursor - 10) = allocate_border(&g_game_base->border_manager);
      v14 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(
        *(name_widget_cursor - 10),
        v11 | 0x20400000,
        (char *)g_blank_text,
        22,
        0.0,
        y,
        v14,
        1,
        -222.0);
      border_add_text_number(*(name_widget_cursor - 10), saved_row + 1);
      layout_frontend_widget(*(name_widget_cursor - 10));
      *name_widget_cursor = allocate_border(&g_game_base->border_manager);
      v15 = set_color_rgba((tColour *)&v47, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(
        *name_widget_cursor,
        v11 | 0x20400000,
        g_game_base->subgame.sub_high_score.active_record_bank[record_index].player_name,
        22,
        0.0,
        y,
        v15,
        1,
        -180.0);
      if ( saved_row == high_score->selected_rank )
      {
        border_input_text_init(*name_widget_cursor, 16, g_runtime_config.last_entered_player_name, 16);
        widget_flags = (*name_widget_cursor)->widget_flags;
        BYTE1(widget_flags) |= 0x20u;
        (*name_widget_cursor)->widget_flags = widget_flags;
      }
      layout_frontend_widget(*name_widget_cursor);
      name_widget_cursor[10] = allocate_border(&g_game_base->border_manager);
      v17 = set_color_rgba((tColour *)&v42, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(
        name_widget_cursor[10],
        v11 | 0x20400000,
        (char *)g_blank_text,
        22,
        0.0,
        y,
        v17,
        3,
        125.0);
      border_add_text_number(
        name_widget_cursor[10],
        g_game_base->subgame.sub_high_score.active_record_bank[record_index].score);
      layout_frontend_widget(name_widget_cursor[10]);
      name_widget_cursor[20] = allocate_border(&g_game_base->border_manager);
      v18 = set_color_rgba((tColour *)&v49, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(name_widget_cursor[20], v11 | 0x20000014, aReplay, 22, 0.0, y, v18, 2, 170.0);
      if ( !high_score->entering_name )
        goto LABEL_23;
    }
    else
    {
      ya = (double)saved_row * v37 + 111.0;
      *(name_widget_cursor - 20) = allocate_border(&g_game_base->border_manager);
      v19 = set_color_rgba((tColour *)&v44, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(*(name_widget_cursor - 20), v11 | 0x20000000, asc_4A37F8, 22, 0.0, ya, v19, 1, -228.0);
      *(name_widget_cursor - 10) = allocate_border(&g_game_base->border_manager);
      v20 = set_color_rgba((tColour *)&v48, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(
        *(name_widget_cursor - 10),
        v11 | 0x20400000,
        (char *)g_blank_text,
        22,
        0.0,
        ya,
        v20,
        1,
        -222.0);
      border_add_text_number(*(name_widget_cursor - 10), saved_row + 1);
      layout_frontend_widget(*(name_widget_cursor - 10));
      *name_widget_cursor = allocate_border(&g_game_base->border_manager);
      v21 = set_color_rgba((tColour *)&v46, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(
        *name_widget_cursor,
        v11 | 0x20400000,
        g_game_base->subgame.sub_high_score.active_record_bank[record_index].player_name,
        22,
        0.0,
        ya,
        v21,
        1,
        -180.0);
      if ( saved_row == high_score->selected_rank )
      {
        border_input_text_init(*name_widget_cursor, 16, g_runtime_config.last_entered_player_name, 16);
        v22 = (*name_widget_cursor)->widget_flags;
        BYTE1(v22) |= 0x20u;
        (*name_widget_cursor)->widget_flags = v22;
      }
      layout_frontend_widget(*name_widget_cursor);
      name_widget_cursor[10] = allocate_border(&g_game_base->border_manager);
      v23 = set_color_rgba((tColour *)&v43, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(
        name_widget_cursor[10],
        v11 | 0x20400000,
        (char *)g_blank_text,
        22,
        0.0,
        ya,
        v23,
        3,
        160.0);
      border_add_text_number(
        name_widget_cursor[10],
        g_game_base->subgame.sub_high_score.active_record_bank[record_index].score);
      layout_frontend_widget(name_widget_cursor[10]);
      name_widget_cursor[20] = allocate_border(&g_game_base->border_manager);
      v24 = set_color_rgba((tColour *)&v45, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(name_widget_cursor[20], v11 | 0x20000014, aReplay, 22, 0.0, ya, v24, 2, 125.0);
    }
    hide_border_init(name_widget_cursor[20]);
LABEL_23:
    row = saved_row;
    if ( (saved_row & 1) != 0 )
    {
      (*(name_widget_cursor - 20))->idle_fill_color = *set_color_rgba(
                                                         (tColour *)&v41,
                                                         0.32941177,
                                                         0.18431373,
                                                         0.41960785,
                                                         0.69999999);
      name_widget_cursor[20]->idle_fill_color = *set_color_rgba(
                                                   (tColour *)&v38,
                                                   0.32941177,
                                                   0.18431373,
                                                   0.41960785,
                                                   0.69999999);
    }
LABEL_25:
    ++row;
    record_offset_bytes = record_index * 129728 + 129728;
    ++name_widget_cursor;
    v25 = record_index * 129728 + 129728 < 1297280;
    saved_row = row;
    ++record_index;
  }
  while ( v25 );
  yb = v37 * 10.0 + 111.0;
  if ( high_score->entering_name )
  {
    high_score->cancel_name_button = allocate_border(&g_game_base->border_manager);
    v26 = set_color_rgba((tColour *)&v38, 1.0, 1.0, 1.0, 1.0);
    initialize_frontend_widget(high_score->cancel_name_button, 0x20000014u, aCancel, 23, 0.0, yb, v26, 2, -110.0);
    set_frontend_widget_shortcut_key(high_score->cancel_name_button, 11);
    high_score->submit_name_button = allocate_border(&g_game_base->border_manager);
    v27 = set_color_rgba((tColour *)&v38, 1.0, 1.0, 1.0, 1.0);
    initialize_frontend_widget(high_score->submit_name_button, 0x20000014u, aSubmit, 23, 0.0, yb, v27, 2, 55.0);
    set_frontend_widget_shortcut_key(high_score->submit_name_button, 5);
  }
  else
  {
    high_score->back_button = allocate_border(&g_game_base->border_manager);
    v28 = set_color_rgba((tColour *)&v38, 1.0, 1.0, 1.0, 1.0);
    initialize_frontend_widget(high_score->back_button, 0x20000014u, g_back_text, 23, 0.0, yb, v28, 2, -132.0);
    high_score->bank_toggle_button = allocate_border(&g_game_base->border_manager);
    v29 = high_score->selected_bank;
    if ( v29 )
    {
      if ( v29 == 1 )
      {
        v30 = set_color_rgba((tColour *)&v38, 1.0, 1.0, 1.0, 1.0);
        initialize_frontend_widget(
          high_score->bank_toggle_button,
          0x20000014u,
          aPostalScores,
          23,
          0.0,
          yb,
          v30,
          2,
          33.0);
      }
    }
    else
    {
      v31 = set_color_rgba((tColour *)&v41, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(
        high_score->bank_toggle_button,
        0x20000014u,
        aChallengeScore,
        23,
        0.0,
        yb,
        v31,
        2,
        33.0);
    }
  }
}
