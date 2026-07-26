/*
 * mangled: _Z19RShellSoundRegisterPci
 * demangled: RShellSoundRegister(char*, int)
 * address: 0000cfd0
 * size: 112
 */

/* RShellSoundRegister(char*, int) */

int RShellSoundRegister(char *param_1,int param_2)

{
  int iVar1;

  Rstrcpy((char *)(&_RShellSoundName + _RShellSoundCount * 0x20),param_1);
  iVar1 = _RShellSoundCount + 1;
  if (_RShellSoundCount + 1 == 0x100) {
    RShellError("Run out of Sound slots increase RSHELL_SOUND_MAX in RShell.h");
    iVar1 = _RShellSoundCount;
  }
  _RShellSoundCount = iVar1;
  cRLoadingBar::Signal((cRLoadingBar *)PTR__gLoadingBar_001b60bc);
  MacAudioLoadSample(param_1);
  return _RShellSoundCount + -1;
}
