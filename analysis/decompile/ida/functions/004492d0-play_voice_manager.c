/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: play_voice_manager @ 0x4492d0 */
/* selector: play_voice_manager */

char __thiscall sub_4492D0(int this, int a2, unsigned int a3, int a4)
{
  int v5; // eax
  char result; // al

  if ( a3 < 2 )
  {
    if ( is_voice_playing((int *)this) != -1 )
      return 0;
    if ( a3 == 1 && *(float *)(this + 384) < (double)*(float *)(this + 388) )
      return 0;
  }
  else if ( a3 == 2 )
  {
    v5 = is_voice_playing((int *)this);
    if ( v5 != -1 )
      stop_registered_sound_sample(v5);
  }
  result = play_voice_set((float *)(this + 24 * a2), a4);
  if ( result == 1 && (a3 == 1 || a3 == 2) )
    *(_DWORD *)(this + 384) = 0;
  return result;
}

