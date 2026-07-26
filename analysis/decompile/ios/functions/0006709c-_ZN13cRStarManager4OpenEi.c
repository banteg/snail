/*
 * mangled: _ZN13cRStarManager4OpenEi
 * demangled: cRStarManager::Open(int)
 * address: 0006709c
 * size: 80
 */

/* cRStarManager::Open(int) */

void cRStarManager::Open(int param_1)

{
  undefined *puVar1;
  undefined4 uVar2;

  uVar2 = RShellMemoryMalloc(0,"StarField");
  *(undefined4 *)(param_1 + 0x34) = 0;
  puVar1 = PTR__gConfig_001b60d4;
  *(undefined4 *)(param_1 + 0x30) = uVar2;
  if ((*(uint *)(puVar1 + 0x1c) & 4) != 0) {
    *(undefined4 *)(param_1 + 0x2c) = 1;
    Init((cRStarManager *)param_1);
    return;
  }
  *(undefined4 *)(param_1 + 0x2c) = 0;
  return;
}
