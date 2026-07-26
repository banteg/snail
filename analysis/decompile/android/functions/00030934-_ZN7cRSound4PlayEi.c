/*
 * mangled: _ZN7cRSound4PlayEi
 * demangled: cRSound::Play(int)
 * address: 00030934
 * size: 36
 */

/* cRSound::Play(int) */

void cRSound::Play(int param_1)

{
  int in_r1;
  float in_s0;
  float in_s1;
  float in_s2;

  RShellSoundPlay(*(int *)(*(int *)param_1 + in_r1 * 0xc + 4),in_s0,in_s1,in_s2);
  return;
}
