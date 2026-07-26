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
  bool bVar2;

  uVar1 = RShellMemoryMalloc(0,"StarField");
  *(undefined4 *)(param_1 + 0x34) = 0;
  bVar2 = (gConfig._28_4_ & 4) == 0;
  if (bVar2) {
    *(undefined4 *)(param_1 + 0x2c) = 0;
  }
  *(undefined4 *)(param_1 + 0x30) = uVar1;
  if (bVar2) {
    return;
  }
  *(undefined4 *)(param_1 + 0x2c) = 1;
  Init((cRStarManager *)param_1);
  return;
}
