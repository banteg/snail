/*
 * mangled: _Z15RShellVoicePlayPcfff
 * demangled: RShellVoicePlay(char*, float, float, float)
 * address: 0002b58c
 * size: 40
 */

/* RShellVoicePlay(char*, float, float, float) */

void RShellVoicePlay(char *param_1,float param_2,float param_3,float param_4)

{
  int iVar1;
  float extraout_s0;
  float extraout_s1;
  float extraout_s2;

  iVar1 = RShellFindSample(param_1);
  RShellVoicePlay(iVar1,extraout_s0,extraout_s1,extraout_s2);
  return;
}
