/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_tip @ 0x448c40 */
/* selector: update_tip */

// Runs one gameplay tip slot, handling hide or show state, button-click consumption, timed expiry, and the final teardown or UI-state restore path.
void *__fastcall update_tip(TipSlot *slot)
{
  _DWORD *widget_main; // ecx
  void *result; // eax
  _DWORD *widget_ok; // ecx
  double v5; // st7
  __int16 v6; // fps
  bool v7; // c0
  char v8; // c2
  bool v9; // c3

  widget_main = slot->widget_main;
  if ( *((_BYTE *)MEMORY[0x4DF904] + 476705) )
  {
    hide_border_init(widget_main);
  }
  else
  {
    LOWORD(result) = unhide_border_init(widget_main);
    widget_ok = slot->widget_ok;
    if ( widget_ok && (result = (void *)widget_ok[104], ((unsigned __int8)result & 0x20) != 0)
      || (widget_ok = slot->widget_disable) != nullptr
      && (result = (void *)widget_ok[104], ((unsigned __int8)result & 0x20) != 0) )
    {
      LOBYTE(result) = (unsigned __int8)result & 0xDF;
      widget_ok[104] = result;
      *((_DWORD *)MEMORY[0x4DF904] + 110) = slot->previous_outer_owner;
      kill_tip_widgets(slot);
      result = (void *)unhide_all_borders((int *)MEMORY[0x4DF904] + 723);
      slot->active = 0;
    }
    else if ( (slot->definition->flags & 2) != 0 )
    {
      v5 = slot->dismiss_step + slot->dismiss_progress;
      slot->dismiss_progress = v5;
      v7 = v5 < 1.0;
      v8 = 0;
      v9 = v5 == 1.0;
      LOWORD(result) = v6;
      if ( v5 > 1.0 )
      {
        kill_tip_widgets(slot);
        slot->active = 0;
      }
    }
  }
  return result;
}

