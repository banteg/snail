/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: flush_row_event_display @ 0x404830 */
/* selector: flush_row_event_display */

// Fast-forwards the active gameplay row-event display by paying out any remaining row score awards, destroying its widget actors, and clearing the owning controller state.
int __thiscall sub_404830(_DWORD *this)
{
  int result; // eax
  int v3; // eax
  int v4; // ecx
  int v5; // ecx
  int v6; // eax
  _DWORD *v7; // [esp-4h] [ebp-8h]

  result = *(this + 5);
  if ( result )
  {
    v3 = *(this + 10);
    v4 = *(this + 7);
    if ( v3 != v4 )
    {
      if ( v3 < v4 )
      {
        do
        {
          add_subgoldy_score((int *)((char *)&loc_42FD7C + (_DWORD)MEMORY[0x4DF904]), 4, 0);
          v5 = *(this + 7);
          v6 = *(this + 10) + 1;
          *(this + 10) = v6;
        }
        while ( v6 < v5 );
      }
      if ( *(this + 8) )
        add_subgoldy_score((int *)((char *)&loc_42FD7C + (_DWORD)MEMORY[0x4DF904]), *(this + 18), 0);
    }
    v7 = (_DWORD *)*this;
    ++*(this + 10);
    kill_border(v7);
    kill_border((_DWORD *)*(this + 1));
    kill_border((_DWORD *)*(this + 3));
    kill_border((_DWORD *)*(this + 2));
    kill_border((_DWORD *)*(this + 4));
    result = *(this + 19);
    if ( *((_DWORD *)MEMORY[0x4DF904] + 1097752) != result )
      *((_DWORD *)MEMORY[0x4DF904] + 1097752) = result;
  }
  *(this + 5) = 0;
  return result;
}

