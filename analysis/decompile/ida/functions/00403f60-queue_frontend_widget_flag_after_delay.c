/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: queue_frontend_widget_flag_after_delay @ 0x403f60 */
/* selector: queue_frontend_widget_flag_after_delay */

// Arms the shared border-manager delay lane for one front-end widget: stores the destination widget pointer and flag mask, starts the fixed `0.1` step timer, and optionally begins the global front-end fade when the widget requests it.
char __thiscall sub_403F60(int this, int a2, int a3)
{
  char result; // al

  result = *(_BYTE *)(this + 275872);
  if ( !result )
  {
    if ( (*(_DWORD *)(a2 + 416) & 0x40000000) != 0 )
      result = begin_frontend_fade_out((_DWORD *)MEMORY[0x4DF904] + 9, 0);
    *(_DWORD *)(this + 275884) = a2;
    *(_BYTE *)(this + 275872) = 1;
    *(_DWORD *)(this + 275876) = 0;
    *(_DWORD *)(this + 275880) = 1034594987;
    *(_DWORD *)(this + 275868) = a3;
  }
  return result;
}

