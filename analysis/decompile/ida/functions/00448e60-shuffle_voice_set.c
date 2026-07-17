/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: shuffle_voice_set @ 0x448e60 */
/* selector: shuffle_voice_set */

void __thiscall shuffle_voice_set(VoiceSet *set)
{
  int v2; // ebx
  int v3; // edi
  __int64 v4; // rax
  int32_t *playlist; // ecx

  v2 = 100;
  do
  {
    v3 = (__int64)((double)next_math_random_value() * (double)(int)set->sample_count * 0.000030517578);
    v4 = (__int64)((double)next_math_random_value() * (double)(int)set->sample_count * 0.000030517578);
    playlist = set->playlist;
    --v2;
    HIDWORD(v4) = playlist[v3];
    playlist[v3] = playlist[(_DWORD)v4];
    set->playlist[v4] = HIDWORD(v4);
  }
  while ( v2 );
}
