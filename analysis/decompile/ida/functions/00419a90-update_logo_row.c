/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_logo_row @ 0x419a90 */
/* selector: update_logo_row */

char __thiscall update_logo_row(int this)
{
  int v1; // eax

  *(float *)(this + 104) = *(float *)(this + 128) + *(float *)(this + 104);
  *(float *)(this + 108) = *(float *)(this + 132) + *(float *)(this + 108);
  *(float *)(this + 112) = *(float *)(this + 136) + *(float *)(this + 112);
  if ( *(float *)(this + 112) <= 8.0 )
    *(_DWORD *)(this + 52) = 1065336439;
  else
    *(float *)(this + 52) = (1.0 - (*(float *)(this + 112) - 8.0) * 0.125) * 0.99900001;
  *(_DWORD *)(*(_DWORD *)(this + 36) + 16) |= 0x10u;
  if ( *(float *)(this + 112) > 16.0 || *(float *)(this + 112) < -4.0 )
  {
    v1 = *(_DWORD *)(this + 4);
    LOBYTE(v1) = v1 & 0xDF;
    *(_DWORD *)(this + 4) = v1;
  }
  else
  {
    v1 = *(_DWORD *)(this + 4);
    LOBYTE(v1) = v1 | 0x20;
    *(_DWORD *)(this + 4) = v1;
  }
  return v1;
}

