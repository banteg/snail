/*
 * mangled: _Z15RShellVoicePlayifff
 * demangled: RShellVoicePlay(int, float, float, float)
 * address: 0000c130
 * size: 156
 */

/* RShellVoicePlay(int, float, float, float) */

void RShellVoicePlay(int param_1,float param_2,float param_3,float param_4)

{
  if (param_1 == -1) {
    return;
  }
  if (param_4 == 0.0) {
    if (param_3 == -1.0) {
      MacAudioPlaySample(param_1,param_2 * *(float *)PTR__MacNormalizeVoice_001b61c0,-1.0,0.0);
      return;
    }
    MacAudioPlaySample(param_1,param_2 * *(float *)PTR__MacNormalizeVoice_001b61c0,param_3,0.0);
    return;
  }
  MacAudioPlaySample(param_1,param_2 * *(float *)PTR__MacNormalizeVoice_001b61c0,-1.0,param_4);
  return;
}
