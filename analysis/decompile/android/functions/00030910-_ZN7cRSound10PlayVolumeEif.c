/*
 * mangled: _ZN7cRSound10PlayVolumeEif
 * demangled: cRSound::PlayVolume(int, float)
 * address: 00030910
 * size: 36
 */

/* cRSound::PlayVolume(int, float) */

void cRSound::PlayVolume(int param_1,float param_2)

{
  int in_r1;
  float in_s1;
  float in_s2;

  RShellSoundPlay(*(int *)(*(int *)param_1 + in_r1 * 0xc + 4),param_2,in_s1,in_s2);
  return;
}
