/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_frontend_widget @ 0x401d30 */
/* selector: initialize_frontend_widget */

// Authored void `cRBorder::Init(int, char*, int, float, float, tColour, int, float)`: constructs one shell-font widget, seeds its border style, text scale, alignment, six color blocks, and optional slider children, then links it into the active list. All 83 Windows callers discard the incidental EAX state.
void __thiscall initialize_frontend_widget(
        FrontendWidget *widget,
        uint32_t widget_flags,
        char *text,
        int32_t widget_type,
        float x,
        float y,
        tColour *color,
        int32_t text_alignment,
        float anchor_x)
{
  FrontendWidget *v10; // eax
  FrontendWidget *list_next; // eax
  tColour *p_hot_text_color; // edi
  tColour *v13; // eax
  tColour *v14; // eax
  tColour *v15; // eax
  tColour *v16; // eax
  tColour *v17; // eax
  char v18; // al
  double idle_padding; // st7
  uint32_t v20; // eax
  double v21; // st7
  tColour *v22; // eax
  tColour *v23; // eax
  tColour *v24; // eax
  int v25; // [esp+0h] [ebp-128h]
  int v26; // [esp+0h] [ebp-128h]
  float v27; // [esp+4h] [ebp-124h]
  int ArgList; // [esp+24h] [ebp-104h]
  struct tColour v29; // [esp+28h] [ebp-100h] BYREF
  tColour v30; // [esp+38h] [ebp-F0h] BYREF
  struct tColour v31; // [esp+48h] [ebp-E0h] BYREF
  struct tColour v32; // [esp+58h] [ebp-D0h] BYREF
  tColour v33; // [esp+68h] [ebp-C0h] BYREF
  struct tColour v34; // [esp+78h] [ebp-B0h] BYREF
  struct tColour v35; // [esp+88h] [ebp-A0h] BYREF
  tColour v36; // [esp+98h] [ebp-90h] BYREF
  struct tColour v37; // [esp+A8h] [ebp-80h] BYREF
  struct tColour v38; // [esp+B8h] [ebp-70h] BYREF
  struct tColour v39; // [esp+C8h] [ebp-60h] BYREF
  struct tColour v40; // [esp+D8h] [ebp-50h] BYREF
  struct tColour v41; // [esp+E8h] [ebp-40h] BYREF
  struct tColour v42; // [esp+F8h] [ebp-30h] BYREF
  struct tColour v43; // [esp+108h] [ebp-20h] BYREF
  struct tColour v44; // [esp+118h] [ebp-10h] BYREF

  widget->widget_type = widget_type;
  widget->border_texture_id = 5;
  widget->texture_hit_test_enabled = 0;
  widget->render_inset_delta = 0.0;
  widget->render_inset_base = 20.0;
  widget->render_inset_dynamic = 0;
  v10 = (FrontendWidget *)((char *)g_game_base + 2892);
  if ( (widget->list_flags & 0x200) != 0 )
  {
    report_errorf(aListAddafter);
  }
  else
  {
    widget->list_prev = v10;
    widget->list_next = v10->list_next;
    v10->list_next = widget;
    list_next = widget->list_next;
    if ( list_next )
      list_next->list_prev = widget;
    widget->list_flags |= 0x200u;
  }
  p_hot_text_color = &widget->hot_text_color;
  widget->tooltip.state = 0;
  widget->tooltip.owner_widget = widget;
  widget->tooltip.tooltip_widget = nullptr;
  widget->tooltip.owner_widget_38 = widget;
  widget->widget_flags = widget_flags | 0x40001;
  set_color_white(&widget->hot_text_color);
  set_color_white(&widget->hot_fill_color);
  switch ( widget_type )
  {
    case 20:
      widget->font_id = 0;
      widget->font_scale = 1.3;
      widget->idle_padding = 9.0;
      widget->hot_padding = 13.0;
      widget->stack_gap = 26.0;
      widget->idle_text_color = *set_color_rgba(&v37, 1.0, 0.52156866, 0.0, 0.69999999);
      v13 = set_color_rgba(&v44, 1.0, 1.0, 1.0, 1.0);
      p_hot_text_color->r = v13->r;
      widget->hot_text_color.g = v13->g;
      widget->hot_text_color.b = v13->b;
      widget->hot_text_color.a = v13->a;
      widget->idle_fill_color = *set_color_rgba(&v41, 0.32941177, 0.22352941, 0.50196081, 0.69999999);
      v14 = set_color_rgba(&v33, 0.60784316, 0.30980393, 0.69411767, 1.0);
      goto LABEL_11;
    case 21:
      widget->font_id = 0;
      widget->font_scale = 1.0;
      widget->idle_padding = 9.0;
      widget->hot_padding = 13.0;
      widget->stack_gap = 26.0;
      widget->idle_text_color = *set_color_rgba(&v38, 1.0, 0.52156866, 0.0, 0.69999999);
      v17 = set_color_rgba(&v40, 1.0, 1.0, 1.0, 1.0);
      p_hot_text_color->r = v17->r;
      widget->hot_text_color.g = v17->g;
      widget->hot_text_color.b = v17->b;
      widget->hot_text_color.a = v17->a;
      widget->idle_fill_color = *set_color_rgba(&v42, 0.32941177, 0.22352941, 0.50196081, 0.69999999);
      v14 = set_color_rgba(&v29, 0.60784316, 0.30980393, 0.69411767, 1.0);
      goto LABEL_11;
    case 22:
      widget->render_inset_base = 20.0;
      widget->font_id = 0;
      widget->font_scale = 0.64999998;
      widget->idle_padding = 1.0;
      widget->hot_padding = 3.0;
      widget->stack_gap = 2.0;
      widget->render_inset_dynamic = 1;
      widget->idle_text_color = *set_color_rgba(&v39, 1.0, 0.52156866, 0.0, 0.69999999);
      v15 = set_color_rgba(&v35, 1.0, 1.0, 1.0, 1.0);
      p_hot_text_color->r = v15->r;
      widget->hot_text_color.g = v15->g;
      widget->hot_text_color.b = v15->b;
      widget->hot_text_color.a = v15->a;
      widget->idle_fill_color = *set_color_rgba(&v43, 0.32941177, 0.22352941, 0.50196081, 0.69999999);
      v14 = set_color_rgba(&v30, 0.60784316, 0.30980393, 0.69411767, 1.0);
      goto LABEL_11;
    case 23:
      widget->font_id = 0;
      widget->font_scale = 1.14;
      widget->idle_padding = 6.0;
      widget->hot_padding = 7.0;
      widget->stack_gap = 2.0;
      widget->render_inset_base = 20.0;
      widget->idle_text_color = *set_color_rgba(&v31, 1.0, 0.52156866, 0.0, 0.69999999);
      v16 = set_color_rgba(&v32, 1.0, 1.0, 1.0, 1.0);
      p_hot_text_color->r = v16->r;
      widget->hot_text_color.g = v16->g;
      widget->hot_text_color.b = v16->b;
      widget->hot_text_color.a = v16->a;
      widget->idle_fill_color = *set_color_rgba(&v34, 0.32941177, 0.22352941, 0.50196081, 0.69999999);
      v14 = set_color_rgba(&v36, 0.60784316, 0.30980393, 0.69411767, 1.0);
LABEL_11:
      widget->hot_fill_color.r = v14->r;
      widget->hot_fill_color.g = v14->g;
      widget->hot_fill_color.b = v14->b;
      widget->hot_fill_color.a = v14->a;
      break;
    default:
      report_errorf(aUnknownBorderS);
      break;
  }
  widget->slider_position_target = 0.5;
  widget->slider_position_current = 0.5;
  *(_DWORD *)&widget->_pad_10[40] = 1;
  unhide_border_init(widget);
  rstrcpy_checked_ascii((char *)&widget->text_buffer, text);
  widget->layout_anchor_y = y;
  v18 = widget->widget_flags;
  widget->layout_anchor_x = x;
  widget->hover_blend_target = 1.0;
  if ( (v18 & 2) != 0 )
    highlight_border(widget);
  else
    unhighlight_border(widget);
  idle_padding = widget->idle_padding;
  widget->hover_blend_current = widget->hover_blend_target;
  widget->target_padding = idle_padding;
  widget->current_padding = idle_padding;
  widget->text_effect_target = 0.0;
  widget->text_effect_current = 0.0;
  widget->text_alignment = text_alignment;
  widget->anchor_x = anchor_x;
  v20 = widget->widget_flags;
  v21 = anchor_x + *((float *)g_game_base + 69695);
  widget->mouse_history_warmup_frames = 1;
  widget->anchor_x = v21;
  if ( (v20 & 0x100000) != 0 )
  {
    *(float *)&ArgList = y + 40.0;
    widget->slider_more_widget = (FrontendWidget *)allocate_border((_DWORD *)g_game_base + 723);
    v22 = set_color_rgba(&v29, 1.0, 1.0, 1.0, 1.0);
    *(float *)&v25 = *((float *)g_game_base + 69695) + 458.0;
    initialize_frontend_sprite_button(
      (int)widget->slider_more_widget,
      (unsigned int)&unk_800000 & widget->widget_flags | 0x20400814,
      42,
      v25,
      ArgList,
      v22,
      0.0,
      4);
    border_sprite_extend((int)widget->slider_more_widget, 44, 43, 45, 1);
    widget->slider_less_widget = (FrontendWidget *)allocate_border((_DWORD *)g_game_base + 723);
    v23 = set_color_rgba(&v29, 1.0, 1.0, 1.0, 1.0);
    *(float *)&v26 = *((float *)g_game_base + 69695) + 118.0;
    initialize_frontend_sprite_button(
      (int)widget->slider_less_widget,
      (unsigned int)&unk_800000 & widget->widget_flags | 0x20400814,
      38,
      v26,
      ArgList,
      v23,
      0.0,
      4);
    border_sprite_extend((int)widget->slider_less_widget, 40, 39, 41, 0);
    widget->slider_value_widget = (FrontendWidget *)allocate_border((_DWORD *)g_game_base + 723);
    v24 = set_color_rgba(&v29, 1.0, 1.0, 1.0, 1.0);
    v27 = widget->layout_anchor_y + 40.0;
    initialize_frontend_widget(widget->slider_value_widget, 0x400000u, ::text, 21, 0.0, v27, v24, 2, 0.0);
  }
  layout_frontend_widget(widget);
}

