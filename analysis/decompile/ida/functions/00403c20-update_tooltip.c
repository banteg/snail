/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_tooltip @ 0x403c20 */
/* selector: update_tooltip */

int32_t __thiscall update_tooltip(FrontendWidgetTooltip *tooltip)
{
  int32_t result; // eax
  FrontendWidget *tooltip_widget; // ecx
  FrontendWidget *owner_widget; // ecx
  double v5; // st7
  __int16 v6; // fps
  bool v7; // c0
  char v8; // c2
  bool v9; // c3
  FrontendWidget *v10; // eax
  uint32_t mode_flags; // eax
  Color4f *v12; // eax
  float *v13; // edi
  Color4f *v14; // eax
  float *v15; // edi
  float *v16; // eax
  double v17; // st7
  float *v18; // edi
  FrontendWidget *v19; // ecx
  float *pad_00; // ecx
  double v21; // st7
  float v22; // [esp+0h] [ebp-6Ch]
  float v23; // [esp+0h] [ebp-6Ch]
  float v24; // [esp+0h] [ebp-6Ch]
  float v25; // [esp+0h] [ebp-6Ch]
  Color4f *v26; // [esp+4h] [ebp-68h]
  Color4f *v27; // [esp+4h] [ebp-68h]
  int32_t v28; // [esp+8h] [ebp-64h]
  float v29; // [esp+Ch] [ebp-60h]
  float aux_progress; // [esp+18h] [ebp-54h]
  Color4f v31; // [esp+1Ch] [ebp-50h] BYREF
  Color4f v32; // [esp+2Ch] [ebp-40h] BYREF
  Color4f v33; // [esp+3Ch] [ebp-30h] BYREF
  Color4f v34; // [esp+4Ch] [ebp-20h] BYREF
  Color4f v35; // [esp+5Ch] [ebp-10h] BYREF

  if ( tooltip->state != 1 )
  {
    result = tooltip->state - 2;
    if ( tooltip->state != 2 )
    {
      result = tooltip->state - 3;
      if ( tooltip->state == 3 )
      {
        result = (int32_t)tooltip->owner_widget;
        if ( (*(_DWORD *)(result + 416) & 0x20000) == 0 )
        {
          tooltip_widget = tooltip->tooltip_widget;
          tooltip->state = 1;
          kill_border(tooltip_widget);
          tooltip->tooltip_widget = nullptr;
        }
      }
      return result;
    }
    owner_widget = tooltip->owner_widget;
    if ( (owner_widget->widget_flags & 0x20000) == 0 )
    {
      tooltip->state = 1;
      return result;
    }
    v5 = tooltip->delay_step + tooltip->delay_progress;
    tooltip->delay_progress = v5;
    v7 = v5 < 1.0;
    v8 = 0;
    v9 = v5 == 1.0;
    LOWORD(result) = v6;
    if ( v5 <= 1.0 )
      return result;
    if ( LODWORD(owner_widget->text_alignment) )
      aux_progress = owner_widget->anchor_x;
    else
      aux_progress = owner_widget->layout_width * 0.5 + owner_widget->layout_anchor_x - 320.0;
    v10 = tooltip->tooltip_widget;
    tooltip->state = 3;
    if ( v10 )
      report_errorf(aToolTipOverloa);
    else
      tooltip->tooltip_widget = (FrontendWidget *)allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
    mode_flags = tooltip->mode_flags;
    if ( (mode_flags & 1) != 0 )
    {
      v12 = set_color_rgba(&v31, 1.0, 1.0, 1.0, 1.0);
      v22 = *((float *)MEMORY[0x4DF904] + 168) + 64.0;
      initialize_frontend_widget(
        tooltip->tooltip_widget,
        2u,
        (char *)tooltip,
        7,
        *((float *)MEMORY[0x4DF904] + 167),
        v22,
        v12,
        1,
        aux_progress);
LABEL_27:
      v19 = tooltip->tooltip_widget;
      if ( v19->layout_left - v19->hot_padding - *(float *)&v19->stack_gap < 0.0 )
        LODWORD(v19->layout_anchor_x) = v19->stack_gap;
      pad_00 = (float *)tooltip->tooltip_widget->_pad_00;
      v21 = pad_00[155] + pad_00[146] + pad_00[142] + pad_00[134];
      if ( v21 > 640.0 )
        pad_00[445] = pad_00[445] - (v21 - 640.0);
      return layout_frontend_widget(tooltip->tooltip_widget);
    }
    if ( (mode_flags & 4) != 0 )
    {
      v13 = (float *)tooltip->owner_widget->_pad_00;
      v29 = aux_progress;
      v28 = 1;
      v14 = set_color_rgba(&v32, 1.0, 1.0, 1.0, 1.0);
LABEL_22:
      v24 = v13[446] - v13[136];
      initialize_frontend_widget(tooltip->tooltip_widget, 2u, (char *)tooltip, 7, v13[445], v24, v14, v28, v29);
      v16 = (float *)tooltip->tooltip_widget->_pad_00;
      v17 = v16[446] - (v16[147] + v16[136]);
LABEL_26:
      v16[446] = v17;
      goto LABEL_27;
    }
    if ( (mode_flags & 2) != 0 )
    {
      v15 = (float *)tooltip->owner_widget->_pad_00;
      v26 = set_color_rgba(&v33, 1.0, 1.0, 1.0, 1.0);
      v23 = v15[446] + v15[147] + v15[136];
      initialize_frontend_widget(tooltip->tooltip_widget, 2u, (char *)tooltip, 7, v15[445], v23, v26, 1, aux_progress);
    }
    else
    {
      if ( (mode_flags & 0x10) != 0 )
      {
        v13 = (float *)tooltip->owner_widget->_pad_00;
        v29 = 0.0;
        v28 = 0;
        v14 = set_color_rgba(&v34, 1.0, 1.0, 1.0, 1.0);
        goto LABEL_22;
      }
      if ( (mode_flags & 8) == 0 )
        goto LABEL_27;
      v18 = (float *)tooltip->owner_widget->_pad_00;
      v27 = set_color_rgba(&v35, 1.0, 1.0, 1.0, 1.0);
      v25 = v18[446] + v18[147] + v18[136];
      initialize_frontend_widget(tooltip->tooltip_widget, 2u, (char *)tooltip, 7, v18[445], v25, v27, 0, 0.0);
    }
    v16 = (float *)tooltip->tooltip_widget->_pad_00;
    v17 = v16[136] + v16[446];
    goto LABEL_26;
  }
  result = (int32_t)tooltip->owner_widget;
  if ( (*(_DWORD *)(result + 416) & 0x20000) != 0 )
  {
    tooltip->delay_progress = 0.0;
    tooltip->state = 2;
  }
  return result;
}

