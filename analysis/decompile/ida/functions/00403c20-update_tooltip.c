/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_tooltip @ 0x403c20 */
/* selector: update_tooltip */

// Exact authored void cRToolTip::AI() state-machine update over the FrontendWidget-owned 0x40-byte controller: arms the hover delay, allocates and lays out the manager-owned tooltip widget, and releases it when hover ends.
void __thiscall update_tooltip(FrontendWidgetTooltip *tooltip)
{
  FrontendWidget *tooltip_widget; // ecx
  FrontendWidget *owner_widget; // ecx
  double v4; // st7
  FrontendWidget *v5; // eax
  uint32_t mode_flags; // eax
  tColour *v7; // eax
  FrontendWidget *v8; // edi
  tColour *v9; // eax
  FrontendWidget *v10; // edi
  FrontendWidget *v11; // eax
  double v12; // st7
  FrontendWidget *v13; // edi
  FrontendWidget *v14; // ecx
  FrontendWidget *v15; // ecx
  double v16; // st7
  float y; // [esp+0h] [ebp-6Ch]
  float ya; // [esp+0h] [ebp-6Ch]
  float yb; // [esp+0h] [ebp-6Ch]
  float yc; // [esp+0h] [ebp-6Ch]
  tColour *v21; // [esp+4h] [ebp-68h]
  tColour *v22; // [esp+4h] [ebp-68h]
  int32_t v23; // [esp+8h] [ebp-64h]
  float v24; // [esp+Ch] [ebp-60h]
  float anchor_x; // [esp+18h] [ebp-54h]
  Color4f color; // [esp+1Ch] [ebp-50h] BYREF
  tColour v27; // [esp+2Ch] [ebp-40h] BYREF
  Color4f v28; // [esp+3Ch] [ebp-30h] BYREF
  Color4f v29; // [esp+4Ch] [ebp-20h] BYREF
  Color4f v30; // [esp+5Ch] [ebp-10h] BYREF

  if ( tooltip->state != 1 )
  {
    if ( tooltip->state != 2 )
    {
      if ( tooltip->state == 3 && (tooltip->owner_widget->widget_flags & 0x20000) == 0 )
      {
        tooltip_widget = tooltip->tooltip_widget;
        tooltip->state = 1;
        kill_border(&g_game_base->border_manager, tooltip_widget);
        tooltip->tooltip_widget = nullptr;
      }
      return;
    }
    owner_widget = tooltip->owner_widget;
    if ( (owner_widget->widget_flags & 0x20000) == 0 )
    {
      tooltip->state = 1;
      return;
    }
    v4 = tooltip->delay_step + tooltip->delay_progress;
    tooltip->delay_progress = v4;
    if ( v4 <= 1.0 )
      return;
    if ( owner_widget->text_alignment )
      anchor_x = owner_widget->anchor_x;
    else
      anchor_x = owner_widget->layout_width * 0.5 + owner_widget->layout_anchor_x - 320.0;
    v5 = tooltip->tooltip_widget;
    tooltip->state = 3;
    if ( v5 )
      report_errorf(aToolTipOverloa);
    else
      tooltip->tooltip_widget = allocate_border(&g_game_base->border_manager);
    mode_flags = tooltip->mode_flags;
    if ( (mode_flags & 1) != 0 )
    {
      v7 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
      y = g_game_base->players[0].mouse_cursor.saved_y + 64.0;
      initialize_frontend_widget(
        tooltip->tooltip_widget,
        2u,
        (char *)tooltip,
        7,
        g_game_base->players[0].mouse_cursor.saved_x,
        y,
        v7,
        1,
        anchor_x);
LABEL_27:
      v14 = tooltip->tooltip_widget;
      if ( v14->layout_left - v14->hot_padding - v14->stack_gap < 0.0 )
        v14->layout_anchor_x = v14->stack_gap;
      v15 = tooltip->tooltip_widget;
      v16 = v15->stack_gap + v15->layout_width + v15->layout_left + v15->hot_padding;
      if ( v16 > 640.0 )
        v15->layout_anchor_x = v15->layout_anchor_x - (v16 - 640.0);
      layout_frontend_widget(tooltip->tooltip_widget);
      return;
    }
    if ( (mode_flags & 4) != 0 )
    {
      v8 = tooltip->owner_widget;
      v24 = anchor_x;
      v23 = 1;
      v9 = set_color_rgba(&v27, 1.0, 1.0, 1.0, 1.0);
LABEL_22:
      yb = v8->layout_anchor_y - v8->current_padding;
      initialize_frontend_widget(tooltip->tooltip_widget, 2u, (char *)tooltip, 7, v8->layout_anchor_x, yb, v9, v23, v24);
      v11 = tooltip->tooltip_widget;
      v12 = v11->layout_anchor_y - (v11->layout_height + v11->current_padding);
LABEL_26:
      v11->layout_anchor_y = v12;
      goto LABEL_27;
    }
    if ( (mode_flags & 2) != 0 )
    {
      v10 = tooltip->owner_widget;
      v21 = set_color_rgba((tColour *)&v28, 1.0, 1.0, 1.0, 1.0);
      ya = v10->layout_anchor_y + v10->layout_height + v10->current_padding;
      initialize_frontend_widget(
        tooltip->tooltip_widget,
        2u,
        (char *)tooltip,
        7,
        v10->layout_anchor_x,
        ya,
        v21,
        1,
        anchor_x);
    }
    else
    {
      if ( (mode_flags & 0x10) != 0 )
      {
        v8 = tooltip->owner_widget;
        v24 = 0.0;
        v23 = 0;
        v9 = set_color_rgba((tColour *)&v29, 1.0, 1.0, 1.0, 1.0);
        goto LABEL_22;
      }
      if ( (mode_flags & 8) == 0 )
        goto LABEL_27;
      v13 = tooltip->owner_widget;
      v22 = set_color_rgba((tColour *)&v30, 1.0, 1.0, 1.0, 1.0);
      yc = v13->layout_anchor_y + v13->layout_height + v13->current_padding;
      initialize_frontend_widget(tooltip->tooltip_widget, 2u, (char *)tooltip, 7, v13->layout_anchor_x, yc, v22, 0, 0.0);
    }
    v11 = tooltip->tooltip_widget;
    v12 = v11->current_padding + v11->layout_anchor_y;
    goto LABEL_26;
  }
  if ( (tooltip->owner_widget->widget_flags & 0x20000) != 0 )
  {
    tooltip->delay_progress = 0.0;
    tooltip->state = 2;
  }
}
