/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: kill_sprite @ 0x44e200 */
/* selector: kill_sprite */

void __thiscall kill_sprite(int sprite)
{
  int next; // eax
  int prev; // eax
  int next_after_prev; // eax

  if ( (*(_BYTE *)(sprite + 4) & 1) == 0 )
    report_errorf("Sprite kill error, already dead (%s)", (const char *)(*(_DWORD *)(sprite + 28) + 12));
  if ( (_UNKNOWN *)sprite != &unk_814CB0 )
  {
    *(_DWORD *)(sprite + 4) &= ~1u;
    if ( sprite == unk_814C94[*(_DWORD *)(sprite + 8)] )
    {
      next = *(_DWORD *)(sprite + 12);
      if ( next )
        *(_DWORD *)(next + 16) = 0;
      unk_814C94[*(_DWORD *)(sprite + 8)] = *(_DWORD *)(sprite + 12);
      *(_DWORD *)(sprite + 12) = unk_814CA8;
      unk_814CA8 = sprite;
    }
    else
    {
      prev = *(_DWORD *)(sprite + 16);
      if ( prev )
        *(_DWORD *)(prev + 12) = *(_DWORD *)(sprite + 12);
      next_after_prev = *(_DWORD *)(sprite + 12);
      if ( next_after_prev )
        *(_DWORD *)(next_after_prev + 16) = *(_DWORD *)(sprite + 16);
      *(_DWORD *)(sprite + 12) = unk_814CA8;
      unk_814CA8 = sprite;
    }
  }
}
