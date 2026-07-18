/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_tip @ 0x448a40 */
/* selector: initialize_tip */

// Implements `cRTip::Init(cRTipData*, ...)`: builds one Tip-owned main border widget, optional OK or Disable buttons, and the timed auto-dismiss rate for transient tips. The Windows hide-disable-button formal is a 32-bit int even though mobile ports spell it bool or signed char.
void __thiscall initialize_tip(Tip *tip, TipData *definition, int32_t hide_disable_button)
{
  TipData *v4; // edi
  tColour *v5; // eax
  TipData *v6; // eax
  tColour *v7; // eax
  tColour *v8; // eax
  tColour *v9; // eax
  FrontendWidget *widget_main; // ecx
  TipData *v11; // ecx
  int32_t v12; // [esp-8h] [ebp-24h]
  float layout_y; // [esp-4h] [ebp-20h]
  float anchor_x; // [esp+0h] [ebp-1Ch]
  float anchor_xa; // [esp+0h] [ebp-1Ch]
  float anchor_xb; // [esp+0h] [ebp-1Ch]
  Color4f color; // [esp+Ch] [ebp-10h] BYREF

  tip->active = 1;
  if ( definition )
    tip->definition = definition;
  else
    tip->definition = &g_default_tip_message;
  tip->widget_main = allocate_border(&g_game_base->border_manager);
  v4 = tip->definition;
  layout_y = v4->layout_y;
  v12 = (unsigned __int8)(~(unsigned __int8)v4->flags & 4) >> 1;
  v5 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
  initialize_frontend_widget(tip->widget_main, 2u, v4->text, 20, v4->layout_y, v4->text_scale, v5, v12, layout_y);
  v6 = tip->definition;
  if ( (v6->flags & 2) != 0 )
  {
    tip->dismiss_progress = 0.0;
    tip->dismiss_step = 1.0 / (v6->dismiss_seconds * 60.0);
  }
  if ( (v6->flags & 1) != 0 )
  {
    tip->widget_ok = allocate_border(&g_game_base->border_manager);
    if ( hide_disable_button )
    {
      anchor_xb = tip->definition->layout_y;
      v9 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(tip->widget_ok, 0x14u, aOk, 20, 0.0, 0.0, v9, 2, anchor_xb);
      widget_main = tip->widget_main;
      tip->widget_disable = nullptr;
      stack_widget_below(tip->widget_ok, widget_main);
    }
    else
    {
      anchor_x = tip->definition->layout_y + 40.0;
      v7 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(tip->widget_ok, 0x14u, aOk, 20, 0.0, 0.0, v7, 2, anchor_x);
      tip->widget_disable = allocate_border(&g_game_base->border_manager);
      anchor_xa = tip->definition->layout_y - 60.0;
      v8 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(tip->widget_disable, 0x14u, aDisable, 20, 0.0, 0.0, v8, 2, anchor_xa);
      stack_widget_below(tip->widget_disable, tip->widget_main);
      stack_widget_below(tip->widget_ok, tip->widget_main);
    }
  }
  else
  {
    tip->widget_ok = nullptr;
    tip->widget_disable = nullptr;
  }
  v11 = tip->definition;
  tip->previous_outer_owner = g_game_base->players[0].frontend_state;
  if ( (v11->flags & 1) != 0 )
    g_game_base->players[0].frontend_state = 22;
}
