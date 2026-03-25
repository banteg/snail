/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: play_voice_set @ 0x449390 */
/* selector: play_voice_set */

char __thiscall sub_449390(float *this, int a2)
{
  float v3; // ecx
  int v4; // eax

  if ( *(this + 4) != 0.0 )
    return 0;
  *(this + 4) = *(this + 5);
  if ( a2 == -1 )
  {
    play_voice_backend(
      *(_DWORD *)(*((_DWORD *)this + 3) + 4 * *(_DWORD *)(*((_DWORD *)this + 2) + 4 * *((_DWORD *)this + 1))),
      1.0,
      -1.0,
      0.0);
    v3 = *this;
    v4 = *((_DWORD *)this + 1) + 1;
    *((_DWORD *)this + 1) = v4;
    if ( v4 == LODWORD(v3) )
    {
      *(this + 1) = 0.0;
      return 1;
    }
  }
  else
  {
    play_voice_backend(a2, 1.0, -1.0, 0.0);
  }
  return 1;
}

