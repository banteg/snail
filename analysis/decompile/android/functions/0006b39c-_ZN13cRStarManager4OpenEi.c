/*
 * mangled: _ZN13cRStarManager4OpenEi
 * demangled: cRStarManager::Open(int)
 * address: 0006b39c
 * size: 88
 */

/* cRStarManager::Open(int) */

void cRStarManager::Open(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  bool bVar3;

  iVar2 = DAT_0006b3f4 + 0x6b3b4;
  uVar1 = RShellMemoryMalloc(0,(char *)(iVar2 + DAT_0006b3f8));
  *(undefined4 *)(param_1 + 0x34) = 0;
  bVar3 = (*(uint *)(*(int *)(iVar2 + DAT_0006b3fc) + 0x1c) & 4) == 0;
  if (bVar3) {
    *(undefined4 *)(param_1 + 0x2c) = 0;
  }
  *(undefined4 *)(param_1 + 0x30) = uVar1;
  if (bVar3) {
    return;
  }
  *(undefined4 *)(param_1 + 0x2c) = 1;
  Init((cRStarManager *)param_1);
  return;
}
