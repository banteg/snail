/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_banner @ 0x441d40 */
/* selector: update_banner */

void __thiscall update_banner(int this)
{
  int v1; // eax
  bool v2; // c0
  int v3; // eax
  double v4; // st7
  unsigned __int8 v6; // c0
  unsigned __int8 v7; // c3
  float v8; // [esp+0h] [ebp-8h]

  v1 = *(_DWORD *)(this + 56);
  if ( !v1 )
  {
    v2 = *(float *)(*(_DWORD *)(this + 84) + 112) < 40.0;
    goto LABEL_5;
  }
  if ( v1 == 1 )
  {
    v2 = *(float *)(this + 24) - *(float *)(*(_DWORD *)(this + 84) + 112) < 46.0;
LABEL_5:
    v3 = *(_DWORD *)(this + 4);
    if ( v2 )
      LOBYTE(v3) = v3 | 0x20;
    else
      LOBYTE(v3) = v3 & 0xDF;
    *(_DWORD *)(this + 4) = v3;
  }
  v4 = *(float *)(this + 92) + *(float *)(this + 88);
  *(float *)(this + 88) = v4;
  if ( !(v6 | v7) )
    *(float *)(this + 88) = v4 - 1.0;
  v8 = *(float *)(this + 88) * 6.2831855;
  *(float *)(this + 20) = sine(v8) * 0.25999999;
}

