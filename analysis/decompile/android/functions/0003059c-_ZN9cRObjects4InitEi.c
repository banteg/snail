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
  int iVar3;
  int iVar4;
  uint local_1c;

  *(int *)(this + 4) = param_1;
  iVar3 = 0;
  *(undefined4 *)this = 0;
  iVar1 = RShellMemoryMalloc(param_1 * 0x110,"Object List");
  *(int *)(this + 8) = iVar1;
  if (0 < param_1) {
    iVar4 = 0;
    while( true ) {
      iVar4 = iVar4 + 1;
      cRObject::Init((cRObject *)(iVar1 + iVar3));
      iVar3 = iVar3 + 0x110;
      if (param_1 <= iVar4) break;
      iVar1 = *(int *)(this + 8);
    }
  }
  *(undefined4 *)(this + 0xc) = 0;
  uVar2 = RShellMemoryMalloc(0x6000,"Objects Normal Table");
  *(undefined4 *)(this + 0x10) = uVar2;
  iVar1 = RShellFindFile("Data/NormalsTable.bin",false);
  if (iVar1 != 0) {
    wprintf("1\n");
    uVar2 = RShellLoadFile("Data/NormalsTable.bin",*(void **)(this + 0x10),(int *)&local_1c);
    *(undefined4 *)(this + 0x10) = uVar2;
    wprintf("2\n");
    *(uint *)(this + 0xc) = local_1c / 0xc;
    wprintf("3\n",local_1c * -0x55555555);
  }
  return;
}
