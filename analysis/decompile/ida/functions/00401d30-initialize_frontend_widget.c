/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_frontend_widget @ 0x401d30 */
/* selector: initialize_frontend_widget */

// Constructs one shell-font front-end widget, seeds its border style, text scale, alignment, colors, and optional slider-child controls, then links it into the active widget list.
int32_t __thiscall initialize_frontend_widget(
        FrontendWidget *widget,
        uint32_t widget_flags,
        char *text,
        int32_t widget_type,
        float x,
        float y,
        Color4f *color,
        int32_t text_alignment,
        float anchor_x)
{
  FrontendWidget *v10; // eax
  FrontendWidget *list_next; // eax
  float *p_g; // edi
  Color4f *v13; // eax
  Color4f *v14; // eax
  Color4f *v15; // eax
  Color4f *v16; // eax
  Color4f *v17; // eax
  char v18; // al
  double hot_padding; // st7
  uint32_t v20; // eax
  double v21; // st7
  Color4f *v22; // eax
  Color4f *v23; // eax
  Color4f *v24; // eax
  int v26; // [esp+0h] [ebp-128h]
  int v27; // [esp+0h] [ebp-128h]
  float v28; // [esp+4h] [ebp-124h]
  int ArgList; // [esp+24h] [ebp-104h]
  Color4f v30; // [esp+28h] [ebp-100h] BYREF
  Color4f v31; // [esp+38h] [ebp-F0h] BYREF
  Color4f v32; // [esp+48h] [ebp-E0h] BYREF
  Color4f v33; // [esp+58h] [ebp-D0h] BYREF
  Color4f v34; // [esp+68h] [ebp-C0h] BYREF
  Color4f v35; // [esp+78h] [ebp-B0h] BYREF
  Color4f v36; // [esp+88h] [ebp-A0h] BYREF
  Color4f v37; // [esp+98h] [ebp-90h] BYREF
  Color4f v38; // [esp+A8h] [ebp-80h] BYREF
  Color4f v39; // [esp+B8h] [ebp-70h] BYREF
  Color4f v40; // [esp+C8h] [ebp-60h] BYREF
  Color4f v41; // [esp+D8h] [ebp-50h] BYREF
  Color4f v42; // [esp+E8h] [ebp-40h] BYREF
  Color4f v43; // [esp+F8h] [ebp-30h] BYREF
  Color4f v44; // [esp+108h] [ebp-20h] BYREF
  Color4f v45; // [esp+118h] [ebp-10h] BYREF

  widget->widget_type = widget_type;
  *(_DWORD *)&widget->_pad_10[56] = 5;
  widget->state_5c = 0;
  widget->render_inset_delta = 0.0;
  *(_DWORD *)&widget->render_inset_base = 1101004800;
  LOBYTE(widget->render_inset_dynamic) = 0;
  v10 = (FrontendWidget *)((char *)MEMORY[0x4DF904] + 2892);
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
  p_g = &widget->?.g;
  widget->?.mode_flags = 0;
  LODWORD(widget->?.delay_progress) = widget;
  *(_DWORD *)widget->?._pad_1c = 0;
  *(_DWORD *)widget->?._pad_3c = widget;
  widget->widget_flags = widget_flags | 0x40001;
  set_color_white(&widget->?.g);
  set_color_white(&widget->?.g);
  switch ( widget_type )
  {
    case 20:
      widget->font_id = 0.0;
      widget->font_scale = 1.3;
      widget->idle_padding = 9.0;
      widget->hot_padding = 13.0;
      widget->stack_gap = 1104150528;
      *(Color4f *)&widget->?.g = *set_color_rgba(&v38, 1.0, 0.52156866, 0.0, 0.69999999);
      v13 = set_color_rgba(&v45, 1.0, 1.0, 1.0, 1.0);
      *p_g = v13->r;
      widget->?.b = v13->g;
      widget->?.a = v13->b;
      widget->? = v13->a;
      *(Color4f *)&widget->?.g = *set_color_rgba(&v42, 0.32941177, 0.22352941, 0.50196081, 0.69999999);
      v14 = set_color_rgba(&v34, 0.60784316, 0.30980393, 0.69411767, 1.0);
      goto LABEL_11;
    case 21:
      widget->font_id = 0.0;
      widget->font_scale = 1.0;
      widget->idle_padding = 9.0;
      widget->hot_padding = 13.0;
      widget->stack_gap = 1104150528;
      *(Color4f *)&widget->?.g = *set_color_rgba(&v39, 1.0, 0.52156866, 0.0, 0.69999999);
      v17 = set_color_rgba(&v41, 1.0, 1.0, 1.0, 1.0);
      *p_g = v17->r;
      widget->?.b = v17->g;
      widget->?.a = v17->b;
      widget->? = v17->a;
      *(Color4f *)&widget->?.g = *set_color_rgba(&v43, 0.32941177, 0.22352941, 0.50196081, 0.69999999);
      v14 = set_color_rgba(&v30, 0.60784316, 0.30980393, 0.69411767, 1.0);
      goto LABEL_11;
    case 22:
      *(_DWORD *)&widget->render_inset_base = 1101004800;
      widget->font_id = 0.0;
      widget->font_scale = 0.64999998;
      widget->idle_padding = 1.0;
      widget->hot_padding = 3.0;
      widget->stack_gap = 0x40000000;
      LOBYTE(widget->render_inset_dynamic) = 1;
      *(Color4f *)&widget->?.g = *set_color_rgba(&v40, 1.0, 0.52156866, 0.0, 0.69999999);
      v15 = set_color_rgba(&v36, 1.0, 1.0, 1.0, 1.0);
      *p_g = v15->r;
      widget->?.b = v15->g;
      widget->?.a = v15->b;
      widget->? = v15->a;
      *(Color4f *)&widget->?.g = *set_color_rgba(&v44, 0.32941177, 0.22352941, 0.50196081, 0.69999999);
      v14 = set_color_rgba(&v31, 0.60784316, 0.30980393, 0.69411767, 1.0);
      goto LABEL_11;
    case 23:
      widget->font_id = 0.0;
      widget->font_scale = 1.14;
      widget->idle_padding = 6.0;
      widget->hot_padding = 7.0;
      widget->stack_gap = 0x40000000;
      *(_DWORD *)&widget->render_inset_base = 1101004800;
      *(Color4f *)&widget->?.g = *set_color_rgba(&v32, 1.0, 0.52156866, 0.0, 0.69999999);
      v16 = set_color_rgba(&v33, 1.0, 1.0, 1.0, 1.0);
      *p_g = v16->r;
      widget->?.b = v16->g;
      widget->?.a = v16->b;
      widget->? = v16->a;
      *(Color4f *)&widget->?.g = *set_color_rgba(&v35, 0.32941177, 0.22352941, 0.50196081, 0.69999999);
      v14 = set_color_rgba(&v37, 0.60784316, 0.30980393, 0.69411767, 1.0);
LABEL_11:
      widget->?.g = v14->r;
      widget->?.b = v14->g;
      widget->?.a = v14->b;
      widget->?.r = v14->a;
      break;
    default:
      report_errorf(aUnknownBorderS);
      break;
  }
  widget->slider_position_target = 0.5;
  widget->slider_position_current = 0.5;
  *(_DWORD *)&widget->_pad_10[40] = 1;
  unhide_border_init(widget);
  rstrcpy_checked_ascii((char *)&widget->?.raw[4], text);
  *(float *)widget->layout_anchor_y = y;
  v18 = widget->widget_flags;
  widget->layout_anchor_x = x;
  widget->hover_blend_target = 1.0;
  if ( (v18 & 2) != 0 )
    highlight_border(widget);
  else
    unhighlight_border(widget);
  hot_padding = widget->idle_padding;
  widget->hover_blend_current = widget->hover_blend_target;
  widget->target_padding = hot_padding;
  widget->current_padding = hot_padding;
  widget->text_effect_target = 0.0;
  widget->text_effect_current = 0.0;
  LODWORD(widget->text_alignment) = text_alignment;
  widget->anchor_x = anchor_x;
  v20 = widget->widget_flags;
  v21 = anchor_x + *((float *)MEMORY[0x4DF904] + 69695);
  LODWORD(widget->mouse_settle_frames) = 1;
  widget->anchor_x = v21;
  if ( (v20 & 0x100000) != 0 )
  {
    *(float *)&ArgList = y + 40.0;
    widget->slider_more_widget = (FrontendWidget *)allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
    v22 = set_color_rgba(&v30, 1.0, 1.0, 1.0, 1.0);
    *(float *)&v26 = *((float *)MEMORY[0x4DF904] + 69695) + 458.0;
    initialize_frontend_sprite_button(
      (int)widget->slider_more_widget,
      (unsigned int)&unk_800000 & widget->widget_flags | 0x20400814,
      42,
      v26,
      ArgList,
      v22,
      0.0,
      4);
    border_sprite_extend((int)widget->slider_more_widget, 44, 43, 45, 1);
    widget->slider_less_widget = (FrontendWidget *)allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
    v23 = set_color_rgba(&v30, 1.0, 1.0, 1.0, 1.0);
    *(float *)&v27 = *((float *)MEMORY[0x4DF904] + 69695) + 118.0;
    initialize_frontend_sprite_button(
      (int)widget->slider_less_widget,
      (unsigned int)&unk_800000 & widget->widget_flags | 0x20400814,
      38,
      v27,
      ArgList,
      v23,
      0.0,
      4);
    border_sprite_extend((int)widget->slider_less_widget, 40, 39, 41, 0);
    widget->slider_value_widget = (FrontendWidget *)allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
    v24 = set_color_rgba(&v30, 1.0, 1.0, 1.0, 1.0);
    v28 = *(float *)widget->layout_anchor_y + 40.0;
    initialize_frontend_widget(widget->slider_value_widget, 0x400000u, ::text, 21, 0.0, v28, v24, 2, 0.0);
  }
  return layout_frontend_widget(widget);
}

