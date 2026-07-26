/*
 * mangled: _Z15RShellSoundPlayifff
 * demangled: RShellSoundPlay(int, float, float, float)
 * address: 0000c1d8
 * size: 156
 */

/* RShellSoundPlay(int, float, float, float) */

void RShellSoundPlay(int param_1,float param_2,float param_3,float param_4)

{
  if (param_1 == -1) {
    return;
  }
  if (param_4 == 0.0) {
    if (param_3 == -1.0) {
      MacAudioPlaySample(param_1,param_2 * *(float *)PTR__MacNormalizeSfx_001b61bc,-1.0,0.0);
      return;
    }
    MacAudioPlaySample(param_1,param_2 * *(float *)PTR__MacNormalizeSfx_001b61bc,param_3,0.0);
    return;
  }
  MacAudioPlaySample(param_1,param_2 * *(float *)PTR__MacNormalizeSfx_001b61bc,-1.0,param_4);
  return;
}
