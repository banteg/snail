/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: kill_sprite @ 0x44e200 */
/* selector: kill_sprite */

void __thiscall sub_44E200(int this)
{
  int v2; // eax
  int v3; // eax
  int v4; // eax

  if ( (*(_BYTE *)(this + 4) & 1) == 0 )
    report_errorf("Sprite kill error, already dead (%s)", (const char *)(*(_DWORD *)(this + 28) + 12));
  if ( (_UNKNOWN *)this != &unk_814CB0 )
  {
    *(_DWORD *)(this + 4) &= ~1u;
    if ( this == unk_814C94[*(_DWORD *)(this + 8)] )
    {
      v2 = *(_DWORD *)(this + 12);
      if ( v2 )
        *(_DWORD *)(v2 + 16) = 0;
      unk_814C94[*(_DWORD *)(this + 8)] = *(_DWORD *)(this + 12);
      *(_DWORD *)(this + 12) = unk_814CA8;
      unk_814CA8 = this;
    }
    else
    {
      v3 = *(_DWORD *)(this + 16);
      if ( v3 )
        *(_DWORD *)(v3 + 12) = *(_DWORD *)(this + 12);
      v4 = *(_DWORD *)(this + 12);
      if ( v4 )
        *(_DWORD *)(v4 + 16) = *(_DWORD *)(this + 16);
      *(_DWORD *)(this + 12) = unk_814CA8;
      unk_814CA8 = this;
    }
  }
}

