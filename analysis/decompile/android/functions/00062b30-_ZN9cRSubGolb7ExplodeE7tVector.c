/*
 * mangled: _ZN9cRSubGolb7ExplodeE7tVector
 * demangled: cRSubGolb::Explode(tVector)
 * address: 00062b30
 * size: 180
 */

/* cRSubGolb::Explode(tVector) */

void cRSubGolb::Explode(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;

  if ((gConfig._28_4_ & 0x10) != 0) {
    iVar1 = cRSpriteManager::New
                      ((int)&gRSpriteManager,*(int *)(*(int *)(param_1 + 600) + 0x370),0x13,-1);
    *(undefined4 *)(iVar1 + 0x78) = 0;
    *(undefined4 *)(iVar1 + 0x68) = 0;
    *(undefined4 *)(iVar1 + 0x70) = 0;
    *(undefined4 *)(iVar1 + 0x5c) = 0;
    *(undefined4 *)(iVar1 + 0x54) = 0;
    *(undefined4 *)(iVar1 + 0x6c) = 0x3d638e39;
    *(undefined4 *)(iVar1 + 0x74) = 0x3f555556;
    *(undefined4 *)(iVar1 + 0x60) = 0x3f000000;
    *(undefined4 *)(iVar1 + 100) = 0x3f800000;
    *(undefined4 *)(iVar1 + 0x58) = 0x3d4ccccd;
    *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) | 0x800;
    *(undefined4 *)(iVar1 + 0x48) = param_2;
    *(undefined4 *)(iVar1 + 0x4c) = param_3;
    *(undefined4 *)(iVar1 + 0x50) = param_4;
  }
  return;
}
