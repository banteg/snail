/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: layout_frontend_widget @ 0x4024a0 */
/* selector: layout_frontend_widget */

// Authored void `cRBorder::RePosition()`: recomputes one widget's authored-space position, measured text bounds, and attached slider-child offsets before draw. All 24 Windows callers discard EAX; the honest void transcription is 177/177 instructions at 84.18%.
void __thiscall layout_frontend_widget(FrontendWidget *widget)
{
  FrontendWidgetFlag widget_flags; // eax
  float layout_top; // edx
  float *p_layout_left; // ebx
  float *p_layout_top; // edi
  float authored_left; // eax
  float authored_top; // ecx
  float authored_height; // eax
  float v9; // edx
  FrontendWidgetFlag v10; // ecx
  double v11; // st7
  double texture_hit_x; // st7
  double v13; // st7
  float texture_hit_y; // [esp+10h] [ebp-4h]

  while ( 1 )
  {
    widget_flags = widget->widget_flags;
    if ( (BYTE1(widget_flags) & 8) != 0 )
    {
      layout_top = widget->layout_top;
      p_layout_left = &widget->layout_left;
      p_layout_top = &widget->layout_top;
      widget->layout_anchor_x = widget->layout_left;
      widget->layout_anchor_y = layout_top;
    }
    else if ( (widget_flags & 0x10000) != 0 )
    {
      authored_left = widget->authored_left;
      authored_top = widget->authored_top;
      p_layout_left = &widget->layout_left;
      p_layout_top = &widget->layout_top;
      widget->layout_width = widget->authored_width;
      widget->layout_left = authored_left;
      authored_height = widget->authored_height;
      widget->layout_top = authored_top;
      widget->layout_height = authored_height;
    }
    else
    {
      p_layout_top = &widget->layout_top;
      p_layout_left = &widget->layout_left;
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
        &widget->idle_text_color,
        1u,
        0);
    }
    v9 = *p_layout_top;
    widget->texture_hit_x = *p_layout_left;
    v10 = widget->widget_flags;
    widget->texture_hit_y = v9;
    if ( (v10 & 0x20000000) != 0 )
      break;
    if ( *p_layout_left + widget->hot_padding + widget->layout_width <= 640.0 )
    {
      if ( *p_layout_left - widget->hot_padding < 0.0 )
        widget->texture_hit_x = widget->hot_padding;
    }
    else
    {
      widget->texture_hit_x = 640.0 - widget->hot_padding - widget->layout_width;
    }
    if ( widget->hot_padding + *p_layout_top <= 480.0 )
    {
      if ( *p_layout_top - widget->hot_padding < 0.0 )
        widget->texture_hit_y = widget->hot_padding;
    }
    else
    {
      widget->texture_hit_y = 480.0 - widget->hot_padding;
    }
    v11 = widget->texture_hit_x - *p_layout_left;
    widget->anchor_x = v11 + widget->anchor_x;
    widget->layout_anchor_x = v11 + widget->layout_anchor_x;
    widget->layout_anchor_y = widget->texture_hit_y - *p_layout_top + widget->layout_anchor_y;
    texture_hit_x = widget->texture_hit_x;
    *p_layout_left = widget->texture_hit_x;
    texture_hit_y = widget->texture_hit_y;
    *p_layout_top = texture_hit_y;
    if ( (v10 & 0x100000) == 0 )
      break;
    widget->slider_hit_left = widget->layout_width * 0.1 + texture_hit_x + 4.0 - 12.0;
    widget->slider_hit_right = widget->layout_width * 0.80000001 + texture_hit_x - 4.0;
    v13 = widget->layout_height * 0.5 + texture_hit_y;
    widget->slider_hit_top = v13 - 6.0;
    widget->slider_hit_bottom = v13 + 32.0 - 6.0;
    widget->slider_more_widget->layout_top = widget->texture_hit_y + 33.0;
    layout_frontend_widget(widget->slider_more_widget);
    widget->slider_less_widget->layout_top = widget->texture_hit_y + 33.0;
    layout_frontend_widget(widget->slider_less_widget);
    widget->slider_value_widget->layout_anchor_y = widget->texture_hit_y + 49.0;
    widget = widget->slider_value_widget;
  }
}
