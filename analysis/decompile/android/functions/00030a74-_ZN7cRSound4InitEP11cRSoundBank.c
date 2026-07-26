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
  cRResourceManager *pcVar5;
  int iVar6;

  pcVar2 = *(char **)param_1;
  *(cRSoundBank **)this = param_1;
  if (*pcVar2 == '\0') {
    return;
  }
  pcVar5 = *(cRResourceManager **)(DAT_00030af8 + 0x30a98 + DAT_00030afc);
  iVar6 = 0xc;
  iVar4 = 0;
  do {
    iVar3 = iVar6;
    cRResourceManager::Add(pcVar5,2,param_1 + 4);
    iVar6 = *(int *)this + iVar4;
    uVar1 = RShellSoundRegister(*(char **)(*(int *)this + iVar4),*(int *)(iVar6 + 8));
    param_1 = (cRSoundBank *)(*(int *)this + iVar3);
    pcVar2 = *(char **)(*(int *)this + iVar3);
    *(undefined4 *)(iVar6 + 4) = uVar1;
    iVar6 = iVar3 + 0xc;
    iVar4 = iVar3;
  } while (*pcVar2 != '\0');
  return;
}
