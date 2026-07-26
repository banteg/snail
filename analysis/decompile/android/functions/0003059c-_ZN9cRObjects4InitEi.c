/*
 * mangled: _ZN9cRObjects4InitEi
 * demangled: cRObjects::Init(int)
 * address: 0003059c
 * size: 248
 */

/* cRObjects::Init(int) */

void __thiscall cRObjects::Init(cRObjects *this,int param_1)

{
  int iVar1;
  undefined4 uVar2;
  char *pcVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint local_1c;

  iVar4 = DAT_00030694;
  *(int *)(this + 4) = param_1;
  iVar4 = iVar4 + 0x305c0;
  iVar5 = 0;
  pcVar3 = (char *)(iVar4 + DAT_00030698);
  *(undefined4 *)this = 0;
  iVar1 = RShellMemoryMalloc(param_1 * 0x110,pcVar3);
  *(int *)(this + 8) = iVar1;
  if (0 < param_1) {
    iVar6 = 0;
    while( true ) {
      iVar6 = iVar6 + 1;
      cRObject::Init((cRObject *)(iVar1 + iVar5));
      iVar5 = iVar5 + 0x110;
      if (param_1 <= iVar6) break;
      iVar1 = *(int *)(this + 8);
    }
  }
  iVar1 = DAT_0003069c;
  *(undefined4 *)(this + 0xc) = 0;
  uVar2 = RShellMemoryMalloc(0x6000,(char *)(iVar4 + iVar1));
  pcVar3 = (char *)(iVar4 + DAT_000306a0);
  *(undefined4 *)(this + 0x10) = uVar2;
  iVar1 = RShellFindFile(pcVar3,false);
  if (iVar1 != 0) {
    wprintf((char *)(iVar4 + DAT_000306a4));
    uVar2 = RShellLoadFile(pcVar3,*(void **)(this + 0x10),(int *)&local_1c);
    *(undefined4 *)(this + 0x10) = uVar2;
    wprintf((char *)(iVar4 + DAT_000306a8));
    pcVar3 = (char *)(iVar4 + DAT_000306ac);
    *(uint *)(this + 0xc) = local_1c / 0xc;
    wprintf(pcVar3,local_1c * -0x55555555);
  }
  return;
}
