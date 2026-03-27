/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_frontend_widget_interaction @ 0x402820 */
/* selector: update_frontend_widget_interaction */

// Runs one front-end widget's per-frame interaction state, including hover easing, delayed click-bit dispatch, slider-arrow adjustments, bounds refresh, and draw.
void __thiscall update_frontend_widget_interaction(FrontendWidget *widget)
{
  uint32_t v2; // edx
  uint32_t widget_flags; // eax
  uint32_t list_flags; // eax
  char *v5; // ecx
  FrontendWidget *list_next; // eax
  FrontendWidget *list_prev; // eax
  uint32_t v8; // eax
  char *v9; // ecx
  uint32_t v10; // eax
  FrontendWidget *v11; // eax
  FrontendWidget *v12; // eax
  double v13; // st7
  uint32_t v14; // eax
  FrontendWidget *v15; // eax
  FrontendWidget *v16; // eax
  uint32_t v17; // eax
  uint32_t v18; // eax
  uint32_t v19; // ecx
  uint32_t v20; // eax
  uint32_t v21; // eax
  uint32_t v22; // eax
  uint32_t v23; // eax
  uint32_t v24; // eax
  _DWORD *v25; // ecx
  uint32_t v26; // eax
  uint32_t v27; // edx
  uint32_t v28; // eax
  uint32_t v29; // eax
  double v30; // st7
  double v31; // st7
  double v32; // st7
  double v33; // st6
  uint32_t v34; // eax
  float authored_top; // eax
  float authored_width; // ecx
  float authored_height; // edx
  float previous_mouse_x; // eax
  FrontendWidget *slider_more_widget; // ecx
  uint32_t v40; // eax
  double v41; // st7
  FrontendWidget *slider_less_widget; // ecx
  uint32_t v43; // eax
  double v44; // st7
  FrontendWidget *v45; // eax
  uint32_t v46; // edx
  FrontendWidget *v47; // eax
  uint32_t v48; // ecx
  float *p_g; // ecx
  float v50; // [esp+0h] [ebp-24h]
  float v51; // [esp+0h] [ebp-24h]
  float v52; // [esp+4h] [ebp-20h]
  float v53; // [esp+4h] [ebp-20h]
  float v54; // [esp+8h] [ebp-1Ch]
  float v55; // [esp+8h] [ebp-1Ch]
  float v56; // [esp+Ch] [ebp-18h]
  float v57; // [esp+Ch] [ebp-18h]
  char v58; // [esp+1Ch] [ebp-8h]

  widget->previous_widget_flags = widget->widget_flags;
  v2 = widget->widget_flags & 0xFFFDFFFF;
  widget->widget_flags = v2;
  if ( (v2 & 0x100000) != 0 )
  {
    widget->slider_hit_left = widget->layout_height * 0.1 + widget->layout_top + 4.0 - 12.0;
    widget->slider_hit_right = widget->layout_height * 0.80000001 + widget->layout_top - 4.0;
    widget->slider_hit_top = *(float *)widget->_pad_24c * 0.5 + widget->clamped_left - 6.0;
    widget->slider_hit_bottom = *(float *)widget->_pad_24c * 0.5 + widget->clamped_left + 32.0 - 6.0;
  }
  widget->slider_position_current = (widget->slider_position_target - widget->slider_position_current) * 0.80000001
                                  + widget->slider_position_current;
  widget_flags = widget->widget_flags;
  if ( !widget_flags )
  {
    list_flags = widget->list_flags;
    v5 = (char *)MEMORY[0x4DF904] + 1448;
    if ( (list_flags & 0x200) != 0 )
    {
      if ( (list_flags & 0x40) != 0 )
      {
        report_errorf(aListRemoveNext);
        reset_tooltip((FrontendWidgetTooltip *)&widget->tooltip.state);
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
          *((_DWORD *)v5 + 1) = widget->list_next;
        widget->list_next = *((FrontendWidget **)v5 + 2);
        *((_DWORD *)v5 + 2) = widget;
        v8 = widget->list_flags;
        BYTE1(v8) &= ~2u;
        widget->list_flags = v8;
        reset_tooltip((FrontendWidgetTooltip *)&widget->tooltip.state);
      }
    }
    else
    {
      report_errorf(aListRemove);
      reset_tooltip((FrontendWidgetTooltip *)&widget->tooltip.state);
    }
    return;
  }
  if ( (widget_flags & 0x200) != 0 )
  {
    BYTE1(widget_flags) &= ~2u;
    widget->widget_flags = widget_flags;
    v9 = (char *)MEMORY[0x4DF904] + 1448;
    v10 = widget->list_flags;
    if ( (v10 & 0x200) == 0 )
    {
LABEL_16:
      report_errorf(aListRemove);
LABEL_33:
      reset_tooltip((FrontendWidgetTooltip *)&widget->tooltip.state);
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
      widget->list_next = *((FrontendWidget **)v9 + 2);
      *((_DWORD *)v9 + 2) = widget;
      v17 = widget->list_flags;
      BYTE1(v17) &= ~2u;
      widget->list_flags = v17;
      goto LABEL_33;
    }
    goto LABEL_31;
  }
  if ( (widget_flags & 0x400) == 0 )
  {
    if ( (widget_flags & 0x1000) != 0 )
      return;
    if ( (widget_flags & 0x8000) != 0 )
    {
      widget->text_effect_current = 0.0;
      v18 = widget->widget_flags;
LABEL_82:
      LOBYTE(v18) = v18 & 0xFD;
      widget->widget_flags = v18;
      goto LABEL_83;
    }
    if ( (widget_flags & 2) != 0 )
      widget->hover_blend_current = 1.0;
    v19 = widget->widget_flags;
    if ( (v19 & 0x2000000) != 0
      && !LODWORD(widget->previous_mouse_x)
      && (*((float *)MEMORY[0x4DF904] + 167) != widget->previous_mouse_y
       || *((float *)MEMORY[0x4DF904] + 168) != *(float *)widget->_pad_280) )
    {
      widget->widget_flags = v19 | 0x4000000;
    }
    if ( (widget->widget_flags & 0x80000) != 0
      && is_mouse_captured((char *)MEMORY[0x4DF904] + 656)
      && read_pressed_text_input_key_code() == widget->shortcut_key_code )
    {
      reset_tooltip((FrontendWidgetTooltip *)&widget->tooltip.state);
      v20 = widget->widget_flags;
      if ( (v20 & 0x1000000) != 0 )
      {
        LOBYTE(v20) = v20 | 0x20;
        widget->widget_flags = v20;
      }
      else
      {
        queue_frontend_widget_flag_after_delay((int)MEMORY[0x4DF904] + 2892, (int)widget, 32);
      }
    }
    if ( !is_mouse_captured((char *)MEMORY[0x4DF904] + 656) || !border_mouse_test((int)widget) )
    {
      v27 = widget->widget_flags & 0xFFDFFFFF;
      widget->widget_flags = v27;
      if ( (v27 & 0x2000) == 0 && (v27 & 4) != 0 )
        unhighlight_border(widget);
      widget->text_effect_current = 0.0;
      v18 = widget->widget_flags;
      if ( (v18 & 4) == 0 )
        goto LABEL_83;
      goto LABEL_82;
    }
    v21 = widget->widget_flags | 0x20000;
    widget->widget_flags = v21;
    if ( (v21 & 4) != 0 )
    {
      widget->hover_blend_current = 1.0;
      widget->current_padding = widget->target_padding;
    }
    if ( (widget->widget_flags & 8) != 0 )
      widget->text_effect_current = 1.0;
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
      v25 = MEMORY[0x4DF904];
      if ( *((_BYTE *)MEMORY[0x4DF904] + 278764) || (*(_BYTE *)(*((_DWORD *)MEMORY[0x4DF904] + 163) + 61) & 0x40) == 0 )
      {
LABEL_72:
        v26 = widget->widget_flags;
        if ( (v26 & 0x40) != 0 && *(char *)(v25[163] + 61) < 0 )
        {
          if ( (v26 & 0x1000000) != 0 )
          {
            LOBYTE(v26) = v26 | 0x80;
            widget->widget_flags = v26;
          }
          else
          {
            queue_frontend_widget_flag_after_delay((int)(v25 + 723), (int)widget, 128);
          }
          play_sound_effect(8);
          reset_tooltip((FrontendWidgetTooltip *)&widget->tooltip.state);
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
        queue_frontend_widget_flag_after_delay((int)MEMORY[0x4DF904] + 2892, (int)widget, 32);
      }
      if ( ((unsigned int)&unk_800000 & widget->widget_flags) == 0 )
        play_sound_effect(8);
      if ( ((int)widget->tooltip.owner_widget & 0x20) == 0 )
        reset_tooltip((FrontendWidgetTooltip *)&widget->tooltip.state);
    }
    v25 = MEMORY[0x4DF904];
    goto LABEL_72;
  }
  v13 = widget->stack_gap + widget->aux_step;
  widget->aux_step = v13;
  if ( v13 > 1.0 )
  {
    v9 = (char *)MEMORY[0x4DF904] + 1448;
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
    *((_DWORD *)v9 + 1) = widget->list_next;
    goto LABEL_32;
  }
LABEL_83:
  v28 = widget->widget_flags;
  if ( (v28 & 0x8000) != 0 )
  {
    widget->widget_flags = v28 & 0xFFDFFFFF;
    unhighlight_border(widget);
  }
  v29 = widget->widget_flags;
  if ( (v29 & 0x40000) != 0 )
  {
    widget->widget_flags = v29 & 0xFFFBFFFF;
    widget->idle_padding = widget->hover_blend_current;
    widget->text_effect_target = widget->current_padding;
    widget->render_inset_delta = widget->text_effect_current;
  }
  else
  {
    widget->idle_padding = (widget->hover_blend_current - widget->idle_padding) * 0.1 + widget->idle_padding;
    widget->text_effect_target = (widget->current_padding - widget->text_effect_target) * 0.1
                               + widget->text_effect_target;
    v30 = (widget->text_effect_current - widget->render_inset_delta) * 0.1 + widget->render_inset_delta;
    widget->render_inset_delta = v30;
    v31 = widget->text_effect_current - v30;
    if ( v31 < 0.0 )
      v31 = -v31;
    if ( v31 < 0.1 )
      widget->render_inset_delta = widget->text_effect_current;
  }
  if ( (widget->widget_flags & 0x2000) != 0 )
  {
    if ( is_mouse_captured((char *)MEMORY[0x4DF904] + 656) )
    {
      border_input_text((int)widget);
      if ( (widget->widget_flags & 0x2000) == 0 )
        activate_all_borders((int *)MEMORY[0x4DF904] + 723);
    }
  }
  update_twinkle_manager(widget->_pad_80);
  update_tooltip((FrontendWidgetTooltip *)&widget->tooltip.state);
  v58 = BYTE1(widget->widget_flags) & 1;
  layout_frontend_widget(widget);
  if ( (widget->widget_flags & 0x1000) == 0 )
  {
    v32 = 1.0 - widget->idle_padding;
    v56 = widget->idle_padding * widget->current_text_color.r + v32 * widget->hot_fill_color.r;
    v54 = widget->idle_padding * widget->hot_fill_color.a + v32 * widget->idle_fill_color.a;
    v52 = widget->idle_padding * widget->hot_fill_color.b + v32 * widget->idle_fill_color.b;
    v50 = widget->idle_padding * widget->hot_fill_color.g + v32 * widget->idle_fill_color.g;
    store_color4f((Color4f *)&widget->current_fill_color.g, v50, v52, v54, v56);
    v33 = 1.0 - widget->idle_padding;
    v57 = widget->idle_padding * widget->hover_blend_target + v33 * widget->hot_text_color.r;
    v55 = widget->idle_padding * widget->hot_text_color.a + v33 * widget->idle_text_color.a;
    v53 = widget->idle_padding * widget->hot_text_color.b + v33 * widget->idle_text_color.b;
    v51 = widget->idle_padding * widget->hot_text_color.g + v33 * widget->idle_text_color.g;
    store_color4f((Color4f *)&widget->current_text_color.g, v51, v53, v55, v57);
    v34 = widget->widget_flags;
    if ( (v34 & 0x8000) != 0 )
    {
      widget->current_text_color.g = widget->current_text_color.g * 0.5;
      widget->current_text_color.b = widget->current_text_color.b * 0.5;
      widget->current_text_color.a = widget->current_text_color.a * 0.5;
      widget->idle_text_color.r = widget->idle_text_color.r * 0.5;
      widget->current_fill_color.g = widget->current_fill_color.g * 0.5;
      widget->current_fill_color.b = widget->current_fill_color.b * 0.5;
      widget->current_fill_color.a = widget->current_fill_color.a * 0.5;
      widget->idle_fill_color.r = widget->idle_fill_color.r * 0.5;
    }
    if ( (v34 & 0x800) == 0 )
    {
      if ( (v34 & 0x10000) != 0 )
      {
        authored_top = widget->authored_top;
        authored_width = widget->authored_width;
        widget->layout_top = widget->authored_left;
        authored_height = widget->authored_height;
        widget->clamped_left = authored_top;
        widget->layout_height = authored_width;
        *(float *)widget->_pad_24c = authored_height;
      }
      else
      {
        layout_and_queue_wrapped_font_text(
          (char *)&widget->text_buffer.raw[4],
          LODWORD(widget->font_scale),
          LODWORD(widget->layout_anchor_x),
          widget->layout_anchor_y,
          *(float *)widget->_pad_6f8,
          &widget->layout_top,
          &widget->clamped_left,
          &widget->layout_height,
          (float *)widget->_pad_24c,
          LODWORD(widget->render_inset_delta),
          unk_4DF935 & 1,
          LODWORD(widget->anchor_x),
          LODWORD(widget->aux_progress),
          0x1000000,
          (int)&widget->current_text_color.g,
          0,
          v58);
      }
    }
    draw_frontend_widget((int)widget);
  }
  previous_mouse_x = widget->previous_mouse_x;
  if ( previous_mouse_x != 0.0 )
    LODWORD(widget->previous_mouse_x) = LODWORD(previous_mouse_x) - 1;
  widget->previous_mouse_y = *((float *)MEMORY[0x4DF904] + 167);
  *(_DWORD *)widget->_pad_280 = *((_DWORD *)MEMORY[0x4DF904] + 168);
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
    p_g = &widget->slider_value_widget->current_text_color.g;
    *p_g = widget->current_text_color.g;
    p_g[1] = widget->current_text_color.b;
    p_g[2] = widget->current_text_color.a;
    p_g[3] = widget->idle_text_color.r;
    widget->slider_value_widget->hover_blend_current = widget->hover_blend_current;
    widget->slider_value_widget->idle_padding = widget->idle_padding;
    sprintf(
      (char *const)&widget->slider_value_widget->text_buffer.raw[4],
      "%02i%%",
      (unsigned int)(__int64)(widget->slider_position_target * 100.0 + 0.1));
  }
}

