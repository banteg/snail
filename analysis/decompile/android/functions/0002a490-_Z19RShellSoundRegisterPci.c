/*
 * mangled: _Z19RShellSoundRegisterPci
 * demangled: RShellSoundRegister(char*, int)
 * address: 0002a490
 * size: 40
 */

/* RShellSoundRegister(char*, int) */

void RShellSoundRegister(char *param_1,int param_2)

{
  cRLoadingBar::Signal((cRLoadingBar *)&gLoadingBar);
  PfmAudioLoadSample(param_1);
  return;
}
