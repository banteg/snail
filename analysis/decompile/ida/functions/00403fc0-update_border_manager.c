/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_border_manager @ 0x403fc0 */
/* selector: update_border_manager */

void __thiscall update_border_manager(int this)
{
  double v1; // st7
  int v2; // eax
  int v3; // edx

  if ( *(_BYTE *)(this + 275872) )
  {
    v1 = *(float *)(this + 275880) + *(float *)(this + 275876);
    *(float *)(this + 275876) = v1;
    if ( v1 > 1.0 )
    {
      v2 = *(_DWORD *)(this + 275884);
      *(_DWORD *)(this + 275876) = 1065353216;
      v3 = *(_DWORD *)(v2 + 416);
      if ( (v3 & 0x40000000) == 0 || *((_DWORD *)MEMORY[0x4DF904] + 9) == 4 )
      {
        *(_DWORD *)(v2 + 416) = v3 | *(_DWORD *)(this + 275868);
        *(_BYTE *)(this + 275872) = 0;
      }
    }
  }
}

