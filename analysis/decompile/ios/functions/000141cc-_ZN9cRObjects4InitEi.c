/*
 * mangled: _ZN9cRObjects4InitEi
 * demangled: cRObjects::Init(int)
 * address: 000141cc
 * size: 256
 */

/* cRObjects::Init(int) */

void __thiscall cRObjects::Init(cRObjects *this,int param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint local_24;

  iVar3 = 0;
  *(undefined4 *)this = 0;
  *(int *)(this + 4) = param_1;
  uVar1 = RShellMemoryMalloc(param_1 * 0x110,"Object List");
  *(undefined4 *)(this + 8) = uVar1;
  if (0 < param_1) {
    iVar4 = 0;
    do {
      iVar2 = iVar4 + *(int *)(this + 8);
      iVar3 = iVar3 + 1;
      *(undefined4 *)(iVar4 + *(int *)(this + 8)) = 0;
      *(undefined4 *)(iVar2 + 8) = 0;
      *(undefined4 *)(iVar2 + 0xa0) = 0;
      *(undefined4 *)(iVar2 + 0xc0) = 0;
      *(undefined4 *)(iVar2 + 0xb0) = 0;
      *(undefined4 *)(iVar2 + 0xac) = 0;
      *(undefined4 *)(iVar2 + 0xd4) = 0;
      _strcpy((char *)(iVar2 + 0x20),"Nao");
      *(undefined4 *)(iVar2 + 0x10c) = 0;
      *(undefined4 *)(iVar2 + 0xcc) = 0;
      *(undefined4 *)(iVar2 + 0xd0) = 0;
      *(undefined4 *)(iVar2 + 0xa4) = 0;
      *(undefined4 *)(iVar2 + 200) = 0;
      iVar4 = iVar4 + 0x110;
    } while (iVar3 != param_1);
  }
  *(undefined4 *)(this + 0xc) = 0;
  uVar1 = RShellMemoryMalloc(0x6000,"Objects Normal Table");
  *(undefined4 *)(this + 0x10) = uVar1;
  iVar3 = RShellFindFile("Data/NormalsTable.bin",false);
  if (iVar3 != 0) {
    uVar1 = RShellLoadFile("Data/NormalsTable.bin",*(void **)(this + 0x10),(int *)&local_24);
    *(uint *)(this + 0xc) = local_24 / 0xc;
    *(undefined4 *)(this + 0x10) = uVar1;
  }
  return;
}
