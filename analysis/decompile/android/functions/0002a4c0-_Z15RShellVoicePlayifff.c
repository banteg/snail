/*
 * mangled: _Z15RShellVoicePlayifff
 * demangled: RShellVoicePlay(int, float, float, float)
 * address: 0002a4c0
 * size: 104
 */

/* RShellVoicePlay(int, float, float, float) */

undefined4 RShellVoicePlay(int param_1,float param_2,float param_3,float param_4)

{
  undefined4 uVar1;

  if (param_1 != -1) {
    uVar1 = PfmAudioPlaySample(param_1,param_2,param_3,param_4);
    return uVar1;
  }
  return 0;
}
