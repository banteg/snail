/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_frontend_widget_interaction @ 0x402820 */
/* selector: update_frontend_widget_interaction */

// Authored void `cRBorder::AI()`: slot-zero per-frame callback for one complete front-end border/widget owner. The Android and iOS bodies preserve the Windows flag snapshot, active-list removal, mouse/shortcut dispatch, tooltip and twinkle updates, RePosition/Draw calls, sound IDs 8/9, text input, and slider-child propagation. The Windows active-BOD dispatcher ignores callback results; the honest scratch remains 68.32% with all 93 audited operands clean.
void __thiscall update_frontend_widget_interaction(FrontendWidget *widget)
{
  FrontendWidgetFlag v2; // edx
  FrontendWidgetFlag widget_flags; // eax
  uint32_t list_flags; // eax
  FrameBodList *p_active_bod_list; // ecx
  FrontendWidget *list_next; // eax
  FrontendWidget *list_prev; // eax
  uint32_t v8; // eax
  FrameBodList *v9; // ecx
  uint32_t v10; // eax
  FrontendWidget *v11; // eax
  FrontendWidget *v12; // eax
  double v13; // st7
  uint32_t v14; // eax
  FrontendWidget *v15; // eax
  FrontendWidget *v16; // eax
  uint32_t v17; // eax
  FrontendWidgetFlag v18; // eax
  FrontendWidgetFlag v19; // ecx
  FrontendWidgetFlag v20; // eax
  FrontendWidgetFlag v21; // eax
  FrontendWidgetFlag v22; // eax
  FrontendWidgetFlag v23; // eax
  FrontendWidgetFlag v24; // eax
  GameRoot *v25; // ecx
  FrontendWidgetFlag v26; // eax
  FrontendWidgetFlag v27; // edx
  FrontendWidgetFlag v28; // eax
  FrontendWidgetFlag v29; // eax
  double v30; // st7
  double v31; // st7
  double v32; // st7
  double v33; // st7
  FrontendWidgetFlag v34; // eax
  float authored_top; // eax
  float authored_width; // ecx
  float authored_height; // edx
  int32_t mouse_history_warmup_frames; // eax
  FrontendWidget *slider_more_widget; // ecx
  FrontendWidgetFlag v40; // eax
  double v41; // st7
  FrontendWidget *slider_less_widget; // ecx
  FrontendWidgetFlag v43; // eax
  double v44; // st7
  FrontendWidget *v45; // eax
  FrontendWidgetFlag v46; // edx
  FrontendWidget *v47; // eax
  FrontendWidgetFlag v48; // ecx
  tColour *p_current_text_color; // ecx
  float r; // [esp+0h] [ebp-24h]
  float ra; // [esp+0h] [ebp-24h]
  float g; // [esp+4h] [ebp-20h]
  float ga; // [esp+4h] [ebp-20h]
  float b; // [esp+8h] [ebp-1Ch]
  float ba; // [esp+8h] [ebp-1Ch]
  float a; // [esp+Ch] [ebp-18h]
  float aa; // [esp+Ch] [ebp-18h]
  uint8_t v58; // [esp+1Ch] [ebp-8h]

  widget->previous_widget_flags = widget->widget_flags;
  v2 = widget->widget_flags & 0xFFFDFFFF;
  widget->widget_flags = v2;
  if ( (v2 & 0x100000) != 0 )
  {
    widget->slider_hit_left = widget->layout_width * 0.1 + widget->layout_left + 4.0 - 12.0;
    widget->slider_hit_right = widget->layout_width * 0.80000001 + widget->layout_left - 4.0;
    widget->slider_hit_top = widget->layout_height * 0.5 + widget->layout_top - 6.0;
    widget->slider_hit_bottom = widget->layout_height * 0.5 + widget->layout_top + 32.0 - 6.0;
  }
  widget->slider_position_current = (widget->slider_position_target - widget->slider_position_current) * 0.80000001
                                  + widget->slider_position_current;
  widget_flags = widget->widget_flags;
  if ( !widget_flags )
  {
    list_flags = widget->list_flags;
    p_active_bod_list = &g_game_base->active_bod_list;
    if ( (list_flags & 0x200) != 0 )
    {
      if ( (list_flags & 0x40) != 0 )
      {
        report_errorf(aListRemoveNext);
        reset_tooltip(&widget->tooltip);
      }
      else
      {
        list_next = widget->list_next;
        if ( list_next )
          list_next->list_prev = widget->list_prev;
        list_prev = widget->list_prev;
        if ( list_prev )
          list_prev->list_next = widget->list_next;
        else
          p_active_bod_list->first = (FrameBodBase *)widget->list_next;
        widget->list_next = (FrontendWidget *)p_active_bod_list->free_top;
        p_active_bod_list->free_top = (FrameBodBase *)widget;
        v8 = widget->list_flags;
        BYTE1(v8) &= ~2u;
        widget->list_flags = v8;
        reset_tooltip(&widget->tooltip);
      }
    }
    else
    {
      report_errorf(aListRemove);
      reset_tooltip(&widget->tooltip);
    }
    return;
  }
  if ( (BYTE1(widget_flags) & 2) != 0 )
  {
    BYTE1(widget_flags) &= ~2u;
    widget->widget_flags = widget_flags;
    v9 = &g_game_base->active_bod_list;
    v10 = widget->list_flags;
    if ( (v10 & 0x200) == 0 )
    {
LABEL_16:
      report_errorf(aListRemove);
LABEL_33:
      reset_tooltip(&widget->tooltip);
      widget->widget_flags = 0;
      return;
    }
    if ( (v10 & 0x40) != 0 )
    {
LABEL_18:
      report_errorf(aListRemoveNext);
      goto LABEL_33;
    }
    v11 = widget->list_next;
    if ( v11 )
      v11->list_prev = widget->list_prev;
    v12 = widget->list_prev;
    if ( v12 )
    {
      v12->list_next = widget->list_next;
LABEL_32:
      widget->list_next = (FrontendWidget *)v9->free_top;
      v9->free_top = (FrameBodBase *)widget;
      v17 = widget->list_flags;
      BYTE1(v17) &= ~2u;
      widget->list_flags = v17;
      goto LABEL_33;
    }
    goto LABEL_31;
  }
  if ( (BYTE1(widget_flags) & 4) == 0 )
  {
    if ( (BYTE1(widget_flags) & 0x10) != 0 )
      return;
    if ( SBYTE1(widget_flags) < 0 )
    {
      widget->text_effect_target = 0.0;
      v18 = widget->widget_flags;
LABEL_82:
      LOBYTE(v18) = v18 & 0xFD;
      widget->widget_flags = v18;
      goto LABEL_83;
    }
    if ( (widget_flags & 2) != 0 )
      widget->hover_blend_target = 1.0;
    v19 = widget->widget_flags;
    if ( (v19 & 0x2000000) != 0
      && !widget->mouse_history_warmup_frames
      && (g_game_base->players[0].mouse_cursor.saved_x != widget->previous_mouse_x
       || g_game_base->players[0].mouse_cursor.saved_y != widget->previous_mouse_y) )
    {
      widget->widget_flags = v19 | 0x4000000;
    }
    if ( (widget->widget_flags & 0x80000) != 0
      && is_mouse_captured(&g_game_base->players[0].mouse_cursor)
      && read_pressed_text_input_key_code() == widget->shortcut_key_code )
    {
      reset_tooltip(&widget->tooltip);
      v20 = widget->widget_flags;
      if ( (v20 & 0x1000000) != 0 )
      {
        LOBYTE(v20) = v20 | 0x20;
        widget->widget_flags = v20;
      }
      else
      {
        queue_frontend_widget_flag_after_delay(&g_game_base->border_manager, widget, 32);
      }
    }
    if ( !is_mouse_captured(&g_game_base->players[0].mouse_cursor) || !border_mouse_test(widget) )
    {
      v27 = widget->widget_flags & 0xFFDFFFFF;
      widget->widget_flags = v27;
      if ( (v27 & 0x2000) == 0 && (v27 & 4) != 0 )
        unhighlight_border(widget);
      widget->text_effect_target = 0.0;
      v18 = widget->widget_flags;
      if ( (v18 & 4) == 0 )
        goto LABEL_83;
      goto LABEL_82;
    }
    v21 = widget->widget_flags | 0x20000;
    widget->widget_flags = v21;
    if ( (v21 & 4) != 0 )
    {
      widget->hover_blend_target = 1.0;
      widget->target_padding = widget->hot_padding;
    }
    if ( (widget->widget_flags & 8) != 0 )
      widget->text_effect_target = 1.0;
    v22 = widget->widget_flags;
    if ( (v22 & 2) == 0 && (v22 & 4) != 0 )
    {
      if ( (v22 & 0x40000) == 0 )
        play_sound_effect(9);
      v23 = widget->widget_flags;
      LOBYTE(v23) = v23 | 2;
      widget->widget_flags = v23;
    }
    v24 = widget->widget_flags;
    if ( (v24 & 0x10) != 0 )
    {
      v25 = g_game_base;
      if ( g_game_base->border_manager.delayed_widget_active
        || (g_game_base->players[0].game_input->input.pressed_buttons & 0x4000) == 0 )
      {
LABEL_72:
        v26 = widget->widget_flags;
        if ( (v26 & 0x40) != 0 && (v25->players[0].game_input->input.pressed_buttons & 0x8000) != 0 )
        {
          if ( (v26 & 0x1000000) != 0 )
          {
            LOBYTE(v26) = v26 | 0x80;
            widget->widget_flags = v26;
          }
          else
          {
            queue_frontend_widget_flag_after_delay(&v25->border_manager, widget, 128);
          }
          play_sound_effect(8);
          reset_tooltip(&widget->tooltip);
        }
        goto LABEL_83;
      }
      if ( (v24 & 0x1000000) != 0 )
      {
        LOBYTE(v24) = v24 | 0x20;
        widget->widget_flags = v24;
      }
      else
      {
        queue_frontend_widget_flag_after_delay(&g_game_base->border_manager, widget, 32);
      }
      if ( ((unsigned int)&unk_800000 & widget->widget_flags) == 0 )
        play_sound_effect(8);
      if ( (widget->tooltip.mode_flags & 0x20) == 0 )
        reset_tooltip(&widget->tooltip);
    }
    v25 = g_game_base;
    goto LABEL_72;
  }
  v13 = widget->teardown_progress_step + widget->teardown_progress;
  widget->teardown_progress = v13;
  if ( v13 > 1.0 )
  {
    v9 = &g_game_base->active_bod_list;
    v14 = widget->list_flags;
    if ( (v14 & 0x200) == 0 )
      goto LABEL_16;
    if ( (v14 & 0x40) != 0 )
      goto LABEL_18;
    v15 = widget->list_next;
    if ( v15 )
      v15->list_prev = widget->list_prev;
    v16 = widget->list_prev;
    if ( v16 )
    {
      v16->list_next = widget->list_next;
      goto LABEL_32;
    }
LABEL_31:
    v9->first = (FrameBodBase *)widget->list_next;
    goto LABEL_32;
  }
LABEL_83:
  v28 = widget->widget_flags;
  if ( SBYTE1(v28) < 0 )
  {
    widget->widget_flags = v28 & 0xFFDFFFFF;
    unhighlight_border(widget);
  }
  v29 = widget->widget_flags;
  if ( (v29 & 0x40000) != 0 )
  {
    widget->widget_flags = v29 & 0xFFFBFFFF;
    widget->hover_blend_current = widget->hover_blend_target;
    widget->current_padding = widget->target_padding;
    widget->text_effect_current = widget->text_effect_target;
  }
  else
  {
    widget->hover_blend_current = (widget->hover_blend_target - widget->hover_blend_current) * 0.1
                                + widget->hover_blend_current;
    widget->current_padding = (widget->target_padding - widget->current_padding) * 0.1 + widget->current_padding;
    v30 = (widget->text_effect_target - widget->text_effect_current) * 0.1 + widget->text_effect_current;
    widget->text_effect_current = v30;
    v31 = widget->text_effect_target - v30;
    if ( v31 < 0.0 )
      v31 = -v31;
    if ( v31 < 0.1 )
      widget->text_effect_current = widget->text_effect_target;
  }
  if ( (widget->widget_flags & 0x2000) != 0 )
  {
    if ( is_mouse_captured(&g_game_base->players[0].mouse_cursor) )
    {
      border_input_text(widget);
      if ( (widget->widget_flags & 0x2000) == 0 )
        activate_all_borders(&g_game_base->border_manager);
    }
  }
  update_twinkle_manager(&widget->twinkle_manager);
  update_tooltip(&widget->tooltip);
  v58 = ((unsigned __int16)widget->widget_flags >> 8) & 1;
  layout_frontend_widget(widget);
  if ( (widget->widget_flags & 0x1000) == 0 )
  {
    v32 = 1.0 - widget->hover_blend_current;
    a = widget->hover_blend_current * widget->hot_fill_color.a + v32 * widget->idle_fill_color.a;
    b = widget->hover_blend_current * widget->hot_fill_color.b + v32 * widget->idle_fill_color.b;
    g = widget->hover_blend_current * widget->hot_fill_color.g + v32 * widget->idle_fill_color.g;
    r = widget->hover_blend_current * widget->hot_fill_color.r + v32 * widget->idle_fill_color.r;
    store_color4f(&widget->current_fill_color, r, g, b, a);
    v33 = 1.0 - widget->hover_blend_current;
    aa = widget->hover_blend_current * widget->hot_text_color.a + v33 * widget->idle_text_color.a;
    ba = widget->hover_blend_current * widget->hot_text_color.b + v33 * widget->idle_text_color.b;
    ga = widget->hover_blend_current * widget->hot_text_color.g + v33 * widget->idle_text_color.g;
    ra = widget->hover_blend_current * widget->hot_text_color.r + v33 * widget->idle_text_color.r;
    store_color4f(&widget->current_text_color, ra, ga, ba, aa);
    v34 = widget->widget_flags;
    if ( SBYTE1(v34) < 0 )
    {
      widget->current_text_color.r = widget->current_text_color.r * 0.5;
      widget->current_text_color.g = widget->current_text_color.g * 0.5;
      widget->current_text_color.b = widget->current_text_color.b * 0.5;
      widget->current_text_color.a = widget->current_text_color.a * 0.5;
      widget->current_fill_color.r = widget->current_fill_color.r * 0.5;
      widget->current_fill_color.g = widget->current_fill_color.g * 0.5;
      widget->current_fill_color.b = widget->current_fill_color.b * 0.5;
      widget->current_fill_color.a = widget->current_fill_color.a * 0.5;
    }
    if ( (BYTE1(v34) & 8) == 0 )
    {
      if ( (v34 & 0x10000) != 0 )
      {
        authored_top = widget->authored_top;
        authored_width = widget->authored_width;
        widget->layout_left = widget->authored_left;
        authored_height = widget->authored_height;
        widget->layout_top = authored_top;
        widget->layout_width = authored_width;
        widget->layout_height = authored_height;
      }
      else
      {
        layout_and_queue_wrapped_font_text(
          (char *)&widget->text_buffer,
          widget->font_id,
          widget->font_scale,
          widget->layout_anchor_x,
          widget->layout_anchor_y,
          &widget->layout_left,
          &widget->layout_top,
          &widget->layout_width,
          &widget->layout_height,
          widget->text_effect_current,
          BYTE1(g_runtime_config.render_flags) & 1,
          widget->text_alignment,
          widget->anchor_x,
          0x1000000u,
          &widget->current_text_color,
          0,
          v58);
      }
    }
    draw_frontend_widget(widget);
  }
  mouse_history_warmup_frames = widget->mouse_history_warmup_frames;
  if ( mouse_history_warmup_frames )
    widget->mouse_history_warmup_frames = mouse_history_warmup_frames - 1;
  widget->previous_mouse_x = g_game_base->players[0].mouse_cursor.saved_x;
  widget->previous_mouse_y = g_game_base->players[0].mouse_cursor.saved_y;
  if ( (widget->widget_flags & 0x100000) != 0 )
  {
    slider_more_widget = widget->slider_more_widget;
    v40 = slider_more_widget->widget_flags;
    if ( (v40 & 0x20) != 0 )
    {
      LOBYTE(v40) = v40 & 0xDF;
      slider_more_widget->widget_flags = v40;
      v41 = widget->slider_position_target + 0.2;
      widget->slider_position_target = v41;
      if ( v41 >= 0.89999998 )
        widget->slider_position_target = 1.0;
    }
    slider_less_widget = widget->slider_less_widget;
    v43 = slider_less_widget->widget_flags;
    if ( (v43 & 0x20) != 0 )
    {
      LOBYTE(v43) = v43 & 0xDF;
      slider_less_widget->widget_flags = v43;
      v44 = widget->slider_position_target - 0.2;
      widget->slider_position_target = v44;
      if ( v44 <= 0.1 )
        widget->slider_position_target = 0.0;
    }
    v45 = widget->slider_less_widget;
    v46 = v45->widget_flags;
    if ( widget->slider_position_target == 0.0 )
      BYTE1(v46) |= 0x80u;
    else
      v46 &= ~0x8000u;
    v45->widget_flags = v46;
    v47 = widget->slider_more_widget;
    if ( LODWORD(widget->slider_position_target) == 1065353216 )
    {
      v48 = v47->widget_flags;
      BYTE1(v48) |= 0x80u;
      v47->widget_flags = v48;
    }
    else
    {
      v47->widget_flags &= ~0x8000u;
    }
    p_current_text_color = &widget->slider_value_widget->current_text_color;
    p_current_text_color->r = widget->current_text_color.r;
    p_current_text_color->g = widget->current_text_color.g;
    p_current_text_color->b = widget->current_text_color.b;
    p_current_text_color->a = widget->current_text_color.a;
    widget->slider_value_widget->hover_blend_target = widget->hover_blend_target;
    widget->slider_value_widget->hover_blend_current = widget->hover_blend_current;
    sprintf(
      (char *const)&widget->slider_value_widget->text_buffer,
      "%02i%%",
      (unsigned int)(__int64)(widget->slider_position_target * 100.0 + 0.1));
  }
}
