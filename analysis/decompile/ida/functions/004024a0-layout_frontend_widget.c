/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: layout_frontend_widget @ 0x4024a0 */
/* selector: layout_frontend_widget */

// Recomputes one front-end widget's authored-space position, measured text bounds, and any attached slider-child offsets before the current frame draw.
int32_t __thiscall layout_frontend_widget(FrontendWidget *widget)
{
  int32_t result; // eax
  float clamped_left; // edx
  float *p_layout_top; // ebx
  float *p_clamped_left; // edi
  float authored_left; // eax
  float authored_top; // ecx
  float v8; // edx
  uint32_t widget_flags; // ecx
  double v10; // st7
  double clamped_top; // st7
  double v12; // st7
  float layout_width; // [esp+10h] [ebp-4h]

  while ( 1 )
  {
    result = widget->widget_flags;
    if ( (result & 0x800) != 0 )
    {
      clamped_left = widget->layout_top;
      p_layout_top = &widget->layout_left;
      p_clamped_left = &widget->layout_top;
      widget->layout_anchor_x = widget->layout_left;
      *(float *)widget->layout_anchor_y = clamped_left;
    }
    else if ( (result & 0x10000) != 0 )
    {
      authored_left = widget->authored_left;
      authored_top = widget->authored_top;
      p_layout_top = &widget->layout_left;
      p_clamped_left = &widget->layout_top;
      widget->layout_width = widget->authored_width;
      widget->layout_left = authored_left;
      result = LODWORD(widget->authored_height);
      widget->layout_top = authored_top;
      *(_DWORD *)widget->layout_height = result;
    }
    else
    {
      p_clamped_left = &widget->layout_top;
      p_layout_top = &widget->layout_left;
      result = (int32_t)layout_and_queue_wrapped_font_text(
                          (char *)&widget->?.raw[4],
                          LODWORD(widget->font_id),
                          LODWORD(widget->font_scale),
                          widget->layout_anchor_x,
                          *(float *)widget->layout_anchor_y,
                          &widget->layout_left,
                          &widget->layout_top,
                          &widget->layout_width,
                          (float *)widget->layout_height,
                          LODWORD(widget->text_effect_current),
                          unk_4DF935 & 1,
                          LODWORD(widget->text_alignment),
                          LODWORD(widget->anchor_x),
                          0x1000000,
                          (int)&widget->?.g,
                          1,
                          0);
    }
    v8 = *p_clamped_left;
    widget->clamped_left = *p_layout_top;
    widget_flags = widget->widget_flags;
    widget->clamped_top = v8;
    if ( (widget_flags & 0x20000000) != 0 )
      break;
    if ( *p_layout_top + widget->hot_padding + widget->layout_width <= 640.0 )
    {
      if ( *p_layout_top - widget->hot_padding < 0.0 )
        widget->clamped_left = widget->hot_padding;
    }
    else
    {
      widget->clamped_left = 640.0 - widget->hot_padding - widget->layout_width;
    }
    if ( widget->hot_padding + *p_clamped_left <= 480.0 )
    {
      if ( *p_clamped_left - widget->hot_padding < 0.0 )
        widget->clamped_top = widget->hot_padding;
    }
    else
    {
      widget->clamped_top = 480.0 - widget->hot_padding;
    }
    v10 = widget->clamped_left - *p_layout_top;
    result = widget_flags & 0x100000;
    widget->anchor_x = v10 + widget->anchor_x;
    widget->layout_anchor_x = v10 + widget->layout_anchor_x;
    *(float *)widget->layout_anchor_y = widget->clamped_top - *p_clamped_left + *(float *)widget->layout_anchor_y;
    clamped_top = widget->clamped_left;
    *p_layout_top = widget->clamped_left;
    layout_width = widget->clamped_top;
    *p_clamped_left = layout_width;
    if ( (widget_flags & 0x100000) != 0 )
    {
      widget->slider_hit_left = widget->layout_width * 0.1 + clamped_top + 4.0 - 12.0;
      widget->slider_hit_right = widget->layout_width * 0.80000001 + clamped_top - 4.0;
      v12 = *(float *)widget->layout_height * 0.5 + layout_width;
      widget->slider_hit_top = v12 - 6.0;
      widget->slider_hit_bottom = v12 + 32.0 - 6.0;
    }
    if ( !result )
      break;
    widget->slider_more_widget->layout_top = widget->clamped_top + 33.0;
    layout_frontend_widget(widget->slider_more_widget);
    widget->slider_less_widget->layout_top = widget->clamped_top + 33.0;
    layout_frontend_widget(widget->slider_less_widget);
    *(float *)widget->slider_value_widget->layout_anchor_y = widget->clamped_top + 49.0;
    widget = widget->slider_value_widget;
  }
  return result;
}

