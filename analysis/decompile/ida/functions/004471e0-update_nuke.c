/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_nuke @ 0x4471e0 */
/* selector: update_nuke */

// Advances the 25-sprite collision ring effect by orbiting its sprite slots around the owner at radius `7.0` while the owning timer remains active. Cross-port Android symbols match this helper to `cRNuke::AI()`.
int __thiscall sub_4471E0(float *this)
{
  int result; // eax
  double v3; // st7
  unsigned __int8 v5; // c0
  unsigned __int8 v6; // c3
  int v7; // ebx
  char *v8; // esi
  double v9; // st7
  double v10; // st7
  int v11; // [esp+4h] [ebp-4h]
  float v12; // [esp+4h] [ebp-4h]

  result = *(_DWORD *)this;
  if ( *(_DWORD *)this )
  {
    if ( !--result )
    {
      *(this + 3) = *(this + 2) + *(this + 3);
      v3 = *(this + 5) + *(this + 4);
      *(this + 4) = v3;
      if ( !(v5 | v6) )
        *(this + 4) = v3 - 6.2831855;
      v7 = 0;
      v11 = 0;
      v8 = (char *)(this + 6);
      do
      {
        v9 = (double)v11 * 0.039999999 * 6.2831855 + *(this + 4);
        *(float *)(*(_DWORD *)v8 + 80) = *(this + 3);
        v12 = v9;
        *(float *)(*(_DWORD *)v8 + 72) = sine(v12) * 7.0;
        v10 = cosine(v12);
        result = *(_DWORD *)v8;
        ++v7;
        v8 += 4;
        v11 = v7;
        *(float *)(result + 76) = v10 * 7.0;
      }
      while ( v7 < 25 );
    }
  }
  return result;
}

