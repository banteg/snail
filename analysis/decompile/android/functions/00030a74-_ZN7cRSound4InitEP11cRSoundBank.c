/*
 * mangled: _ZN7cRSound4InitEP11cRSoundBank
 * demangled: cRSound::Init(cRSoundBank*)
 * address: 00030a74
 * size: 132
 */

/* cRSound::Init(cRSoundBank*) */

void __thiscall cRSound::Init(cRSound *this,cRSoundBank *param_1)

{
  undefined4 uVar1;
  char *pcVar2;
  int iVar3;
  int iVar4;
  int iVar5;

  pcVar2 = *(char **)param_1;
  *(cRSoundBank **)this = param_1;
  if (*pcVar2 == '\0') {
    return;
  }
  iVar5 = 0xc;
  iVar4 = 0;
  do {
    iVar3 = iVar5;
    cRResourceManager::Add((cRResourceManager *)&gResourceManager,2,param_1 + 4);
    iVar5 = *(int *)this + iVar4;
    uVar1 = RShellSoundRegister(*(char **)(*(int *)this + iVar4),*(int *)(iVar5 + 8));
    param_1 = (cRSoundBank *)(*(int *)this + iVar3);
    pcVar2 = *(char **)(*(int *)this + iVar3);
    *(undefined4 *)(iVar5 + 4) = uVar1;
    iVar5 = iVar3 + 0xc;
    iVar4 = iVar3;
  } while (*pcVar2 != '\0');
  return;
}
