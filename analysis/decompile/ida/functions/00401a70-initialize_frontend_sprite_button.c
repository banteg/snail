/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_frontend_sprite_button @ 0x401a70 */
/* selector: initialize_frontend_sprite_button */

// Constructs one sprite-backed cRBorder child control, including its frame texture, optional shadow offset, authored anchor, texture/layer pair, and immediate-vs-delayed click behavior.
void __thiscall initialize_frontend_sprite_button(
        FrontendWidget *widget,
        uint32_t widget_flags,
        int32_t sprite,
        float x,
        float y,
        tColour *color,
        float anchor_x,
        int32_t layer)
{
  FrontendWidget *p_border_manager; // eax
  FrontendWidget *list_next; // eax
  float hot_padding; // ecx
  float idle_padding; // edx
  float target_padding; // ecx
  double v14; // st7
  double loaded_height; // st7
  float layout_height; // edx
  Color4f colora; // [esp+8h] [ebp-10h] BYREF

  p_border_manager = (FrontendWidget *)&g_game_base->border_manager;
  if ( (widget->list_flags & 0x200) != 0 )
  {
    report_errorf(aListAddafter);
  }
  else
  {
    widget->list_prev = p_border_manager;
    widget->list_next = p_border_manager->list_next;
    p_border_manager->list_next = widget;
    list_next = widget->list_next;
    if ( list_next )
      list_next->list_prev = widget;
    widget->list_flags |= 0x200u;
  }
  widget->border_texture_id = 5;
  widget->texture_hit_test_enabled = 0;
  widget->tooltip.state = 0;
  widget->tooltip.owner_widget = widget;
  widget->tooltip.tooltip_widget = nullptr;
  widget->tooltip.input_ok_state.source_widget = widget;
  widget->render_inset_delta = 0.0;
  widget->render_inset_base = 20.0;
  widget->render_inset_dynamic = 0;
  widget->sprite_shadow_offset = 4.0;
  widget->font_id = 0;
  widget->font_scale = 1.0;
  widget->idle_padding = 10.0;
  widget->hot_padding = 15.0;
  widget->stack_gap = 20.0;
  widget->border_edge = 0.0;
  *(_DWORD *)&widget->_pad_10[40] = 1;
  unhide_border_init(widget);
  widget->layout_anchor_y = y;
  widget->widget_flags = widget_flags | 0x40801;
  widget->previous_widget_flags = widget_flags | 0x40801;
  widget->text_buffer.raw[0] = 0;
  widget->layout_anchor_x = x;
  widget->idle_fill_color = *color;
  widget->hot_fill_color = *color;
  widget->idle_text_color = *set_color_rgba((tColour *)&colora, 1.0, 1.0, 1.0, 1.0);
  widget->hot_text_color = *set_color_rgba((tColour *)&colora, 1.0, 1.0, 1.0, 1.0);
  if ( (widget->widget_flags & 2) != 0 )
  {
    hot_padding = widget->hot_padding;
    widget->hover_blend_target = 1.0;
    widget->target_padding = hot_padding;
  }
  else
  {
    idle_padding = widget->idle_padding;
    widget->hover_blend_target = 0.0;
    widget->target_padding = idle_padding;
  }
  target_padding = widget->target_padding;
  widget->hover_blend_current = widget->hover_blend_target;
  widget->current_padding = target_padding;
  widget->text_effect_target = 0.0;
  widget->text_effect_current = 0.0;
  widget->text_alignment = 0;
  widget->anchor_x = anchor_x;
  v14 = anchor_x + g_game_base->border_manager.justify_centre;
  widget->layout_left = x;
  widget->layout_top = y;
  widget->anchor_x = v14;
  widget->layout_width = (float)(*(&g_sprite_texture_table + sprite))->loaded_width;
  loaded_height = (double)(*(&g_sprite_texture_table + sprite))->loaded_height;
  widget->texture_hit_width = widget->layout_width;
  widget->texture_id = sprite;
  widget->layout_height = loaded_height;
  layout_height = widget->layout_height;
  widget->layout_anchor_x = x;
  widget->texture_hit_height = layout_height;
  widget->layout_anchor_y = y;
  widget->texture_layer = layer;
  widget->teardown_progress = 0.0;
  widget->teardown_progress_step = 0.0;
  layout_frontend_widget(widget);
}
