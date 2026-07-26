/*
 * mangled: _ZN7cRSound4PlayEif
 * demangled: cRSound::Play(int, float)
 * address: 000308f4
 * size: 28
 */

/* cRSound::Play(int, float) */

void cRSound::Play(int param_1,float param_2)

{
  int in_r1;
  float in_s1;
  float in_s2;

  RShellSoundPlay(*(int *)(*(int *)param_1 + in_r1 * 0xc + 4),param_2,in_s1,in_s2);
  return;
}
