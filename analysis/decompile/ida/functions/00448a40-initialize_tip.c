/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_tip @ 0x448a40 */
/* selector: initialize_tip */

// Builds one gameplay tip slot, including the main border widget, optional OK or Disable buttons, and the timed auto-dismiss rate for transient tips.
int32_t __thiscall initialize_tip(TipSlot *slot, TipMessageDefinition *definition, int32_t show_only_ok)
{
  TipMessageDefinition *v4; // edi
  Color4f *v5; // eax
  TipMessageDefinition *v6; // eax
  Color4f *v7; // eax
  Color4f *v8; // eax
  Color4f *v9; // eax
  void *widget_main; // ecx
  TipMessageDefinition *v11; // ecx
  int32_t result; // eax
  int32_t v13; // [esp-8h] [ebp-24h]
  float layout_y; // [esp-4h] [ebp-20h]
  float v15; // [esp+0h] [ebp-1Ch]
  float v16; // [esp+0h] [ebp-1Ch]
  float v17; // [esp+0h] [ebp-1Ch]
  Color4f v18; // [esp+Ch] [ebp-10h] BYREF

  slot->active = 1;
  if ( definition )
    slot->definition = definition;
  else
    slot->definition = (TipMessageDefinition *)&unk_4AC5C8;
  slot->widget_main = (void *)allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  v4 = slot->definition;
  layout_y = v4->layout_y;
  v13 = (unsigned __int8)(~(unsigned __int8)v4->flags & 4) >> 1;
  v5 = set_color_rgba(&v18, 1.0, 1.0, 1.0, 1.0);
  initialize_frontend_widget(
    (FrontendWidget *)slot->widget_main,
    2u,
    v4->text,
    20,
    v4->layout_y,
    v4->text_scale,
    v5,
    v13,
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
    if ( show_only_ok )
    {
      v17 = slot->definition->layout_y;
      v9 = set_color_rgba(&v18, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget((FrontendWidget *)slot->widget_ok, 0x14u, aOk, 20, 0.0, 0.0, v9, 2, v17);
      widget_main = slot->widget_main;
      slot->widget_disable = nullptr;
      stack_widget_below((int)slot->widget_ok, (int)widget_main);
    }
    else
    {
      v15 = slot->definition->layout_y + 40.0;
      v7 = set_color_rgba(&v18, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget((FrontendWidget *)slot->widget_ok, 0x14u, aOk, 20, 0.0, 0.0, v7, 2, v15);
      slot->widget_disable = (void *)allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
      v16 = slot->definition->layout_y - 60.0;
      v8 = set_color_rgba(&v18, 1.0, 1.0, 1.0, 1.0);
      initialize_frontend_widget((FrontendWidget *)slot->widget_disable, 0x14u, aDisable, 20, 0.0, 0.0, v8, 2, v16);
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
  result = *((_DWORD *)MEMORY[0x4DF904] + 110);
  slot->previous_outer_owner = result;
  LOBYTE(result) = v11->flags;
  if ( (v11->flags & 1) != 0 )
    *((_DWORD *)MEMORY[0x4DF904] + 110) = 22;
  return result;
}

