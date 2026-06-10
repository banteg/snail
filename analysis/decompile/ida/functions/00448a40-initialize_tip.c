/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_tip @ 0x448a40 */
/* selector: initialize_tip */

// Builds one gameplay tip slot, including the main border widget, optional OK or Disable buttons, and the timed auto-dismiss rate for transient tips.
void __thiscall initialize_tip(TipSlot *slot, TipMessageDefinition *definition, int32_t show_disable_button)
{
  TipMessageDefinition *v4; // edi
  Color4f *v5; // eax
  TipMessageDefinition *v6; // eax
  Color4f *v7; // eax
  Color4f *v8; // eax
  Color4f *v9; // eax
  void *widget_main; // ecx
  TipMessageDefinition *v11; // ecx
  int32_t v12; // [esp-8h] [ebp-24h]
  float layout_y; // [esp-4h] [ebp-20h]
  float anchor_x; // [esp+0h] [ebp-1Ch]
  float anchor_xa; // [esp+0h] [ebp-1Ch]
  float anchor_xb; // [esp+0h] [ebp-1Ch]
  Color4f color; // [esp+Ch] [ebp-10h] BYREF

  slot->active = 1;
  if ( definition )
    slot->definition = definition;
  else
    slot->definition = (TipMessageDefinition *)&unk_4AC5C8;
  slot->widget_main = (void *)allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  v4 = slot->definition;
  layout_y = v4->layout_y;
  v12 = (unsigned __int8)(~(unsigned __int8)v4->flags & 4) >> 1;
  v5 = set_color_rgba(&color, 1.0, 1.0, 1.0, 1.0);
  initialize_frontend_widget(
    (FrontendWidget *)slot->widget_main,
    2u,
    v4->text,
    20,
    v4->layout_y,
    v4->text_scale,
    v5,
    v12,
    layout_y);
  v6 = slot->definition;
  if ( (v6->flags & 2) != 0 )
  {
    slot->dismiss_progress = 0.0;
    slot->dismiss_step = 1.0 / (v6->dismiss_seconds * 60.0);
  }
  if ( (v6->flags & 1) != 0 )
  {
    slot->widget_ok = (void *)allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
    if ( show_disable_button )
    {
      anchor_xb = slot->definition->layout_y;
      v9 = set_color_rgba(&color, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget((FrontendWidget *)slot->widget_ok, 0x14u, aOk, 20, 0.0, 0.0, v9, 2, anchor_xb);
      widget_main = slot->widget_main;
      slot->widget_disable = nullptr;
      stack_widget_below((int)slot->widget_ok, (int)widget_main);
    }
    else
    {
      anchor_x = slot->definition->layout_y + 40.0;
      v7 = set_color_rgba(&color, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget((FrontendWidget *)slot->widget_ok, 0x14u, aOk, 20, 0.0, 0.0, v7, 2, anchor_x);
      slot->widget_disable = (void *)allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      anchor_xa = slot->definition->layout_y - 60.0;
      v8 = set_color_rgba(&color, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget(
        (FrontendWidget *)slot->widget_disable,
        0x14u,
        aDisable,
        20,
        0.0,
        0.0,
        v8,
        2,
        anchor_xa);
      stack_widget_below((int)slot->widget_disable, (int)slot->widget_main);
      stack_widget_below((int)slot->widget_ok, (int)slot->widget_main);
    }
  }
  else
  {
    slot->widget_ok = nullptr;
    slot->widget_disable = nullptr;
  }
  v11 = slot->definition;
  slot->previous_outer_owner = *((_DWORD *)MEMORY[0x4DF904] + 110);
  if ( (v11->flags & 1) != 0 )
    *((_DWORD *)MEMORY[0x4DF904] + 110) = 22;
}

