/*
 * mangled: _ZN7cRSound4InitEP11cRSoundBank
 * demangled: cRSound::Init(cRSoundBank*)
 * address: 00063300
 * size: 68
 */

/* cRSound::Init(cRSoundBank*) */

void __thiscall cRSound::Init(cRSound *this,cRSoundBank *param_1)

{
  char *pcVar1;
  undefined4 uVar2;

  pcVar1 = *(char **)param_1;
  if (*pcVar1 != '\0') {
    do {
      uVar2 = RShellSoundRegister(pcVar1,*(int *)(param_1 + 8));
      *(undefined4 *)(param_1 + 4) = uVar2;
      pcVar1 = *(char **)(param_1 + 0xc);
      param_1 = param_1 + 0xc;
    } while (*pcVar1 != '\0');
    return;
  }
  return;
}
